describe File.basename(__FILE__, ".rb") do

  let(:logger){Logger.new(STDOUT)}
  let(:client){BrambleClient.new}

  it "at least one event is required to listen" do

    assert_raises ArgumentError do

      client.listen_for_event do |listener|

      end

    end

  end

  it "timeout if no event received" do

    assert_raises BrambleClient::ListenTimeoutError do

      client.listen_for_event('some_event') do |listener|

        listener.pop(timeout: 0.5)

      end

    end

  end

  it "returns event" do

    client.listen_for_event('some_event') do |listener|

      Thread.new do
        client.input "EVT: some_event\r\n"
      end

      listener.pop(timeout: 0.5)

    end

  end

  it "ignores other events" do

    assert_raises BrambleClient::ListenTimeoutError do

      client.listen_for_event('some_event') do |listener|

        Thread.new do
          client.input "EVT: some_other_event\r\n"
        end

        listener.pop(timeout: 0.5)

      end

    end

  end

  it "will not match pattern of event arguments" do

    assert_raises BrambleClient::ListenTimeoutError do

      client.listen_for_event('some_event') do |listener|

        Thread.new do
          client.input "EVT: some_other_event some_event\r\n"
        end

        listener.pop(timeout: 0.5)

      end

    end

  end

  it "can match more than one event by name" do

    client.listen_for_event('some_event', 'some_other_event') do |listener|

      Thread.new do
        client.input "EVT: some_event\r\n"
        client.input "EVT: some_other_event\r\n"
      end

      evt = listener.pop(timeout: 0.5)

      assert_equal 'some_event', evt.first

      evt = listener.pop(timeout: 0.5)

      assert_equal 'some_other_event', evt.first

    end

  end

  it "can match more than one event by pattern" do

    client.listen_for_event(/some[a-z_]+event/) do |listener|

      Thread.new do
        client.input "EVT: some_event\r\n"
        client.input "EVT: some_other_event\r\n"
      end

      evt = listener.pop(timeout: 0.5)

      assert_equal 'some_event', evt.first

      evt = listener.pop(timeout: 0.5)

      assert_equal 'some_other_event', evt.first

    end

  end

end
