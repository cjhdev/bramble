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

#include "bramble_stream.hpp"

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
