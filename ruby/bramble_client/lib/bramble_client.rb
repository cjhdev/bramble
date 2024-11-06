require 'logger'

class BrambleClient

  class Listener

    def initialize(client, prefix, message)
      @client = client
      @queue = TimeoutQueue.new
      @prefix = prefix
      @message = message
    end

    def pop(non_block=false, **opts)
      begin

        msg = @queue.pop(non_block, **opts)

        case msg[1].upcase
        when "EVT"
          msg = msg.first.split
        when "LOG"
          msg = [msg[0], msg[2]]
        end

        msg

      rescue ThreadError
        raise ListenTimeoutError
      rescue ClosedQueueError
        raise ClosedError
      end
    end

    def stop_listening
      client.stop_listening(self)
    end

    # private
    def close
      @queue.close
    end

    # private
    def input(prefix, data)

      prefix_match = @prefix.match(prefix)
      message_match = @message.match(data)

      unless @queue.closed?

        if prefix_match and message_match

          @queue.push([data, prefix_match[:prefix], message_match])

        end

      end

    end

  end

  CMD = "CMD"
  ACK = "ACK"
  NAK = "NAK"
  EVT = "EVT"
  LOG = "LOG"

  # timeout waiting for an ACK/NAK
  class ResponseTimeoutError < StandardError
  end

  # expecting an ACK/NAK but got something else
  class ResponseFormatError < StandardError
  end

  # received a NAK instead of an ACK
  class ResponseError < StandardError
  end

  # generic listen timeout
  class ListenTimeoutError < StandardError
  end

  # transport layer was closed
  class ClosedError < StandardError
  end

  # push data into client
  def input(bytes)

    with_mutex do

      @buffer.concat(bytes)

      while line = @buffer.slice!(/.*\r\n/) do

        line.strip!

        @logger.debug{"#{@log_header}rx: #{line}"} unless line.empty?

        prefix, colon, data = line.partition(':')

        prefix.strip!
        data.strip!

        @listeners.each{|listener|listener.input(prefix, data)}

      end

    end

  end

  # Create a client
  #
  #
  def initialize(**opts, &block)

    @input_queue = Queue.new
    @listeners = []
    @mutex = Mutex.new
    @logger = opts[:logger]||Logger.new(IO::NULL)
    @log_header = opts[:log_header]||"cli: "
    @buffer = ""
    @command_timeout = opts[:command_timeout]||5
    @output_handler = block
    @invoke_id=0

  end

  # set the output_handler if it wasn't set in the constructor
  def set_output_handler(&block)
    @output_handler = block
  end

  # signal to client instance that connection has closed
  #
  #
  def close
    with_mutex do
      @listeners.each { |listener| listener.close }

      # don't get rid of listeners just because you closed them?
      #@listeners.clear
    end
  end

  # send a command
  def command(*arg, **opts)

    raise ArgumentError.new "command argument cannot be empty" if arg.empty?

    response_line = nil

    cmd_line = arg.compact.inject(""){ |acc, a| acc << " #{convert_argument(a)}" }.strip

    if opts[:timeout]
      timeout = opts[:timeout].to_f
    else
      timeout = @command_timeout
    end

    start_listening([CMD,ACK,NAK], /^#{arg.first.to_s.strip}($)|([ ])/) do |listener|

      @output_handler.call("\r#{cmd_line}\r", self) if @output_handler

      @logger.debug{"#{@log_header}tx: #{cmd_line}"}

      timeout_time = Time.now + @command_timeout

      begin
        echo, echo_type = listener.pop(timeout: timeout)
      rescue ListenTimeoutError
        raise ResponseTimeoutError
      end

      raise ResponseFormatError unless echo_type == CMD and echo == cmd_line

      time_now = Time.now

      raise ResponseTimeoutError unless time_now < timeout_time

      begin
        response, response_type = listener.pop(timeout: (timeout_time - time_now))
      rescue ListenTimeoutError
        raise ResponseTimeoutError
      end

      # second response must be an ack/nak
      raise ResponseFormatError unless [ACK,NAK].include? response_type

      # tokenize
      # fixme: support quotes
      response_line = response.split

      # drop the command name
      response_line.shift

      raise ResponseError.new(response_line.first) if response_type == NAK

    end

    response_line

  end

  # listen for an event
  #
  #
  def listen_for_event(*event_name, &block)

    raise ArgumentError.new "must provide at least one event" if event_name.empty?

    pattern = event_name.map do |e|

      "(#{e})#{"|" unless e == event_name.last}"

    end.join

    pattern = "^(#{pattern})"

    start_listening(EVT, pattern, &block)
  end

  def listen_for_log(pattern, &block)

    start_listening(LOG, pattern.to_s, &block)

  end

  # listen for a line prefix and optionally a particular pattern in the text to follow
  #
  # this will match the line and return it complete
  #
  #
  def start_listening(prefix, msg_pattern=/[\s\S]*/, &block)

    prefix = [prefix].flatten.uniq

    raise ArgumentError if prefix.empty?
    raise ArgumentError unless prefix.all? { |t| [CMD,ACK,NAK,EVT,LOG].include? t }

    prefix_pattern = /(?<prefix>#{prefix.join('|')})/

    listener = Listener.new(self, prefix_pattern, Regexp.new(msg_pattern))

    begin

      with_mutex do
        @listeners << listener
      end

      return listener unless block

      retval = nil

      retval = yield(listener)

    rescue => e

      stop_listening(listener)
      raise e

    end

    stop_listening(listener)

    retval

  end

  # destroy a listener
  def stop_listening(listener)
    with_mutex do
      @listeners.delete(listener).tap do |l|
        l.close if l
      end
      self
    end
  end

  ## private ################################################################

  def with_mutex
    @mutex.synchronize do
      yield
    end
  end

  # convert bytes to hex string
  def convert_argument(value)
    if value.kind_of? String
      if value.ascii_only?
        value
      else
        value.bytes.map{|v|"%02X" % v}.join
      end
    else
      value.to_s
    end
  end

  class TimeoutQueue

    def initialize(**opt)

      @queue = []
      @mutex = Mutex.new
      @received = ConditionVariable.new
      @closed = false
      @waiting = []

    end

    # push object into end of queue
    #
    # @param object
    # @return object
    #
    def push(object, **opt)
      __push(object) do
        @queue.send(__method__, object)
      end
    end

    # push object into front of the queue
    #
    # @param object
    # @return object
    #
    def unshift(object)
      __push(object) do
        @queue.send(__method__, object)
      end
    end

    # delete an object from the queue before it can be popped
    #
    # @param object
    # @return object
    #
    def delete(object)

      with_mutex do
        @queue.delete(object)
      end

      object

    end

    # retrieve next object from queue
    #
    # @param non_block [TrueClass,FalseClass] set true to enable non-blocking mode
    # @param opts [Hash]
    #
    # @option opts [Float,Integer] :timeout seconds to wait (in blocking mode)
    #
    # @raise ThreadError if timeout expires or queue is empty in non_block mode
    #
    def pop(non_block=false, **opts)

      timeout = opts[:timeout]

      with_mutex do

        @waiting << Thread.current

        if timeout
          end_time = Time.now + timeout.to_f
        end

        while @queue.empty? and not(non_block) and not(@closed)

          if timeout

            break unless ((time_now = Time.now) < end_time)

            @received.wait(@mutex, end_time - time_now)

          else

            @received.wait(@mutex)

          end

        end

        @waiting.delete(Thread.current)

        if @queue.empty?

          if @closed
            raise ClosedQueueError
          else
            raise ThreadError
          end

        else

          @queue.shift

        end

      end

    end

    def num_waiting
      with_mutex do
        @waiting.size
      end
    end

    def closed?
      @closed
    end

    def close
      with_mutex do
        if not @closed
          @closed = true
          @waiting.each(&:wakeup)
        end
      end
      self
    end

    def empty?
      @queue.send __method__
    end

    def size
      @queue.send __method__
    end

    def clear
      with_mutex do
        @queue.clear
      end
      self
    end

    def with_mutex
      @mutex.synchronize do
        yield
      end
    end

    def __push(object)
      with_mutex do
        raise ClosedQueueError if closed?
        yield
        @received.signal
      end
      object
    end

    alias_method :length, :size

    alias_method :'<<', :push
    alias_method :enq, :push

    alias_method :shift, :pop
    alias_method :deq, :pop

    private :with_mutex, :__push

  end

end
