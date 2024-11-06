#include "bramble.hpp"

#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <boost/asio.hpp>

#define LOG(...) do{printf(__VA_ARGS__);printf("\n");fflush(stdout);}while(0);

class Host : public Bramble::Server::Host {
public:

    using handler_fn = std::function<void(Bramble::Server::Command&, const Bramble::Argument&)>;

    Host(boost::asio::io_context& ctx, uint16_t ip_port)
        :
        endpoint(tcp::v4(), ip_port),
        acceptor(ctx, endpoint),
        socket(ctx),
        cli_server(nullptr)
    {
        input.fill(0);
        acceptor.set_option(tcp::acceptor::reuse_address(true));
        do_accept();
    }

    void add_handler(const char *name, const handler_fn& handler)
    {
        list.emplace_back(name, handler);
    }

    bool call(Bramble::Server::Command& self, const Bramble::Argument& args)
    {
        bool retval = false;

        for(auto iter = list.begin(); iter != list.end(); ++iter){

            if(Bramble::StringView(iter->name.c_str()) == self.name()){

                iter->handler(self, args);
                retval = true;
                break;
            }
        }

        return retval;
    }

    void put_char(char c)
    {
        output += c;

        if((c == '\n') || (output.size() > 512)){

            drain();
        }
    }

    void drain()
    {
        if(output.size() == 0){

            // nothing to send
        }
        else if(!socket.is_open()){

            // nowhere to send
        }
        else if(send_queue.empty()){

            send_queue.push_back(output);

            do_socket_write();
        }
        else{

            send_queue.push_back(output);
        }

        output.clear();
    }

    uint16_t get_port() const
    {
        return acceptor.local_endpoint().port();
    }

    void set_server(Bramble::Server& server)
    {
        cli_server = &server;
    }

private:

    struct Record {

        Record(const char *name, const handler_fn& handler)
            :
            name(name),
            handler(handler)
        {}

        std::string name;
        handler_fn handler;
    };

    std::list<Record> list;

    std::deque<std::string> send_queue;

    using tcp = boost::asio::ip::tcp;

    std::string output;

    tcp::endpoint endpoint;
    tcp::acceptor acceptor;
    tcp::socket socket;

    std::array<char, 1024> input;

    Bramble::Server *cli_server;

    void do_accept()
    {
        LOG("%u", (unsigned)get_port())

        acceptor.async_accept(
            [this](std::error_code ec, tcp::socket s)
            {
                if(!ec){

                    LOG("do_accept: accepted connection")

                    socket = std::move(s);

                    do_socket_read();
                }
                else{

                    LOG("do_accept: acceptor error, shutting down")
                }
            }
        );
    }

    void do_socket_read()
    {
        socket.async_read_some(
            boost::asio::buffer(input.data(), input.size()),
            [this](std::error_code ec, size_t size)
            {
                if(!ec){

                    LOG("do_socket_read: %uB", (unsigned)size)

                    if(this->cli_server != nullptr){

                        this->cli_server->process((const char *)input.data(), size);
                    }

                    do_socket_read();
                }
                else{

                    LOG("do_socket_read: socket error, closing...")

                    socket.close();

                    do_accept();
                }
            }
        );
    }

    void do_socket_write()
    {
        boost::asio::async_write(socket,
            boost::asio::buffer(send_queue.front().data(), send_queue.front().size()),
            [this](std::error_code ec, size_t size)
            {
                if(!ec){

                    LOG("do_socket_write: wrote %u bytes", (unsigned)size)

                    send_queue.pop_front();

                    if(!send_queue.empty()){

                        do_socket_write();
                    }
                }
                else{

                    socket.close();
                }
            }
        );
    }
};

int main(int, char **)
{
    boost::asio::io_context ctx;
    Host host(ctx, 0);
    Bramble::Server server(host);
    host.set_server(server);

    host.add_handler("echo", [](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        Bramble::Encoder encoder(cmd.ack_with_arg());

        for(auto iter : args){

            encoder.put_string(iter);
            encoder.space();
        }
    });

    for(;;){

        ctx.run();
    }

    return 0;
}
