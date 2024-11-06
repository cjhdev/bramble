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

#include "bramble_stream.hpp"
#include "bramble_string_view.hpp"

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
