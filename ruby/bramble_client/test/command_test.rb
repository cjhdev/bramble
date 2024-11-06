describe File.basename(__FILE__, ".rb") do

  let(:logger){Logger.new(STDOUT)}

  describe "input format" do

    let(:client){BrambleClient.new(command_timeout: 0.5)}
    let(:queue){BrambleClient::TimeoutQueue.new}

    before do

      client.set_output_handler do |out|

        queue.push out

      end

    end

    it "will accept leading whitespace" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD: test\r\n"

        client.input "ACK: test\r\n"

      end

      client.command("test")

    end

    it "will accept no leading whitespace" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD:test\r\n"

        client.input "ACK:test\r\n"

      end

      client.command("test")

    end

  end

  describe "format exceptions" do

    let(:client){BrambleClient.new(command_timeout: 0.5)}
    let(:queue){BrambleClient::TimeoutQueue.new}

    before do

      client.set_output_handler do |out|

        queue.push out

      end

    end

    it "raises response timeout if no CMD" do

      assert_raises BrambleClient::ResponseTimeoutError do

        client.command("test")

      end

    end

    it "raises response timeout if CMD name not match" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD: different_test\r\n"

      end

      assert_raises BrambleClient::ResponseTimeoutError do

        client.command("test")

      end

    end

    it "raises timeout if no CMD and ACK/NAK" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD: test\r\n"

      end

      assert_raises BrambleClient::ResponseTimeoutError do

        client.command("test")

      end

    end

    it "raises response timeout if ACK/NAK name not match" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD: test\r\n"
        client.input "ACK: different_test\r\n"

      end

      assert_raises BrambleClient::ResponseTimeoutError do

        client.command("test")

      end

    end

    it "raises format error if CMD is not first" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "ACK: test\r\n"

      end

      assert_raises BrambleClient::ResponseFormatError do

        client.command("test")

      end

    end

    it "raises format error if NAK/ACK is not second" do

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD: test\r\n"

        client.input "CMD: test\r\n"

      end

      assert_raises BrambleClient::ResponseFormatError do

        client.command("test")

      end

    end

    it "raises response error if NAK is second" do

      the_error_message = "nothing"

      Thread.new do

        queue.pop(timeout: 1)

        client.input "CMD: test\r\n"

        client.input "NAK: test #{the_error_message}\r\n"

      end

      error = assert_raises BrambleClient::ResponseError do |e|

        client.command("test")

      end

      assert_equal the_error_message, error.to_s

    end

  end

end
