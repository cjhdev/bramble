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

#ifndef BRAMBLE_GET_OPT_H_INCLUDED
#define BRAMBLE_GET_OPT_H_INCLUDED

#include "bramble_string_view.hpp"
#include "bramble_argument.hpp"

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace Bramble {

    /** An option parser
     *
     *
     * */
    class GetOpt {
    public:

        /** define whether or not an option can have a value */
        enum class Value {

            Optional,   ///< continue parsing with and without a value
            None,       ///< fail parsing if option has a value
            Required    ///< fail parsing if option does not have a value
        };

        /** definition of an option */
        struct Option {

            const char *s;                  ///< long format option name (nullptr if not used)
            char c;                         ///< short format option name (0 if not used)
            Value value;                    ///< instruct parser on how to handle an option value

            /** Successful match handler
             *
             * @param[in] self      the GetOpt instance
             *
             * */
            void (*handler)(GetOpt& self);
        };

        /** Create an option parser instance
         *
         * @param[in] begin     iterator to first token
         * @param[in] end       iterator to end of tokens
         * @param[in] options   pointer to table of options
         * @param[in] size      number of options in table
         *
         * */
        GetOpt(Argument::iterator begin, Argument::iterator end, const Option *options=nullptr, size_t size=0)
            :
            argv_begin(begin),
            argv_end(end),
            options_begin(options),
            options_end(options + size),
            a(begin),
            opt(nullptr),
            ctx(nullptr),
            status(Status::Active),
            state(&Next::instance())
        {
        }

        /** call to stop parsing now
         *
         * */
        void stop()
        {
            state->finish(*this, Status::Ok);
        }

        /** handle the next option (if there is one) */
        void next()
        {
            state->next(*this);
        }

        /** check if parser has finished
         *
         * A parser can finish successfully or unsuccessfully, the finished
         * status simply means that further calls to next() will have no effect.
         *
         * @retval true     parser has finished
         * @retval false    call next() to try to parse next option
         *
         *  */
        bool finished() const
        {
            return status != Status::Active;
        }

        /** Check if parser finished on an unknown option
         *
         * @retval true     option is unknown
         * @retval false
         *
         * */
        bool unknown() const
        {
            return status == Status::Unknown;
        }

        /** Check if parser finished on a known option that is missing a required value
         *
         * @retval true     option is missing a required value
         *
         * */
        bool missing() const
        {
            return status == Status::Missing;
        }

        /** Check if parser finished on a known option that is not supposed to have an associated value
         *
         * @retval true     option has a value that is not expected
         *
         *
         * */
        bool unexpected() const
        {
            return status == Status::Unexpected;
        }

        /** the current argument within argv
         *
         * @return Argument::iterator
         *
         * */
        const Argument::iterator arg() const
        {
            return a;
        }

        /** Get the current option
         *
         * */
        const Option *option() const
        {
            return opt;
        }

        /** Get the current option name
         *
         * */
        StringView name() const
        {
            return n;
        }

        /** Get the current option value
         *
         * */
        StringView value() const
        {
            return v;
        }

        /** Get user pointer from this instance
         *
         * @return   user pointer
         *
         * */
        void *get_ctx() const
        {
            return ctx;
        }

        /** Attach user pointer to this instance
         *
         * @param[in] ctx   user pointer
         *
         * */
        void set_ctx(void *ctx)
        {
            this->ctx = ctx;
        }

    private:

        Argument::iterator argv_begin;
        Argument::iterator argv_end;

        const Option *options_begin;
        const Option *options_end;

        Argument::iterator a;

        StringView v;
        StringView n;
        StringView::iterator n_iter;

        const Option *opt;

        void *ctx;

        enum class Status {

            Active,
            Ok,
            Unknown,
            Unexpected,
            Missing
        };

        Status status;

        class State {
        public:
            virtual ~State(){}
            virtual void before(GetOpt&) const { }
            virtual void after(GetOpt&) const { }
            virtual void next(GetOpt&) const { }
            virtual void finish(GetOpt& self, Status status) const
            {
                self.status = status;
                self.set_state(Finished::instance());
            }
        };

        class Next : public State {
        public:
            static const State& instance()
            {
                static Next inst;
                return inst;
            }
            void next(GetOpt& self) const
            {
                self.opt = nullptr;
                self.v = StringView();
                self.n = StringView();

                if(self.a == self.argv_end){

                    finish(self, Status::Ok);
                }
                else if(self.a->empty()){

                    finish(self, Status::Ok);
                }
                // not an option
                else if(((*self.a)[0] != '-') || (self.a->size() == 1)){

                    finish(self, Status::Ok);
                }
                // '-a' short option
                else if((*self.a)[1] != '-'){

                    self.set_state(ShortOption::instance());
                    self.next();
                }
                // '--' end of options
                else if(self.a->size() == 2){

                    self.a++;
                    finish(self, Status::Ok);
                }
                // '--something' long option
                else{

                    self.n = self.a->substr(2, self.a->find_first_of('=')-2);

                    if(!self.lookup_long_option(self.n, &self.opt)){

                        finish(self, Status::Unknown);
                    }
                    else if(self.opt->value == Value::Required){

                        if(self.a->find_first_of('=') != self.a->npos){

                            self.v = self.a->substr(self.a->find_first_of('=')+1);
                            self.a++;
                            self.call_handler();
                        }
                        else if((self.a+1) == self.argv_end){

                            finish(self, Status::Missing);
                        }
                        else{

                            self.a++;
                            self.v = *self.a;
                            self.a++;
                            self.call_handler();
                        }
                    }
                    else if(self.opt->value == Value::Optional){

                        if(self.a->find_first_of('=') != self.a->npos){

                            self.v = self.a->substr(self.a->find_first_of('=')+1);
                        }

                        self.a++;
                        self.call_handler();
                    }
                    // Value::None
                    else{

                        if(self.a->find_first_of('=') != self.a->npos){

                            self.v = self.a->substr(self.a->find_first_of('=')+1);

                            finish(self, Status::Unexpected);
                        }
                        else{

                            self.a++;
                            self.call_handler();
                        }
                    }
                }
            }
        };

        class ShortOption : public State {
        public:
            static const State& instance()
            {
                static ShortOption inst;
                return inst;
            }
            void before(GetOpt& self) const
            {
                self.n_iter = self.a->begin()+1;
            }
            void next(GetOpt& self) const
            {
                self.opt = nullptr;
                self.n = StringView();
                self.v = StringView();

                if(self.n_iter == self.a->end()){

                    self.a++;
                    self.set_state(Next::instance());
                    self.next();
                }
                else{

                    auto offset = size_t(self.n_iter - self.a->begin());
                    auto equals = self.a->find_first_of('=');

                    self.n = self.a->substr(offset, 1);

                    if(!self.lookup_short_option(self.n.front(), &self.opt)){

                        finish(self, Status::Unknown);
                    }
                    else if(self.opt->value == Value::Required){

                        if(equals == (offset+1)){

                            self.v = self.a->substr(equals+1);
                            self.a++;
                            self.set_state(Next::instance());
                            self.call_handler();
                        }
                        else if((self.n_iter+1) != self.a->end()){

                            finish(self, Status::Missing);
                        }
                        else if((self.a+1) == self.argv_end){

                            finish(self, Status::Missing);
                        }
                        else{

                            self.a++;
                            self.v = *self.a;
                            self.a++;
                            self.set_state(Next::instance());
                            self.call_handler();
                        }
                    }
                    else if(self.opt->value == Value::Optional){

                        if(equals == (offset+1)){

                            self.v = self.a->substr(equals+1);
                            self.a++;
                            self.set_state(Next::instance());
                            self.call_handler();
                        }
                        else if((self.n_iter+1) == self.a->end()){

                            self.a++;
                            self.set_state(Next::instance());
                            self.call_handler();
                        }
                        else{

                            // remain in chain
                            self.n_iter++;
                            self.call_handler();
                        }
                    }
                    // Value::None
                    else{

                        if(equals == (offset+1)){

                            self.v = self.a->substr(equals+1);

                            finish(self, Status::Unexpected);
                        }
                        else if((self.n_iter+1) == self.a->end()){

                            self.a++;
                            self.set_state(Next::instance());
                            self.call_handler();
                        }
                        else{

                            // remain in chain
                            self.n_iter++;
                            self.call_handler();
                        }
                    }
                }
            }
        };

        class Finished : public State {
        public:
            static const State& instance()
            {
                static Finished inst;
                return inst;
            }
        };

        const State *state;

        void set_state(const State& value)
        {
            state->after(*this);
            state = &value;
            state->before(*this);
        }

        bool lookup_short_option(char c, const Option **output) const
        {
            bool retval = false;

            for(auto iter = options_begin; iter != options_end; ++iter){

                if(iter->c == c){

                    *output = iter;
                    retval = true;
                    break;
                }
            }

            return retval;
        }

        bool lookup_long_option(const StringView& s, const Option **output) const
        {
            bool retval = false;

            for(auto iter = options_begin; iter != options_end; ++iter){

                if(s.compare(iter->s) == 0){

                    *output = iter;
                    retval = true;
                    break;
                }
            }

            return retval;
        }

        void call_handler()
        {
            if(opt->handler != nullptr){

                opt->handler(*this);
            }
        }
    };
};

#endif
