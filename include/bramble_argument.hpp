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

#ifndef BRAMBLE_ARGUMENT_H_INCLUDED
#define BRAMBLE_ARGUMENT_H_INCLUDED

#include "bramble_string_view.hpp"
#include "bramble_buffer_stream.hpp"

#include <cstddef>

namespace Bramble {

    /** A container of argument tokens
     *
     * */
    class Argument {
    public:

        /** Create an Argument container from a null-terminated input
         *
         * The tokens in the input will be mutated into a sequence of null-terminated
         * strings (one per token). A working buffer is required to store this new format.
         *
         * The working buffer can be the same memory as the input buffer since the size
         * of the new format is guaranteed to be equal to or smaller than the input (including the null character!).
         *
         * Consequence of a too-small working buffer is that not all tokens will accounted for
         * and accessible.
         *
         * @param[in] s         null-terminated input buffer
         * @param[in] working   working buffer (can be same memory as s)
         * @param[in] max       maximum size of working buffer
         *
         * */
        Argument(const char *s, char *working, size_t max)
            :
            buffer(working),
            max(0),
            count(0)
        {
            StringView input(s);
            BufferStream output(working, max);

            size_t token_size = 0;

            bool escape = false;
            bool quote = false;

            char quote_char;

            for(auto iter = input.begin(); iter != input.end(); ++iter){

                if(escape){

                    escape = false;
                    put_char(output, *iter);
                }
                else if(quote){

                    if(quote_char == *iter){

                        quote = false;
                    }
                    else{

                        put_char(output, *iter);
                        token_size++;
                    }
                }
                else if(*iter == '\\'){

                    escape = true;
                }
                else if(*iter == ' '){

                    if(token_size > 0){

                        put_char(output, 0);
                        token_size = 0;
                    }
                }
                else if((*iter == '\'') || (*iter == '"')){

                    quote_char = *iter;
                    quote = true;
                }
                else{

                    put_char(output, *iter);
                    token_size++;
                }
            }

            if(!quote && (token_size > 0)){

                put_char(output, 0);
            }

            if((this->max == 0) && (working != nullptr) && (max > 0)){

                working[0] = 0;
            }
        }

        /** Create an Argument container from a vector of null-terminated strings
         *
         * Consequence of a too-small working buffer is that not all tokens will accounted for
         * and accessible.
         *
         * @param[in] argc      size of argv
         * @param[in] argv      buffer of tokens
         * @param[in] working   working buffer
         * @param[in] max       maximum size of working buffer
         *
         * */
        Argument(size_t argc, const char **argv, char *working, size_t max)
            :
            buffer(working),
            max(0),
            count(argc)
        {
            BufferStream output(working, max);

            for(auto iter = argv; iter != (argv + argc); ++iter){

                StringView v(*iter);

                for(auto i = v.begin(); i != v.end(); ++i){

                    put_char(output, *i);
                }

                if(!v.empty()){

                    put_char(output, 0);
                }
            }
        }

        typedef StringView value_type;

        class iterator {
        public:

            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = StringView;
            using pointer           = const StringView*;
            using reference         = const StringView&;

            iterator(const Argument& arg)
                :
                arg(&arg),
                offset(0),
                v(arg.buffer)
            {
            }

            iterator(const Argument& arg, bool)
                :
                arg(&arg),
                offset(arg.max),
                v(arg.buffer, 0)
            {
            }

            iterator& operator++()
            {
                if(offset < arg->max){

                    offset += v.size();
                    offset++;
                }

                if(offset < arg->max){

                    v = StringView(arg->buffer + offset);
                }
                else{

                    v = StringView();
                }

                return *this;
            }

            iterator operator++(int)
            {
                auto retval = *this;
                ++(*this);
                return retval;
            }

            iterator operator+(size_t n) const
            {
                auto retval = *this;

                for(size_t i=0; i < n; ++i){

                    ++retval;
                }

                return retval;
            }

            StringView operator*() const
            {
                return v;
            }

            const StringView *operator->() const
            {
                return &v;
            }

            bool operator==(const iterator& other) const
            {
                //return v == other.v;
                return offset == other.offset;
            }

            bool operator!=(const iterator& other) const
            {
                //return v != other.v;
                return offset != other.offset;
            }

        private:

            const Argument *arg;
            size_t offset;
            StringView v;
        };

        typedef iterator const_iterator;

        /** Returns an iterator to the beginning
         *
         * */
        iterator begin() const
        {
            return cbegin();
        }

        /** Returns an iterator to the end
         *
         * */
        iterator end() const
        {
            return cend();
        }

        /// @copydoc begin() const
        const_iterator cbegin() const
        {
            return iterator(*this);
        }

        /// @copydoc end() const
        const_iterator cend() const
        {
            return iterator(*this, true);
        }

        /** Accesses the first token
         *
         * */
        StringView front() const
        {
            return StringView(buffer);
        }

        /** Removes the first token from the container
         *
         * */
        StringView pop_front()
        {
            auto retval = front();

            buffer += retval.size();
            buffer++;
            count--;
            max -=  retval.size();
            max--;

            return retval;
        }

        /** returns the number of tokens in container
         *
         * */
        size_t size() const
        {
            return count;
        }

        /// @copydoc size() const
        size_t length() const
        {
            return size();
        }

        /** Return true if size() == 0
         *
         * */
        bool empty() const
        {
            return count == 0;
        }

    private:

        const char *buffer;
        size_t max;
        size_t count;

        void put_char(BufferStream& s, char c)
        {
            auto n = s.write(&c, 1);

            if((c == 0) && (n > 0)){

                count++;
                max = s.tell();
            }
        }
    };
};

#endif
