bramble_client
==============

A transport layer agnostic client side implementation of Bramble Protocol.

## Example

### Creating an Instance

~~~ ruby
require 'bramble_client'

client = BrambleClient.new(
  command_timeout: 5,
  log_header: "eut: ",    # will appear in front of the log message (default is cli: )
  logger: your_logger
)
~~~

### Connecting Client to Transport Layer

~~~ ruby
client.set_output_handler do |output, the_client_again|

  # send output to the transport layer

end

# or

client = BrambleClient.new do |output, the_client_again|

  # send output to the transport layer

end

# feed data into client from transport layer
client.input(any_data_received_from_transport_layer)

# indicate a close (to unblock any listeners)
client.close

~~~

### Using the Client

Send commands:

~~~ ruby

begin

  response = client.command "help"

rescue BrambleClient::ResponseTimeoutError

  # the CMD and/or ACK/NAK not received within :command_timeout

rescue BrambleClient::ResponseFormatError

  # ACK and/or RSP is malformed

rescue BrambleClient::ResponseError => e

  # server responded with negative acknowledge (NAK)

  # get the error_name
  # puts e.to_s
  # > command_not_found

rescue BrambleClient::ClosedError

  # the transport layer closed

end

# pp response
# > [arg1, arg2, argn]


# override the timeout
response = client.command "other_command", timeout: 1

~~~

Listen for events:

~~~ ruby

client.listen_for_event 'some_event_name' do |listener|

    # wait forever
    evt = listener.pop

    # wait for timeout
    # raises BrambleClient::ListenTimeoutError
    evt = listener.pop(timeout: 1)

    # poll non-blocking
    evt = listener.pop(true)

    evt = listener.pop

    # pp evt
    # > ['some_event_name', 'arg1', 'arg2', 'argn']

end

client.listen_for_event 'this_event', 'that_event' do |listener|
end

client.listen_for_event /some[a-z_]+event/ do |listener|
end

listener = client.listen_for_event 'this_event'

evt = listener.pop

client.stop_listening(listener)

~~~

Listen for certain logs:

~~~ ruby
client.listen_for_log /power=(?<power>[0-9]+)/ do |listener|

    # same pop behaviors as for event listener

    log = listener.pop

    # pp log
    # > ['1234: Radio: tx: power=42', match_obj]
    # puts log[1][:power]
    # > 42

end

listener = client.listen_for_log /power=(?<power>[0-9]+)/

log = listener.pop

client.stop_listening(listener)

~~~

Listen for all logs:
