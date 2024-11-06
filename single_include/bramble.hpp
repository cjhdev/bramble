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

#ifndef BRAMBLE_H_INCLUDED
#define BRAMBLE_H_INCLUDED

/* #include "bramble_version.hpp" */
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

/// @file

#ifndef BRAMBLE_VERSION_H_INCLUDED
#define BRAMBLE_VERSION_H_INCLUDED

/** Version as string */
#define BRAMBLE_VERSION_STRING      "0.1.0"

/** Version as integer */
#define BRAMBLE_VERSION_NUMBER      1000
/** Version major number */
#define BRAMBLE_VERSION_MAJOR       0
/** Version minor number */
#define BRAMBLE_VERSION_MINOR       1
/** Version patch number */
#define BRAMBLE_VERSION_PATCH       0

#include <cstdint>

namespace Bramble {

    /** Get version string
     *
     * */
    constexpr const char *get_version_string()
    {
        return "0.1.0";
    }

    /** Get version integer
     *
     * */
    constexpr uint32_t get_version_number()
    {
        return 1000;
    }

    /** Get version major number
     *
     * */
    constexpr uint32_t get_version_major()
    {
        return 0;
    }

    /** Get version minor number
     *
     * */
    constexpr uint32_t get_version_minor()
    {
        return 1;
    }

    /** Get version patch number
     *
     * */
    constexpr uint32_t get_version_patch()
    {
        return 0;
    }
};

#endif

/* #include "bramble_server.hpp" */
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

/* #include "bramble_stream.hpp" */
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

#ifndef BRAMBLE_STREAM_H_INCLUDED
#define BRAMBLE_STREAM_H_INCLUDED

#include <cstddef>
#include <cstring>
#include <algorithm>

namespace Bramble {

    class Stream {
    public:

        virtual ~Stream()
        {
        }

        virtual size_t read(void *, size_t)
        {
            return 0;
        }

        virtual size_t write(const void *, size_t)
        {
            return 0;
        }

        virtual bool eof() const
        {
            return false;
        }

        virtual size_t peek(void *, size_t)
        {
            return 0;
        }

        virtual void drain()
        {
        }
    };
};

#endif
/* #include "bramble_get_opt.hpp" */
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

/* #include "bramble_string_view.hpp" */
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

#ifndef BRAMBLE_STRING_VIEW_H_INCLUDED
#define BRAMBLE_STRING_VIEW_H_INCLUDED

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <algorithm>

namespace Bramble {

    /** A string_view that doesn't throw exceptions and which works in C++11
     *
     * */
    class StringView {
    public:

        StringView()
            :
            s(nullptr),
            max(0)
        {
        }

        StringView(const StringView& other)
            :
            s(other.s),
            max(other.max)
        {
        }

        StringView(const char *s, size_t size)
            :
            s(s),
            max(size)
        {}

        StringView(const char *s)
            :
            s(s),
            max((s != nullptr) ? strlen(s) : 0)
        {}

        StringView& operator=(const StringView& other)
        {
            s = other.s;
            max = other.max;
            return *this;
        }

        // iterators

        class iterator_base {
        public:

            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = char;
            using pointer           = const char*;
            using reference         = const char&;

            iterator_base()
                :
                ptr(nullptr)
            {}

            iterator_base(const char *ptr)
                :
                ptr(ptr)
            {}

            iterator_base(const iterator_base& other)
                :
                ptr(other.ptr)
            {
            }

            reference operator*() const
            {
                return *ptr;
            }

            pointer operator->() const
            {
                return ptr;
            }

            reference operator[](size_t n) const
            {
                return ptr[n];
            }

            bool operator==(const iterator_base& other) const
            {
                return ptr == other.ptr;
            }

            bool operator!=(const iterator_base& other) const
            {
                return ptr != other.ptr;
            }

        protected:

            const char *ptr;
        };

        class const_iterator : public iterator_base {
        public:

            const_iterator()
                :
                iterator_base()
            {}

            const_iterator(const char *ptr)
                :
                iterator_base(ptr)
            {}

            const_iterator(const const_iterator& other)
                :
                iterator_base(other)
            {
            }

            const_iterator& operator=(const const_iterator& other)
            {
                ptr = other.ptr;
                return *this;
            }

            const_iterator& operator++()
            {
                ptr++;
                return *this;
            }

            const_iterator operator++(int)
            {
                auto retval = *this;
                ptr++;
                return retval;
            }

            const_iterator& operator--()
            {
                ptr--;
                return *this;
            }

            const_iterator operator--(int)
            {
                auto retval = *this;
                ptr--;
                return retval;
            }

            const_iterator operator+(size_t n)
            {
                const_iterator retval = *this;

                retval.ptr += n;

                return retval;
            }

            const_iterator operator-(size_t n)
            {
                const_iterator retval = *this;

                retval.ptr -= n;

                return retval;
            }

            difference_type operator-(const const_iterator& other) const
            {
                return (other.ptr > ptr) ? other.ptr - ptr : ptr - other.ptr;
            }
        };

        class const_reverse_iterator : public iterator_base {
        public:

            const_reverse_iterator()
                :
                iterator_base()
            {}

            const_reverse_iterator(const char *ptr)
                :
                iterator_base(ptr)
            {}

            const_reverse_iterator(const const_reverse_iterator& other)
                :
                iterator_base(other)
            {
            }

            const_reverse_iterator& operator=(const const_reverse_iterator& other)
            {
                ptr = other.ptr;
                return *this;
            }

            const_reverse_iterator& operator++()
            {
                ptr--;
                return *this;
            }

            const_reverse_iterator operator++(int)
            {
                auto retval = *this;
                ptr--;
                return retval;
            }

            const_reverse_iterator& operator--()
            {
                ptr++;
                return *this;
            }

            const_reverse_iterator operator--(int)
            {
                auto retval = *this;
                ptr++;
                return retval;
            }

            const_reverse_iterator operator+(size_t n)
            {
                const_reverse_iterator retval = *this;

                retval.ptr -= n;

                return retval;
            }

            const_reverse_iterator operator-(size_t n)
            {
                const_reverse_iterator retval = *this;

                retval.ptr += n;

                return retval;
            }

            difference_type operator-(const const_reverse_iterator& other) const
            {
                return (other.ptr > ptr) ? other.ptr - ptr : ptr - other.ptr;
            }
        };

        typedef const_iterator iterator;
        typedef const_reverse_iterator reverse_iterator;

        /** Returns an iterator to the beginning
         *
         * */
        iterator begin() const
        {
            return iterator(s);
        }

        /// @copydoc begin() const
        const_iterator cbegin() const
        {
            return begin();
        }

        /** Returns an iterator to the end
         *
         * */
        iterator end() const
        {
            return iterator(s + max);
        }

        /// @copydoc end() const
        const_iterator cend() const
        {
            return end();
        }

        /** Returns a reverse iterator to the beginning
         *
         * */
        reverse_iterator rbegin() const
        {
            return reverse_iterator(s + max - 1);
        }

        /// @copydoc rbegin() const
        const_reverse_iterator crbegin() const
        {
            return rbegin();
        }

        /** Returns a reverse iterator to the end
         *
         * */
        reverse_iterator rend() const
        {
            return reverse_iterator(s - 1);
        }

        /// @copydoc rend() const
        const_reverse_iterator crend() const
        {
            return rend();
        }

        // element access

        /** Accesses the specified character
         *
         * */
        char operator[](size_t i) const
        {
            return s[i];
        }

        /** Accesses the first character
         *
         * */
        char front() const
        {
            return *s;
        }

        /** Accesses the last character
         *
         * */
        char back() const
        {
            return s[max-1];
        }

        /** Returns pointer to the first character of a view
         *
         * */
        const char *data() const
        {
            return s;
        }

        // capacity

        /** Returns the number of characters
         *
         * */
        size_t size() const
        {
            return max;
        }

        /// @copydoc size() const
        size_t length() const
        {
            return size();
        }

        /** Returns the maximum number of characters */
        size_t max_size() const
        {
            return npos;
        }

        /** Checks whether the view is empty */
        bool empty() const
        {
            return size() == 0;
        }

        // modifiers

        /** Shrink the view by moving its start forward
         *
         * @param n     characters to shrink by
         *
         * */
        void remove_prefix(size_t n)
        {
            if(s != nullptr){

                s += std::min(n, max);
                max -= std::min(n, max);
            }
        }

        /** Shrink the view by moving its end backward
         *
         * @param n     characters to shrink by
         *
         * */
        void remove_suffix(size_t n)
        {
            max -= std::min(max, n);
        }

        /** Swaps the contents
         *
         * @param other     view to swap
         *
         * */
        void swap(StringView& other)
        {
            auto tmp = other;

            other = *this;
            *this = tmp;
        }

        // operations

        /** Copies characters
         *
         * */
        size_t copy(char *dest, size_t count, size_t pos=0) const
        {
            size_t retval = (std::min(max, count) > pos)
                ?
                std::min(max, count) - pos
                :
                0;

            (void)memcpy(dest, &s[std::min(max, pos)], retval);

            return retval;
        }

        /** Copies characters
         *
         * */
        StringView substr(size_t pos=0, size_t count=npos) const
        {
            auto p = std::min(max, pos);
            auto n = std::min(count, max - p);

            return (n > 0) ? StringView(&s[p], n) : StringView();
        }

        int compare(const StringView& v) const
        {
            return compare(v.s, v.size());
        }

        int compare(size_t pos1, size_t count1, const StringView& v) const
        {
            auto p = std::min(v.max, pos1);
            auto n = std::min(v.max, v.max - p);

            return compare(&v.s[p], n);
        }

        int compare(const char *s) const
        {
            return compare(s, strlen(s));
        }

        int compare(const char *s, size_t count) const
        {
            return (count < max)
                ?
                -1
                :
                (count > max)
                    ?
                    1
                    :
                    memcmp(this->s, s, count);
        }

        size_t find_first_of(char c, size_t pos=0) const
        {
            auto retval = npos;

            auto v = substr(pos);

            for(auto iter=v.begin(); iter != v.end(); ++iter){

                if(*iter == c){

                    retval = (iter - v.begin()) + pos;
                    break;
                }
            }

            return retval;
        }

        // todo
#if 0
        size_t find_first_of(StringView v, size_t pos=0) const
        {
            (void)v;
            (void)pos;
            return npos;
        }

        size_t find_first_of(const char *s, size_t pos, size_t count) const
        {
            (void)s;
            (void)pos;
            (void)count;
            return npos;
        }

        size_t find_first_of(const char *s, size_t pos=0) const
        {
            (void)s;
            (void)pos;
            return npos;
        }
#endif

        // constants

        static const size_t npos = SIZE_MAX;

        // non-member functions

        bool operator==(const StringView& other) const
        {
            return compare(other) == 0;
        }

        bool operator!=(const StringView& other) const
        {
            return compare(other) != 0;
        }

    private:

        const char *s;
        size_t max;
    };
};

#endif
/* #include "bramble_argument.hpp" */
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

/* #include "bramble_string_view.hpp" first included at line 231 */
/* #include "bramble_buffer_stream.hpp" */
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

#ifndef BRAMBLE_BUFFER_STREAM_H_INCLUDED
#define BRAMBLE_BUFFER_STREAM_H_INCLUDED

/* #include "bramble_stream.hpp" first included at line 139 */

namespace Bramble {

    class BufferStream : public Stream {
    public:

        BufferStream(const void *buffer, size_t size)
            :
            read_ptr((const uint8_t *)buffer),
            write_ptr(nullptr),
            max(size),
            pos(0)
        {
        }

        BufferStream(void *buffer, size_t size)
            :
            read_ptr((uint8_t *)buffer),
            write_ptr((uint8_t *)buffer),
            max(size),
            pos(0)
        {
        }

        size_t read(void *buffer, size_t size)
        {
            size_t retval = std::min(max - pos, size);
            (void)memcpy(buffer, &read_ptr[pos], retval);
            pos += retval;

            return retval;
        }

        size_t peek(void *buffer, size_t size)
        {
            size_t retval = std::min(max - pos, size);
            (void)memcpy(buffer, &read_ptr[pos], retval);

            return retval;
        }

        size_t write(const void *buffer, size_t size)
        {
            size_t retval = 0;

            if(write_ptr != nullptr){

                retval = std::min(max - pos, size);
                (void)memcpy(&write_ptr[pos], buffer, retval);
                pos += retval;
            }

            return retval;
        }

        size_t tell() const
        {
            return pos;
        }

        bool eof() const
        {
            return pos == max;
        }

        void rewind()
        {
            pos = 0;
        }

        size_t capacity() const
        {
            return max;
        }

    private:

        const uint8_t *read_ptr;
        uint8_t *write_ptr;
        size_t max;
        size_t pos;
        bool error;
    };
};

#endif

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
/* #include "bramble_encoder.hpp" */
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

#ifndef BRAMBLE_ENCODER_H_INCLUDED
#define BRAMBLE_ENCODER_H_INCLUDED

/* #include "bramble_stream.hpp" first included at line 139 */
/* #include "bramble_string_view.hpp" first included at line 231 */

#include <cstdint>
#include <cstddef>
#include <array>
#include <algorithm>

namespace Bramble {

    /** Encoder is intended to be used to add arguments to a Request or an ACK response.
     *
     * Encoder instances write to Stream and representations are optimised for Bramble protocol.
     *
     * */
    class Encoder {
    public:

        /** integer base */
        enum class Base {

            k10,    ///< decimal
            k16     ///< hexadecimal
        };

        /** Create an Encoder
         *
         * @param[in] s output stream
         *
         * */
        Encoder(Stream& s)
            :
            s(s)
        {}

        virtual ~Encoder()
        {}

        /** the output stream */
        Stream& s;

        /** put a deliminter character (a single whitespace)
         *
         * Delimiters separate tokens in Bramble protocol.
         *
         * @return Encoder&
         *
         * */
        Encoder& put_space()
        {
            return put_char(' ');
        }

        /// @copydoc put_space()
        Encoder& space()
        {
            return put_space();
        }

        /** put visible string
         *
         * @param[in] value     input buffer
         * @param[in] size      size of input buffer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_string(const char *value, size_t size)
        {
            (void)s.write(value, size);
            return *this;
        }

        /** put null terminated visible string
         *
         * @param[in] value     input buffer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_string(const char *value)
        {
            (void)s.write(value, strlen(value));
            return *this;
        }

        /** put a string view
         *
         * @param[in] value     input view
         *
         * @return Encoder&
         *
         * */
        Encoder& put_string(const StringView& value)
        {
            (void)s.write(value.data(), value.size());
            return *this;
        }

        /** put a single character
         *
         * @param[in] value     single character
         *
         * @return Encoder&
         *
         * */
        Encoder& put_char(char value)
        {
            (void)s.write(&value, sizeof(value));
            return *this;
        }

        /** put an integer
         *
         * @param[in] value     integer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_int(uint8_t value, Base base=Base::k10)
        {
            return put_int(uint32_t(value), base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(uint16_t value, Base base=Base::k10)
        {
            return put_int(uint32_t(value), base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(uint32_t value, Base base=Base::k10)
        {
            return uint_to_s<uint32_t>(value, base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(uint64_t value, Base base=Base::k10)
        {
            return uint_to_s<uint64_t>(value, base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(int8_t value, Base base=Base::k10)
        {
            return put_int(int32_t(value), base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(int16_t value, Base base=Base::k10)
        {
            return put_int(int32_t(value), base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(int32_t value, Base base=Base::k10)
        {
            if((base == Base::k10) && (value < 0)){

                (void)put_char('-');
            }

            return put_int(uint32_t(std::abs(value)), base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int(int64_t value, Base base=Base::k10)
        {
            if((base == Base::k10) && (value < 0)){

                (void)put_char('-');
            }

            return put_int(uint64_t(std::abs(value)), base);
        }

        /** put an unsigned integer
         *
         * @param[in] value     unsigned integer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_unsigned(uint8_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_unsigned(uint16_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_unsigned(uint32_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_unsigned(uint64_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_uint8(uint8_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_uint16(uint16_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_uint32(uint32_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_unsigned(uint8_t)
        Encoder& put_uint64(uint64_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int8(int8_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int16(int16_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int32(int32_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /// @copydoc put_int(uint8_t)
        Encoder& put_int64(int64_t value, Base base=Base::k10)
        {
            return put_int(value, base);
        }

        /** put a boolean value
         *
         * @param[in] value     boolean value
         *
         * @return Encoder&
         *
         * */
        Encoder& put_bool(bool value)
        {
            return put_string(value ? "true" : "false");
        }

        /** put value as hexadecimal string
         *
         * @param[in] value     input buffer
         * @param[in] size      size of input buffer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_hex_string(const void *value, size_t size)
        {
            auto begin = (const uint8_t *)value;
            auto end = begin + size;

            for(auto iter = begin; iter != end; ++iter){

                (void)put_char(nibble_to_hex((*iter) >> 4));
                (void)put_char(nibble_to_hex(*iter));
            }

            return *this;
        }

        /** put value as hexadecimal string
         *
         * @param[in] value     null terminated input buffer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_hex_string(const char *value)
        {
            return put_hex_string(value, strlen(value));
        }

        /** put value as hexadecimal string
         *
         * @param[in] value     input view
         *
         * @return Encoder&
         *
         * */
        Encoder& put_hex_string(const StringView& value)
        {
            return put_hex_string(value.data(), value.size());
        }

        /** put value as base64 string
         *
         * @param[in] value     input buffer
         * @param[in] size      size of input buffer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_b64_string(const void *value, size_t size)
        {
            auto begin = (const uint8_t *)value;
            auto end = begin + size;

            for(auto iter = begin; iter != end;){

                switch(std::distance(iter, end)){
                default:

                    (void)put_char(byte_to_b64(iter[0] >> 2));
                    (void)put_char(byte_to_b64((iter[1] >> 4) | (iter[0] << 4)));
                    (void)put_char(byte_to_b64((iter[2] >> 6) | (iter[1] << 2)));
                    (void)put_char(byte_to_b64(iter[2]));

                    ++iter;
                    ++iter;
                    ++iter;
                    break;

                case 1:

                    (void)put_char(byte_to_b64(iter[0] >> 2));
                    (void)put_char(byte_to_b64(iter[0] << 4));
                    (void)put_char('=');
                    (void)put_char('=');

                    ++iter;
                    break;

                case 2:

                    (void)put_char(byte_to_b64(iter[0] >> 2));
                    (void)put_char(byte_to_b64((iter[1] >> 4) | (iter[0] << 4)));
                    (void)put_char(byte_to_b64(iter[1] << 2));
                    (void)put_char('=');

                    ++iter;
                    ++iter;
                    break;
                }
            }

            return *this;
        }

        /** put value as base64 string
         *
         * @param[in] value     null terminated input buffer
         *
         * @return Encoder&
         *
         * */
        Encoder& put_b64_string(const char *value)
        {
            return put_b64_string(value, strlen(value));
        }

        /** put value as base64 string
         *
         * @param[in] value     input view
         *
         * @return Encoder&
         *
         * */
        Encoder& put_b64_string(const StringView& value)
        {
            return put_b64_string(value.data(), value.size());
        }

    protected:

        template<typename T>
        Encoder& uint_to_s(T value, Base base)
        {
            T v = value;

            // at most 20 digits for 64bit
            std::array<char,20> buf;

            auto iter = buf.rbegin();

            switch(base){
            default:
            case Base::k10:

                do{

                    *iter = '0' + char(v % T(10));
                    ++iter;
                    v /= T(10);
                }
                while((v > 0) && (iter != buf.rend()));

                break;

            case Base::k16:

                do{

                    *iter = nibble_to_hex(uint8_t(v));
                    v >>= 4;
                    ++iter;
                }
                while((v > 0) && (iter != buf.rend()));

                (void)put_string("0x");

                break;
            }

            auto num_digits = iter - buf.rbegin();

            (void)s.write(&(iter[-1]), num_digits);

            return *this;
        }

        static char nibble_to_hex(uint8_t value)
        {
            static const char table[] = {
                '0',
                '1',
                '2',
                '3',
                '4',
                '5',
                '6',
                '7',
                '8',
                '9',
                'a',
                'b',
                'c',
                'd',
                'e',
                'f'
            };

            return table[value & 0xf];
        }

        static char byte_to_b64(uint8_t value)
        {
            static const char table[] = {
                'A',
                'B',
                'C',
                'D',
                'E',
                'F',
                'G',
                'H',
                'I',
                'J',
                'K',
                'L',
                'M',
                'N',
                'O',
                'P',
                'Q',
                'R',
                'S',
                'T',
                'U',
                'V',
                'W',
                'X',
                'Y',
                'Z',
                'a',
                'b',
                'c',
                'd',
                'e',
                'f',
                'g',
                'h',
                'i',
                'j',
                'k',
                'l',
                'm',
                'n',
                'o',
                'p',
                'q',
                'r',
                's',
                't',
                'u',
                'v',
                'w',
                'x',
                'y',
                'z',
                '0',
                '1',
                '2',
                '3',
                '4',
                '5',
                '6',
                '7',
                '8',
                '9',
                '+',
                '/'
            };

            return table[value & 0x3f];
        }
    };
};

#endif
/* #include "bramble_decoder.hpp" */
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

#ifndef BRAMBLE_DECODER_H_INCLUDED
#define BRAMBLE_DECODER_H_INCLUDED

/* #include "bramble_string_view.hpp" first included at line 231 */
/* #include "bramble_buffer_stream.hpp" first included at line 824 */

#include <cctype>

namespace Bramble {

    /** A tool for pulling values out of strings
     *
     * */
    class Decoder {
    public:

        Decoder()
        {
        }

        /** decode a null-terminated string
         *
         * @param[in] s     null-terminated string
         *
         * */
        Decoder(const char *s)
            :
            input(s, strlen(s))
        {
        }

        /** decode a string
         *
         * @param[in] s     string
         * @param[in] size  size of string
         *
         * */
        Decoder(const char *s, size_t size)
            :
            input(s, size)
        {
        }

        /** decode a string view
         *
         * @param[in] v     string view
         *
         * */
        Decoder(const StringView& v)
            :
            input(v)
        {
        }

        Decoder(const Decoder& other)
            :
            input(other.input)
        {
        }

        const Decoder& operator=(const Decoder& other)
        {
            input = other.input;
            return *this;
        }

        void swap(Decoder& other)
        {
            auto tmp = other.input;
            other.input = input;
            input = tmp;
        }

        /** Test if input is a named argument
         *
         * @retval true     argument is named
         * @retval false    argument is not named
         *
         * */
        bool is_named() const
        {
            return input.find_first_of('=') != input.npos;
        }

        /** Get the name of a named argument
         *
         * @return StringView
         *
         * */
        StringView name() const
        {
            return is_named() ? strip(input).substr(0, strip(input).find_first_of('=')) : StringView();
        }

        /** Get the value associated with name()
         *
         * @return StringView
         *
         * */
        StringView named_value() const
        {
            return input.substr(input.find_first_of('=')+1);
        }

        /** Get the input value as-is
         *
         * @return StringView
         *
         * */
        StringView value() const
        {
            return input;
        }

        /** Test named argument name
         *
         * @param[in] v     expected name
         *
         * @retval true     v == name()
         * @retval false    v != name()
         *
         * */
        bool name_eq(const char *v) const
        {
            return name_eq(StringView(v));
        }

        /// @copydoc name_eq(const char *) const
        bool name_eq(const StringView v) const
        {
            return is_named() && (name().compare(v) == 0);
        }

        /** Test if value() is a boolean
         *
         * @retval true     value() is
         * @retval false    value() is not
         *
         * */
        bool is_bool() const
        {
            bool v;
            return get_bool(v);
        }

        /** Test if value() is integer (signed or unsigned)
         *
         * @retval true     value() is
         * @retval false    value() is not
         *
         * */
        bool is_int() const
        {
            bool retval = false;

            auto tmp = strip(input);

            if(!tmp.empty()){

                if(tmp.front() == '-'){

                    tmp.remove_prefix(1);
                }

                retval = true;

                for(auto iter = tmp.begin(); (iter != tmp.end()) && retval; ++iter){

                    if((*iter < '0') || (*iter > '9')){

                        retval = false;
                    }
                }
            }

            return retval;
        }

        /** Test if value() is unsigned integer
         *
         * @retval true     value() is
         * @retval false    value() is not
         *
         * */
        bool is_unsigned() const
        {
            bool retval = false;

            auto tmp = strip(input);

            if(!tmp.empty()){

                retval = true;

                for(auto iter = tmp.begin(); (iter != tmp.end()) && retval; ++iter){

                    if((*iter < '0') || (*iter > '9')){

                        retval = false;
                    }
                }
            }

            return retval;
        }

        /** Remove whitespace from before and after non-whitespace characters
         *
         * @param[in] v     input string
         *
         * @return StringView
         *
         * */
        static StringView strip(const StringView& v)
        {
            StringView retval(v);

            if(!retval.empty()){

                for(auto iter=retval.begin(); (iter != retval.end()) && std::isspace(*iter); ++iter){

                    retval.remove_prefix(1);
                }

                for(auto iter=retval.rbegin(); (iter != retval.rend()) && std::isspace(*iter); ++iter){

                    retval.remove_suffix(1);
                }
            }

            return retval;
        }

        /// @copydoc strip(const StringView&)
        static StringView strip(const char *v)
        {
            StringView tmp(v);
            return strip(tmp);
        }

        /** Test if value() is a string of hexadecimal characters
         *
         * @retval true     value() is
         * @retval false    value() is not
         *
         * */
        bool is_hex_string() const
        {
            return get_hex_string(nullptr, 0) > 0;
        }

        /** Test if value() is a valid b64 string
         *
         * @retval true     value() is
         * @retval false    value() is not
         *
         * */
        bool is_b64_string() const
        {
            return get_b64_string(nullptr, 0) > 0;
        }

        /** Get boolean from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_bool(bool& v) const
        {
            bool retval = true;

            const StringView v_true("true");
            const StringView v_false("false");

            auto vv = strip(value());

            if(case_insensitive_compare(v_true, vv)){

                v = true;
            }
            else if(case_insensitive_compare(v_false, vv)){

                v = false;
            }
            else{

                retval = false;
            }

            return retval;
        }

        /** Get signed integer from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_int(int8_t& v) const
        {
            return get_int8(v);
        }

        /// @copydoc get_int(int8_t&) const
        bool get_int(int16_t& v) const
        {
            return get_int16(v);
        }

        /// @copydoc get_int(int8_t&) const
        bool get_int(int32_t& v) const
        {
            return get_int32(v);
        }

        /// @copydoc get_int(int8_t&) const
        bool get_int(int64_t& v) const
        {
            return get_int64(v);
        }

        /** Get unsigned integer from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_unsigned(uint8_t& v) const
        {
            return get_uint8(v);
        }

        /// @copydoc get_unsigned(uint8_t&) const
        bool get_unsigned(uint16_t& v) const
        {
            return get_uint16(v);
        }

        /// @copydoc get_unsigned(uint8_t&) const
        bool get_unsigned(uint32_t& v) const
        {
            return get_uint32(v);
        }

        /// @copydoc get_unsigned(uint8_t&) const
        bool get_unsigned(uint64_t& v) const
        {
            return get_uint64(v);
        }

        /** Get uint8_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_uint8(uint8_t& v) const
        {
            bool retval = false;
            uint32_t tmp;

            if(get_uint32(tmp) && (tmp <= UINT8_MAX)){

                v = uint8_t(tmp);
                retval = true;
            }

            return retval;
        }

        /** Get uint16_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_uint16(uint16_t& v) const
        {
            bool retval = false;
            uint32_t tmp;

            if(get_uint32(tmp) && (tmp <= UINT16_MAX)){

                v = uint16_t(tmp);
                retval = true;
            }

            return retval;
        }

        /** Get uint32_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_uint32(uint32_t& v) const
        {
            return s_to_uint<uint32_t>(strip(value()), v, Base::Dec);
        }

        /** Get uint64_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_uint64(uint64_t& v) const
        {
            return s_to_uint<uint64_t>(strip(value()), v, Base::Dec);
        }

        /** Get int8_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_int8(int8_t& v) const
        {
            bool retval = false;
            int32_t tmp;

            if(get_int32(tmp) && (tmp <= INT8_MAX) && (tmp >= INT8_MIN)){

                v = int8_t(tmp);
                retval = true;
            }

            return retval;
        }

        /** Get int16_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_int16(int16_t& v) const
        {
            bool retval = false;
            int32_t tmp;

            if(get_int32(tmp) && (tmp <= INT16_MAX) && (tmp >= INT16_MIN)){

                v = int16_t(tmp);
                retval = true;
            }

            return retval;
        }

        /** Get int32_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_int32(int32_t& v) const
        {
            return s_to_int<int32_t, uint32_t, INT32_MAX>(strip(value()), v);
        }

        /** Get int64_t from value()
         *
         * @param[out] v    output
         *
         * @retval true     success
         * @retval false    failure
         *
         * */
        bool get_int64(int64_t& v) const
        {
            return s_to_int<int64_t, uint64_t, INT64_MAX>(strip(value()), v);
        }

        /** Interpret value() as hex encoded memory
         *
         * @note use is_hex_string() to test if all characters in value() appear to be a hex string
         *
         * @param[out] buffer   output
         * @param[out] max      maximum size of buffer
         *
         * @retval bytes written to buffer
         *
         * */
        size_t get_hex_string(void *buffer, size_t max) const
        {
            size_t retval = 0;
            uint8_t cc, c;
            BufferStream output(buffer, max);

            auto tmp = strip(value());

            for(auto iter = tmp.begin(); iter != tmp.end(); ++iter){

                if(!hex_to_value(*iter, cc)){

                    retval = 0;
                    break;
                }

                if(((iter - tmp.begin()) & 1) == 0){

                    c = (cc << 4) & uint8_t(0xf0);

                    if((iter+1) == tmp.end()){

                        output.write(&c, sizeof(c));
                        retval++;
                    }
                }
                else{

                    c |= (cc & uint8_t(0xf));

                    output.write(&c, sizeof(c));
                    retval++;
                }
            }

            return retval;
        }

        size_t get_hex_string_size() const
        {
            return get_hex_string(nullptr, 0);
        }

        /** Interpret value() as base64 encoded memory
         *
         * @note use is_b64_string() to test if all characters in value() appear to be base64
         *
         * @param[out] buffer   output
         * @param[out] max      maximum size of buffer
         *
         * @retval bytes written to buffer
         *
         * */
        size_t get_b64_string(void *buffer, size_t max) const
        {
            size_t retval = 0;
            uint8_t c, out, acc;
            BufferStream output(buffer, max);

            auto tmp = strip(value());

            for(auto iter = tmp.begin(); iter != tmp.end(); ++iter){

                if(b64_to_value(*iter, c)){

                    switch((iter - tmp.begin()) % 4){
                    case 0:
                        acc = (c << 2);
                        break;
                    case 1:
                        out = acc | (c >> 4);
                        acc = (c << 4);
                        output.write(&out, sizeof(out));
                        retval++;
                        break;
                    case 2:
                        out = acc | (c >> 2);
                        acc = (c << 6);
                        output.write(&out, sizeof(out));
                        retval++;
                        break;
                    case 3:
                        out = acc | c;
                        output.write(&out, sizeof(out));
                        retval++;
                        break;
                    }
                }
                else if(*iter == '='){

                    // skip
                }
                else{

                    retval = 0;
                    break;
                }
            }

            return retval;
        }

        size_t get_b64_string_size() const
        {
            return get_b64_string(nullptr, 0);
        }

    protected:

        enum class Base {

            Dec,
            Hex
        };

        StringView input;

        template<typename T>
        bool s_to_uint(StringView s, T& value, Base base) const
        {
            bool retval = false;

            if(!s.empty()){

                value = 0;

                retval = true;

                for(auto iter = s.begin(); (iter != s.end()) && retval; ++iter){

                    switch(base){
                    default:
                    case Base::Dec:

                        if((*iter < '0') || (*iter > '9')){

                            retval = false;
                        }
                        else{

                            auto pre = value;

                            value *= 10;
                            value += (*iter - '0');

                            // overflow
                            if(value < pre){

                                retval = false;
                            }
                        }
                        break;
                    }
                }
            }

            return retval;
        }

        template<typename T, typename TU, size_t T_MAX>
        bool s_to_int(StringView s, T& value) const
        {
            bool retval = false;
            bool negative;
            TU v;

            if(!s.empty()){

                retval = true;

                v = 0;

                if(s.front() == '-'){

                    negative = true;
                    s.remove_prefix(1);
                }
                else{

                    negative = false;
                }

                retval = s_to_uint<TU>(s, v, Base::Dec);

                if(retval){

                    if(negative){

                        // overflow
                        if(v > T_MAX){

                            retval = false;
                        }
                        else{

                            value = T(0) - T(v);
                        }
                    }
                    else{

                        value = T(v);
                    }
                }
            }

            return retval;
        }

        static bool hex_to_value(char c, uint8_t& v)
        {
            bool retval = true;

            if((c >= '0') && (c <= '9')){

                v = c - '0';
            }
            else if((c >= 'a') && (c <= 'f')){

                v = c - 'a' + 10;
            }
            else if((c >= 'A') && (c <= 'F')){

                v = c - 'A' + 10;
            }
            else{

                retval = false;
            }

            return retval;
        }

        static bool b64_to_value(char c, uint8_t& v)
        {
            bool retval = true;

            if((c >= 'A') && (c <= 'Z')){

                v = c - 'A';
            }
            else if((c >= 'a') && (c <= 'z')){

                v = c - 'a' + 26;
            }
            else if((c >= '0') && (c <= '9')){

                v = c - '0' + 26 + 26;
            }
            else if(c == '+'){

                v = 26 + 26 + 10;
            }
            else if(c == '/'){

                v = 26 + 26 + 10 + 1;
            }
            else{

                retval = false;
            }

            return retval;
        }

        static bool case_insensitive_compare(const StringView& a, const StringView& b)
        {
            bool retval = false;

            if(a.size() == b.size()){

                auto a_iter = a.begin();
                auto b_iter = b.begin();

                retval = true;

                for(; a_iter != a.end(); ++a_iter, ++b_iter){

                    if(std::tolower(*a_iter) != std::tolower(*b_iter)){

                        retval = false;
                        break;
                    }
                }
            }

            return retval;
        }
    };
};

#endif
/* #include "bramble_argument.hpp" first included at line 797 */
/* #include "bramble_string_view.hpp" first included at line 231 */

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

#endif
