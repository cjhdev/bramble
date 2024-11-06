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

#include "bramble_string_view.hpp"
#include "bramble_buffer_stream.hpp"

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
