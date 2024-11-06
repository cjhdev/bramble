/*
 * Scenario:
 *
 * - you wish to add support for encoding and decoding a string representation of YourEnum
 * - you would like the string to be case insensitive
 * - you would like any whitespace around the string to be ignored
 *
 * */

#include "bramble.hpp"
#include <cstdio>
#include <string>

enum class YourEnum {

    FirstValue,
    SecondValue,
    ThirdValue,
};

const char *your_enum_to_s(YourEnum value)
{
    switch(value){
    default:                    return "?";
    case YourEnum::FirstValue:  return "FirstValue";
    case YourEnum::SecondValue: return "SecondValue";
    case YourEnum::ThirdValue:  return "ThirdValue";
    }
}

class TestStream : public Bramble::Stream {
public:

    std::string buffer;

    size_t write(const void *v, size_t size)
    {
        auto begin = (const char *)v;
        for(auto i = begin; i != begin + size; ++i){

            buffer.push_back(*i);
        }

        return size;
    }

    void reset()
    {
        buffer.clear();
    }
};

// subclass the encoder to extend it
class YourEncoder : public Bramble::Encoder {
public:

    YourEncoder(Bramble::Stream& s)
        :
        Encoder(s)
    {}

    Encoder& put_your_enum(YourEnum value)
    {
        return put_string(your_enum_to_s(value));
    }
};

// subclass the decoder to extend it
class YourDecoder : public Bramble::Decoder {
public:

    YourDecoder(const char *s)
        :
        Decoder(s)
    {}

    bool get_your_enum(YourEnum& value)
    {
        bool retval = false;

        static const YourEnum table[] {
            YourEnum::FirstValue,
            YourEnum::SecondValue,
            YourEnum::ThirdValue,
        };

        auto stripped = strip(input);

        for(auto i = table; i < table + sizeof(table)/sizeof(*table); ++i){

            if(case_insensitive_compare(stripped, Bramble::StringView(your_enum_to_s(*i)))){

                value = *i;
                retval = true;
                break;
            }
        }

        return retval;
    }
};

int main(int argc, char **argv)
{
    YourEnum v;

    // these will return true
    printf("decode FirstValue: %s\n", YourDecoder("FirstValue").get_your_enum(v) ? "true" : "false");
    printf("decode SecondValue: %s\n", YourDecoder("SecondValue").get_your_enum(v) ? "true" : "false");
    printf("decode ThirdValue: %s\n", YourDecoder("ThirdValue").get_your_enum(v) ? "true" : "false");

    // this will return false
    printf("decode UnknownValue: %s\n", YourDecoder("UnknownValue").get_your_enum(v) ? "true" : "false");

    TestStream s;

    // encode

    YourEncoder(s).put_your_enum(YourEnum::FirstValue);
    printf("encoder FirstValue: %s\n", s.buffer.c_str());
    s.reset();

    YourEncoder(s).put_your_enum(YourEnum::SecondValue);
    printf("encoder SecondValue: %s\n", s.buffer.c_str());
    s.reset();

    YourEncoder(s).put_your_enum(YourEnum::ThirdValue);
    printf("encoder ThirdValue: %s\n", s.buffer.c_str());
    s.reset();

    return 0;
}
