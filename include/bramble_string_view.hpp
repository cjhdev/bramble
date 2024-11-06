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
