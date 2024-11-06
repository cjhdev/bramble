#include "gtest/gtest.h"

#include "bramble.hpp"

TEST(Argument, shall_handle_null_input)
{
    Bramble::Argument arg(nullptr, nullptr, 0);

    ASSERT_EQ(0, arg.size());
    ASSERT_EQ(arg.begin(), arg.end());
}

TEST(Argument, shall_handle_empty_string)
{
    char argv[] = "";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_EQ(0, arg.size());
    ASSERT_TRUE(arg.empty());
    ASSERT_EQ(arg.begin(), arg.end());
}

TEST(Argument, shall_handle_empty_token)
{
    char argv[] = "' '";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_EQ(1, arg.size());
    ASSERT_FALSE(arg.empty());
    ASSERT_NE(arg.begin(), arg.end());

    ASSERT_EQ(Bramble::StringView(" "), arg.front());

    ASSERT_EQ(arg.begin()+1, arg.end());
}

TEST(Argument, shall_handle_open_single_quote)
{
    char argv[] = "' ";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_EQ(0, arg.size());
    ASSERT_TRUE(arg.empty());
    ASSERT_EQ(arg.begin(), arg.end());
}

TEST(Argument, shall_handle_open_double_quote)
{
    char argv[] = "\" ";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_EQ(0, arg.size());
    ASSERT_TRUE(arg.empty());
    ASSERT_EQ(arg.begin(), arg.end());
}

TEST(Argument, shall_handle_one_token)
{
    char argv[] = "one";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_EQ(1, arg.size());
    ASSERT_FALSE(arg.empty());
    ASSERT_NE(arg.begin(), arg.end());

    ASSERT_EQ(Bramble::StringView("one"), arg.front());

    ASSERT_EQ(arg.begin()+1, arg.end());
}

TEST(Argument, shall_handle_two_token)
{
    char argv[] = "one two";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_EQ(2, arg.size());
    ASSERT_FALSE(arg.empty());
    ASSERT_NE(arg.begin(), arg.end());

    ASSERT_EQ(Bramble::StringView("one"), arg.front());

    ASSERT_EQ(arg.begin()+2, arg.end());

    auto iter = arg.begin();

    ASSERT_EQ(Bramble::StringView("one"), *iter);
    ASSERT_NE(arg.end(), iter);

    ++iter;

    ASSERT_EQ(Bramble::StringView("two"), *iter);
    ASSERT_NE(arg.end(), iter);

    ++iter;

    ASSERT_EQ(arg.end(), iter);
}

TEST(Argument, shall_pop_front_of_one_token)
{
    char argv[] = "one";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_FALSE(arg.empty());
    ASSERT_EQ(1, arg.size());
    ASSERT_EQ(arg.begin()+1, arg.end());

    auto front = arg.pop_front();

    ASSERT_EQ(Bramble::StringView("one"), front);

    ASSERT_TRUE(arg.empty());
    ASSERT_TRUE(arg.size() == 0);
    ASSERT_EQ(arg.begin(), arg.end());
}

TEST(Argument, shall_pop_front_of_two_token)
{
    char argv[] = "one two";
    Bramble::Argument arg(argv, argv, sizeof(argv));

    ASSERT_FALSE(arg.empty());
    ASSERT_EQ(2, arg.size());
    ASSERT_EQ(arg.begin()+2, arg.end());

    auto front = arg.pop_front();

    ASSERT_EQ(Bramble::StringView("one"), front);

    ASSERT_FALSE(arg.empty());
    ASSERT_EQ(1, arg.size());
    ASSERT_EQ(arg.begin()+1, arg.end());

    ASSERT_EQ(Bramble::StringView("two"), arg.front());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
