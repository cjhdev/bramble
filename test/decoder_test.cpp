#include "gtest/gtest.h"

#include "bramble.hpp"

#include <string>

TEST(Decoder, shall_get_true)
{
    const char input[] = "true";
    Bramble::Decoder eut(input);

    bool output;

    ASSERT_TRUE(eut.is_bool());
    ASSERT_TRUE(eut.get_bool(output));
    ASSERT_TRUE(output);
}

TEST(Decoder, shall_get_upper_true)
{
    const char input[] = "TRUE";
    Bramble::Decoder eut(input);

    bool output;

    ASSERT_TRUE(eut.is_bool());
    ASSERT_TRUE(eut.get_bool(output));
    ASSERT_TRUE(output);
}

TEST(Decoder, shall_get_false)
{
    const char input[] = "false";
    Bramble::Decoder eut(input);

    bool output;

    ASSERT_TRUE(eut.is_bool());
    ASSERT_TRUE(eut.get_bool(output));
    ASSERT_FALSE(output);
}

TEST(Decoder, shall_get_upper_false)
{
    const char input[] = "FALSE";
    Bramble::Decoder eut(input);

    bool output;

    ASSERT_TRUE(eut.is_bool());
    ASSERT_TRUE(eut.get_bool(output));
    ASSERT_FALSE(output);
}

TEST(Decoder, shall_detect_named)
{
    const char input[] = "named=value";
    Bramble::Decoder eut(input);

    bool output;

    ASSERT_TRUE(eut.is_named());

    // compare the name
    ASSERT_EQ(Bramble::StringView("named"), eut.name());
    ASSERT_TRUE(eut.name_eq("named"));
    ASSERT_TRUE(eut.name_eq(Bramble::StringView("named")));

    // extract the value
    ASSERT_EQ(Bramble::StringView("value"), eut.named_value());
}

TEST(Decoder, shall_detect_unsigned_integer)
{
    const char input[] = "42";
    Bramble::Decoder eut(input);

    ASSERT_TRUE(eut.is_int());
    ASSERT_TRUE(eut.is_unsigned());
}

TEST(Decoder, shall_get_unsigned_integer)
{
    const char input[] = "42";
    Bramble::Decoder eut(input);

    uint32_t u;
    int32_t i;

    ASSERT_TRUE(eut.get_unsigned(u));
    ASSERT_TRUE(eut.get_int(i));

    ASSERT_EQ(42, u);
    ASSERT_EQ(42, i);
}

TEST(Decoder, shall_detect_unsigned_integer_with_space)
{
    const char input[] = " 42  ";
    Bramble::Decoder eut(input);

    ASSERT_TRUE(eut.is_int());
    ASSERT_TRUE(eut.is_unsigned());
}

TEST(Decoder, shall_get_unsigned_integer_with_space)
{
    const char input[] = " 42  ";
    Bramble::Decoder eut(input);

    uint32_t u;
    int32_t i;

    ASSERT_TRUE(eut.get_unsigned(u));
    ASSERT_TRUE(eut.get_int(i));

    ASSERT_EQ(42, u);
    ASSERT_EQ(42, i);
}

TEST(Decoder, shall_detect_negative_integer)
{
    const char input[] = "-42";
    Bramble::Decoder eut(input);

    ASSERT_TRUE(eut.is_int());
    ASSERT_FALSE(eut.is_unsigned());
}

TEST(Decoder, shall_get_negative_integer)
{
    const char input[] = "-42";
    Bramble::Decoder eut(input);

    uint32_t u;
    int32_t i;

    ASSERT_FALSE(eut.get_unsigned(u));
    ASSERT_TRUE(eut.get_int(i));

    ASSERT_EQ(-42, i);
}

TEST(Decoder, shall_detect_negative_integer_with_space)
{
    const char input[] = " -42  ";
    Bramble::Decoder eut(input);

    ASSERT_TRUE(eut.is_int());
    ASSERT_FALSE(eut.is_unsigned());
}

TEST(Decoder, shall_get_negative_integer_with_space)
{
    const char input[] = " -42  ";
    Bramble::Decoder eut(input);

    uint32_t u;
    int32_t i;

    ASSERT_FALSE(eut.get_unsigned(u));
    ASSERT_TRUE(eut.get_int(i));

    ASSERT_EQ(-42, i);
}

TEST(Decoder, shall_strip_whitespace)
{
    const char input[] = " -42  ";
    auto output = Bramble::Decoder::strip(input);

    ASSERT_EQ(Bramble::StringView("-42"), output);
}

TEST(Decoder, shall_detect_hex_string_even)
{
    const char input[] = "001122334455aabb";
    Bramble::Decoder eut(input);
    uint8_t output[100];
    const uint8_t expected[] = {0, 0x11, 0x22, 0x33, 0x44, 0x55, 0xaa, 0xbb};
    size_t expected_size = sizeof(expected);

    ASSERT_TRUE(eut.is_hex_string());

    ASSERT_EQ(expected_size, eut.get_hex_string_size());
    ASSERT_EQ(expected_size, eut.get_hex_string(output, sizeof(output)));
    ASSERT_TRUE(memcmp(output, expected, expected_size) == 0);
}

TEST(Decoder, shall_detect_hex_string_odd)
{
    const char input[] = "001122334455aab";
    Bramble::Decoder eut(input);
    uint8_t output[100];
    const uint8_t expected[] = {0, 0x11, 0x22, 0x33, 0x44, 0x55, 0xaa, 0xb0};
    size_t expected_size = sizeof(expected);

    ASSERT_TRUE(eut.is_hex_string());

    ASSERT_EQ(expected_size, eut.get_hex_string_size());
    ASSERT_EQ(expected_size, eut.get_hex_string(output, sizeof(output)));
    ASSERT_TRUE(memcmp(output, expected, expected_size) == 0);
}

TEST(Decoder, shall_detect_hex_string_with_space)
{
    const char input[] = " 001122334455aabb  ";
    Bramble::Decoder eut(input);
    uint8_t output[100];
    const uint8_t expected[] = {0, 0x11, 0x22, 0x33, 0x44, 0x55, 0xaa, 0xbb};
    size_t expected_size = sizeof(expected);

    ASSERT_TRUE(eut.is_hex_string());

    ASSERT_EQ(expected_size, eut.get_hex_string_size());
    ASSERT_EQ(expected_size, eut.get_hex_string(output, sizeof(output)));
    ASSERT_TRUE(memcmp(output, expected, expected_size) == 0);
}

TEST(Decoder, shall_detect_b64_string)
{
    const char input[] = "aGVsbG8gd29ybGQ=";
    Bramble::Decoder eut(input);
    char output[100];
    const char expected[] = "hello world";
    size_t expected_size = strlen(expected);
    (void)memset(output, 0, sizeof(output));

    ASSERT_TRUE(eut.is_b64_string());

    ASSERT_EQ(expected_size, eut.get_b64_string_size());
    ASSERT_EQ(expected_size, eut.get_b64_string(output, sizeof(output)));
    ASSERT_STREQ(expected, output);
}

TEST(Decoder, shall_detect_b64_string_with_space)
{
    const char input[] = " aGVsbG8gd29ybGQ=  ";
    Bramble::Decoder eut(input);
    char output[100];
    const char expected[] = "hello world";
    size_t expected_size = strlen(expected);
    (void)memset(output, 0, sizeof(output));

    ASSERT_TRUE(eut.is_b64_string());

    ASSERT_EQ(expected_size, eut.get_b64_string_size());
    ASSERT_EQ(expected_size, eut.get_b64_string(output, sizeof(output)));
    ASSERT_STREQ(expected, output);
}

TEST(Decoder, shall_detect_non_hex_string)
{
    const char input[] = "001122334455aabbgg";
    Bramble::Decoder eut(input);

    ASSERT_FALSE(eut.is_hex_string());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

