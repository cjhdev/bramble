/* Copyright (c) 2024 Cameron Harper
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef BRAMBLE_SERVER_H_INCLUDED
#define BRAMBLE_SERVER_H_INCLUDED

#include "bramble_stream.hpp"
#include "bramble_get_opt.hpp"
#include "bramble_encoder.hpp"
#include "bramble_decoder.hpp"
#include "bramble_argument.hpp"
#include "bramble_string_view.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <cctype>

namespace Bramble {

    /** A Bramble server
     *
     * */
    class Server {
    public:

        /** Represents the command that is being handled
         *
         * */
        class Command {
        public:

            /// @private
            Command(Server& server)
                :
                server(server)
            {}

            /** Command name
             *
             * @return command name
             *
             * */
            StringView name()
            {
                return server.name;
            }

            /** Initiate an ACK
             *
             * */
            void ack()
            {
                (void)server.state->ack(server);
            }

            /** Initiate an ACK that will be followed by arguments
             *
             * @return output stream
             *
             * */
            Stream& ack_with_arg()
            {
                return Encoder(server.state->ack(server)).space().s;
            }

            /** Initiate a NAK
             *
             * @param[in] reason    reason for NAK
             *
             * */
            void nak(const char *reason)
            {
                return server.state->nak(server, reason);
            }

            /** Force server to end the ACK/NAK line and drain the output now rather than on
             * return from the handler.
             *
             * */
            void end()
            {
                server.state->end(server);
            }

            /** Get the user pointer that was attached to server instance
             *
             * */
            void *ctx()
            {
                return server.get_ctx();
            }

            /** The server instance */
            Server& server;
        };

        /** Server host interface
         *
         * Anything a server instance may want from the host.
         *
         * This class will need to be subclassed when porting to a new host.
         *
         * */
        class Host {
        public:

            virtual ~Host(){}

            /// called everytime a line is received
            virtual void line_was_rx()
            {}

            /// called everytime a line is sent
            virtual void line_was_tx()
            {}

            enum class GetCharStatus {

                Ok,
                Blocked,
                Error
            };

            /** put a character to the transport layer
             *
             * @param[in] c     character
             *
             * */
            virtual void put_char(char c)
            {
                (void)c;
            };

            /** block until output buffer has been emptied */
            virtual void drain()
            {};

            /** get a character from the transport layer
             *
             * @param[out] c        output character
             *
             * @retval GetCharStatus::Ok
             * @retval GetCharStatus::Error
             * @retval GetCharStatus::Blocked
             *
             * */
            virtual GetCharStatus get_char(char& c)
            {
                (void)c;
                return GetCharStatus::Blocked;
            };

            /** call to evaluate the status code
             *
             * @param[in] status
             *
             * @retval true     character is valid
             *
             * */
            static bool get_char_status_ok(GetCharStatus status)
            {
                return (status == GetCharStatus::Ok);
            }

            /** Lookup and execute a command handler by name
             *
             * @note The command name is accessible from Command::name()
             *
             * @param[in] cmd       the command being handled
             * @param[in] args      arguments
             *
             * @retval true         handler exists and was called
             * @retval false        no handler exists for command name
             *
             * */
            virtual bool call(Command& cmd, const Argument& args)
            {
                (void)cmd;
                (void)args;
                return false;
            }
        };

        /** Create a new server instance
         *
         * @param[in] host      host interface
         * @param[in] max_line  largest line server can receive
         *
         * */
        Server(Host& host, size_t max_line = 1024)
            :
            host(host),
            output(*this),
            state(&Idle::instance()),
            size(0),
            end_offset(max_line)
        {
            buffer = new char[max_line+1];

            (void)memset(buffer, 0, max_line+1);
        }

        /** Destroy this server
         *
         * */
        ~Server()
        {
            delete buffer;
        }

        /** Process input characters from HostInterface::get_char()
         *
         * Most useful if your transport layer has a queue that needs to be polled for
         * updates.
         *
         * @see process(const char*,size_t) if your server receives strings directly
         *
         * */
        void process()
        {
            char c;

            while(host.get_char_status_ok(host.get_char(c))){

                state->input(*this, c);
            }
        }

        /** Process input characters direct from buffer
         *
         * Most useful if your transport layer delivers messages directly into your application.
         *
         * @see alternative to process() if your server polls an existing queue infrastructure
         *
         * */
        void process(const char *buffer, size_t size)
        {
            for(auto iter = buffer; iter != (buffer + size); ++iter){

                state->input(*this, *iter);
            }
        }

        /** Block until output buffer becomes empty */
        void drain()
        {
            output.drain();
        }

        /** Attach a user pointer which can be accessed in command handler
         *
         * */
        void set_ctx(void *ctx)
        {
            this->ctx = ctx;
        }

        using ArgumentClosure = std::function<void(Bramble::Stream&)>;

        /** send an event
         *
         * @param[in] name     event name
         *
         * */
        void event(const char *name)
        {
            Encoder(output).put_string("EVT: ").put_string(name);
            put_line_end();
        }

        /** @copydoc event(const char *)
         *
         * @param[in] fn    closure for additional arguments
         *
         *  */
        void event(const char *name, const ArgumentClosure& fn)
        {
            Encoder(output).put_string("EVT: ").put_string(name).space();
            fn(output);
            put_line_end();
        }

        /** Send a log message
         *
         * @param[in] s     message
         *
         * */
        void log(const char *s)
        {
            Encoder(output).put_string("LOG: ").put_string(s);
            put_line_end();
        }

        /** @copydoc log(const char *)
         *
         * @param[in] fn    closure for additional arguments
         *
         * */
        void log(const char *s, const ArgumentClosure& fn)
        {
            Encoder(output).put_string("LOG: ").put_string(s).space();
            fn(output);
            put_line_end();
        }

        /** Send without a prefix
         *
         * @param[in] s     message
         *
         * */
        void no_prefix(const char *s)
        {
            Encoder(output).put_string(s);
            put_line_end();
        }

        /** @copydoc no_prefix(const char *)
         *
         * @param[in] fn    closure for additional arguments
         *
         * */
        void no_prefix(const char *s, const ArgumentClosure& fn)
        {
            Encoder(output).put_string(s);
            fn(output);
            put_line_end();
        }

        /** Get the maximum line size server able to echo and acknowledge
         *
         * @return maximum line size
         *
         * */
        constexpr size_t max_line_size() const
        {
            return end_offset;
        }

    private:

        class State {
        public:
            virtual void before(Server&) const {}
            virtual void after(Server&) const {}

            virtual void input(Server&, char) const {}

            virtual Stream& ack(Server& self) const { return self.output; }
            virtual void nak(Server&, const char *) const {}
            virtual void end(Server&) const {}
        };

        class Idle : public State {
        public:

            static State& instance(){
                static Idle inst;
                return inst;
            }

            void before(Server& self) const
            {
                self.size = 0;
                self.buffer[self.size] = 0;
                self.name = StringView();
            }

            void input(Server& self, char c) const
            {
                if(std::isprint(c)){

                    if(self.size < self.end_offset){

                        self.buffer[self.size] = c;
                        self.size++;
                        self.buffer[self.size] = 0;
                    }
                    else{

                        self.set_state(TooLong::instance());
                    }
                }
                else if((c == '\r') && (self.size > 0U)){

                    self.set_state(Handle::instance());
                }
                else{

                    // keep listening
                }
            }
        };

        class Handle : public State {

            static void detect_command_name(Server& self, Argument& args)
            {
                bool matched = true;

                self.full_name = Decoder::strip(args.pop_front());

                auto id_offset = self.full_name.find_first_of('#');

                self.name = self.full_name.substr(0, id_offset);

                if(id_offset == 0){

                    matched = false;
                }
                else if(id_offset != StringView::npos){

                    self.invoke_id = self.full_name.substr(id_offset + 1);
                }
                else{

                    self.invoke_id = StringView();
                }

                // [a-zA-Z0-9_]+
                for(auto iter = self.name.begin(); iter != self.name.end(); ++iter){

                    if(!std::isupper(*iter) && !std::islower(*iter) && !std::isdigit(*iter) && (*iter != '_')){

                        matched = false;
                        break;
                    }
                }

                // [0-9]+
                if(self.invoke_id.empty()){

                    if(id_offset != StringView::npos){

                        matched = false;
                    }
                }
                else{

                    for(auto iter = self.invoke_id.begin(); iter != self.invoke_id.end(); ++iter){

                        if(!std::isdigit(*iter)){

                            matched = false;
                            break;
                        }
                    }
                }

                if(!matched){

                    self.name = self.full_name;
                    self.invoke_id = StringView();
                }
            }

        public:

            static State& instance()
            {
                static Handle inst;
                return inst;
            }

            void before(Server& self) const
            {
                self.host.line_was_rx();

                self.put_cmd();
                self.put_line_end();

                self.host.line_was_tx();

                // will mutate contents of self.buffer into sequence of null-terminated strings
                Argument args(self.buffer, self.buffer, self.end_offset);
                Command cmd(self);

                if(!args.empty()){

                    detect_command_name(self, args);

                    if(!self.host.call(cmd, args)){

                        self.put_nak("unknown_command");
                        self.put_line_end();
                        self.host.line_was_tx();
                    }
                    else{

                        // default response is always ack
                        if(self.state == &Handle::instance()){

                            self.put_ack();
                            self.put_line_end();
                            self.host.line_was_tx();
                        }
                    }
                }

                self.set_state(Idle::instance());
            }

            Stream& ack(Server& self) const
            {
                self.set_state(Responding::instance());
                self.put_ack();

                return self.output;
            }

            void nak(Server& self, const char *reason) const
            {
                self.set_state(Responding::instance());
                self.put_nak(reason);
            }

            void end(Server& self) const
            {
                self.set_state(Responding::instance());
                self.state->end(self);
            }
        };

        class Responding : public State {
        public:
            static State& instance()
            {
                static Responding inst;
                return inst;
            }

            Stream& ack(Server& self) const
            {
                return self.output;
            }

            void end(Server& self) const
            {
                self.set_state(Idle::instance());
            }

            void after(Server& self) const
            {
                self.put_line_end();
                self.host.line_was_tx();
            }
        };

        class TooLong : public State {
        public:

            static State& instance()
            {
                static TooLong inst;
                return inst;
            }

            void input(Server& self, char c) const
            {
                if(c == '\r'){

                    self.set_state(Idle::instance());
                }
            }
        };

        // server output stream
        class Output : public Stream {
        public:

            Output(Server& server)
                :
                server(&server)
            {
            }

            Output()
                :
                server(nullptr)
            {
            }

            size_t write(const void *buffer, size_t size)
            {
                if(server != nullptr){

                    auto begin = (const uint8_t *)buffer;
                    auto end = begin + size;

                    for(auto iter = begin; iter != end; ++iter){

                        server->host.put_char(*iter);
                    }
                }

                return size;
            }

            void drain()
            {
                if(server != nullptr){

                    server->host.drain();
                }
            }

        private:

            Server *server;
        };

        Host& host;

        Output output;

        const State *state;

        void *ctx;

        void set_state(const State& value)
        {
            state->after(*this);
            state = &value;
            state->before(*this);
        }

        char *buffer;
        size_t size;
        const size_t end_offset;

        StringView name;
        StringView full_name;
        StringView invoke_id;

        void put_cmd()
        {
            Encoder(output)
                .put_string("CMD:")
                .put_string(buffer);
        }

        void put_nak(const char *msg)
        {
            Encoder(output)
                .put_string("NAK:")
                .put_string(full_name)
                .space()
                .put_string(msg);
        }

        void put_ack()
        {
            Encoder(output)
                .put_string("ACK:")
                .put_string(full_name);
        }

        void put_line_end()
        {
            Encoder(output).put_string("\r\n");
        }

        void *get_ctx()
        {
            return ctx;
        }
    };
};

#endif
