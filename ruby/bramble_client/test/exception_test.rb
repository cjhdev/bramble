describe File.basename(__FILE__, ".rb") do

  describe "any exception in listener block" do

    let(:logger){Logger.new(STDOUT)}
    let(:client){BrambleClient.new(logger: logger)}

    class AnyException < StandardError
    end

    it "unwinds and passes through" do

      assert_raises AnyException do

        client.listen_for_event('some_event') do |listener|

          raise AnyException

        end

      end

    end

  end

end
