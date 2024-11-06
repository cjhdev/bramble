describe File.basename(__FILE__, ".rb") do

  let(:logger){Logger.new(STDOUT)}
  let(:client){BrambleClient.new}

  describe "blocked on open listener" do

    it "raises close" do

      assert_raises BrambleClient::ClosedError do

        client.listen_for_event('some_event') do |listener|

          Thread.new do

            sleep 0.2

            client.close

          end

          listener.pop

        end

      end

    end

  end

  describe "try to block on closed listener" do

    it "raises close" do

      assert_raises BrambleClient::ClosedError do

        client.listen_for_event('some_event') do |listener|

          client.close

          listener.pop

        end

      end

    end

  end

  describe "try to input to closed listener" do

    it "does nothing" do

      client.listen_for_event('some_event') do |listener|

        client.close
        client.input "EVT: some_event"

      end

    end

  end

end
