#include "gtest/gtest.h"

#include "bramble.hpp"

#include <string>

class TestStream : public Bramble::Stream {
public:

    size_t write(const void *value, size_t size)
    {
        s.append((const char *)value, size);

        return size;
    }

    std::string s;
};

TEST(Encoder, shall_put_true)
{
    TestStream output;
    Bramble::Encoder eut(output);

    eut.put_bool(true);

    ASSERT_EQ("true", output.s);
}

TEST(Encoder, shall_put_false)
{
    TestStream output;
    Bramble::Encoder eut(output);

    eut.put_bool(false);

    ASSERT_EQ("false", output.s);
}

TEST(Encoder, shall_put_null_terminated_string)
{
    TestStream output;
    Bramble::Encoder eut(output);

    eut.put_string("hello world");

    ASSERT_EQ("hello world", output.s);
}

TEST(Encoder, shall_put_string)
{
    TestStream output;
    Bramble::Encoder eut(output);

    eut.put_string("hello world", 11);

    ASSERT_EQ("hello world", output.s);
}

TEST(Encoder, shall_put_char)
{
    TestStream output;
    Bramble::Encoder eut(output);

    eut.put_char('?');

    ASSERT_EQ("?", output.s);
}

TEST(Encoder, shall_put_delimiter)
{
    TestStream output;
    Bramble::Encoder eut(output);

    eut.space();

    ASSERT_EQ(" ", output.s);
}

TEST(Encoder, shall_put_hex_string)
{
    TestStream output;
    Bramble::Encoder eut(output);

    const char input[] = "hello world";

    eut.put_hex_string(input, strlen(input));

    ASSERT_EQ("68656c6c6f20776f726c64", output.s);
}

TEST(Encoder, shall_put_hex_string_null_terminated)
{
    TestStream output;
    Bramble::Encoder eut(output);

    const char input[] = "hello world";

    eut.put_hex_string(input);

    ASSERT_EQ("68656c6c6f20776f726c64", output.s);
}

TEST(Encoder, shall_put_b64)
{
    TestStream output;
    Bramble::Encoder eut(output);

    const char input[] = "hello world";

    eut.put_b64_string(input, strlen(input));

    ASSERT_EQ("aGVsbG8gd29ybGQ=", output.s);
}

TEST(Encoder, shall_put_b64_pad0)
{
    TestStream output;
    Bramble::Encoder eut(output);

    const char input[] = "hello wor";

    eut.put_b64_string(input, strlen(input));

    ASSERT_EQ("aGVsbG8gd29y", output.s);
}

TEST(Encoder, shall_put_b64_pad1)
{
    TestStream output;
    Bramble::Encoder eut(output);

    const char input[] = "hello worl";

    eut.put_b64_string(input, strlen(input));

    ASSERT_EQ("aGVsbG8gd29ybA==", output.s);
}

TEST(Encoder, shall_put_b64_null_terminated)
{
    TestStream output;
    Bramble::Encoder eut(output);

    const char input[] = "hello world";

    eut.put_b64_string(input);

    ASSERT_EQ("aGVsbG8gd29ybGQ=", output.s);
}

TEST(Encoder, shall_put_unsigned_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    uint32_t input = 42;

    eut.put_int(input);

    ASSERT_EQ("42", output.s);
}

#include <cinttypes>

TEST(Encoder, shall_put_large_unsigned_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    uint64_t input = 35184372088832;

    eut.put_int(input);

    ASSERT_EQ("35184372088832", output.s);
}

TEST(Encoder, shall_put_largest_unsigned_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    uint64_t input = UINT64_MAX;

    eut.put_int(input);

    ASSERT_EQ("18446744073709551615", output.s);
}

TEST(Encoder, shall_put_signed_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    int32_t input = -42;

    eut.put_int(input);

    ASSERT_EQ("-42", output.s);
}

TEST(Encoder, shall_put_large_signed_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    int64_t input = -35184372088832;

    eut.put_int(input);

    ASSERT_EQ("-35184372088832", output.s);
}

TEST(Encoder, shall_put_largest_signed_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    int64_t input = INT64_MAX;

    eut.put_int(input);

    ASSERT_EQ("9223372036854775807", output.s);
}

TEST(Encoder, shall_put_smallest_signed_int)
{
    TestStream output;
    Bramble::Encoder eut(output);

    int64_t input = INT64_MIN;

    eut.put_int(input);

    ASSERT_EQ("-9223372036854775808", output.s);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
