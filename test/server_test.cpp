#include "gtest/gtest.h"

#include "bramble.hpp"

#include <list>
#include <string>

class Host : public Bramble::Server::Host {
public:

    std::string output;
    std::string input;

    using handler_fn = std::function<void(Bramble::Server::Command&, const Bramble::Argument&)>;

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
        output.push_back(c);
    }

    virtual GetCharStatus get_char(char& c)
    {
        GetCharStatus retval;

        if(input.size() == 0){

            retval = GetCharStatus::Blocked;
        }
        else{

            c = input.front();
            input.erase(0, 1);

            retval = GetCharStatus::Ok;
        }

        return retval;
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
};

TEST(Server, shall_ignore_empty_command)
{
    Host host;
    Bramble::Server server(host);

    std::string input("\r");

    server.process(input.data(), input.size());

    std::string expected("");

    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_not_acknowledge_zero_token)
{
    Host host;
    Bramble::Server server(host);

    std::string input(" \r");

    server.process(input.data(), input.size());

    std::string expected("CMD: \r\n");

    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_nak_unknown_command)
{
    Host host;
    Bramble::Server server(host);

    std::string input("test hello world\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("NAK:test unknown_command\r\n");

    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_ignore_too_long)
{
    Host host;
    Bramble::Server server(host, 10);

    std::string input("test hello world i am too long\r");

    server.process(input.data(), input.size());

    std::string expected("");

    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_implicit_ack)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        ASSERT_EQ(Bramble::StringView("test"), cmd.name());
        ASSERT_TRUE(args.empty());

        called = true;
    });

    std::string input("test\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("ACK:test\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_explicit_ack)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        ASSERT_EQ(Bramble::StringView("test"), cmd.name());
        ASSERT_TRUE(args.empty());

        called = true;
        cmd.ack();
    });

    std::string input("test\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("ACK:test\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_ack_with_arg)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        ASSERT_EQ(Bramble::StringView("test"), cmd.name());
        ASSERT_TRUE(args.empty());

        Bramble::Encoder(cmd.ack_with_arg()).put_string("token");

        called = true;
    });

    std::string input("test\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("ACK:test token\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_handle_invoke_id)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        //ASSERT_EQ(Bramble::StringView("test"), cmd.name());
        //ASSERT_TRUE(args.empty());

        called = true;
    });

    std::string input("test#42 arg\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("ACK:test#42\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}

TEST(Server, shall_handle_input_arg)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        ASSERT_EQ(Bramble::StringView("test"), cmd.name());
        ASSERT_FALSE(args.empty());
        ASSERT_EQ(Bramble::StringView("token"), args.front());

        called = true;
    });

    std::string input("test token\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("ACK:test\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}


TEST(Server, nak_shall_not_ack)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        //ASSERT_FALSE(cmd.is_nak());

        cmd.nak("no_reason");

        //ASSERT_TRUE(cmd.is_nak());

        cmd.ack();

        called = true;
    });

    std::string input("test\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("NAK:test no_reason\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}

TEST(Server, ack_shall_not_nak)
{
    Host host;
    Bramble::Server server(host);

    bool called = false;

    host.add_handler("test", [&called](Bramble::Server::Command& cmd, const Bramble::Argument& args){

        //ASSERT_FALSE(cmd.is_nak());

        cmd.ack();

        //ASSERT_TRUE(cmd.is_nak());

        cmd.nak("no_reason");

        called = true;
    });

    std::string input("test\r");

    server.process(input.data(), input.size());

    std::string expected("CMD:");
    expected.append(input);
    expected.append("\n");
    expected.append("ACK:test\r\n");

    ASSERT_TRUE(called);
    ASSERT_EQ(expected, host.output);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
