describe File.basename(__FILE__, ".rb") do

  let(:logger){Logger.new(STDOUT)}
  let(:client){BrambleClient.new}

  it "timeout if log pattern not matched" do

    assert_raises BrambleClient::ListenTimeoutError do

      client.listen_for_log(/power=(?<power>[0-9]+)/) do |listener|

        Thread.new do

          client.input "LOG: some other log message\r\n"

        end

        listener.pop(timeout: 0.5)

      end

    end

  end

  it "timeout if no logs at all" do

    assert_raises BrambleClient::ListenTimeoutError do

      client.listen_for_log(/power=(?<power>[0-9]+)/) do |listener|

        listener.pop(timeout: 0.5)

      end

    end

  end

  it "matches log by pattern" do

    msg = "1234: Radio: tx: power=42"

    client.listen_for_log(/power=(?<power>[0-9]+)/) do |listener|

      Thread.new do

        client.input "LOG: #{msg}\r\n"

      end

      rx_msg, rx_match = listener.pop(timeout: 0.5)

      assert_equal msg, rx_msg
      assert_equal "42", rx_match[:power]

    end

  end


end
