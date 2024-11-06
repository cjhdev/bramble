#include "gtest/gtest.h"

#include "bramble.hpp"

TEST(GetOpt, shall_have_init_state)
{
    char argv[] = "";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end());

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
    ASSERT_EQ(arg.begin(), value.arg());
    ASSERT_TRUE(value.value().empty());
    ASSERT_EQ(nullptr, value.get_ctx());
}

TEST(GetOpt, shall_finish_if_no_options)
{
    char argv[] = "";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
    ASSERT_EQ(arg.begin(), value.arg());
    ASSERT_TRUE(value.value().empty());
}

TEST(GetOpt, shall_parse_long_value_none)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::None,
            nullptr
        }
    };

    char argv[] = "--test";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
}

TEST(GetOpt, shall_parse_long_value_none_unexpected1)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::None,
            nullptr
        }
    };

    char argv[] = "--test=TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_TRUE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("TEST"), value.value());
}

TEST(GetOpt, shall_parse_long_value_none_unexpected2)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::None,
            nullptr
        }
    };

    char argv[] = "--test TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    ASSERT_EQ(value.arg(), arg.begin()+1);
}

TEST(GetOpt, shall_parse_short_value_none)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::None,
            nullptr
        }
    };

    char argv[] = "-t";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    ASSERT_EQ(value.arg(), arg.begin()+1);
}

TEST(GetOpt, shall_parse_short_value_none_unexpected1)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::None,
            nullptr
        }
    };

    char argv[] = "-t=TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_TRUE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(value.arg(), arg.begin());
}

TEST(GetOpt, shall_parse_short_value_none_unexpected2)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::None,
            nullptr
        }
    };

    char argv[] = "-t TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
}

TEST(GetOpt, shall_parse_long_value_optional_not_present)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::Optional,
            nullptr
        }
    };

    char argv[] = "--test";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
}

TEST(GetOpt, shall_parse_long_value_optional_present1)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::Optional,
            nullptr
        }
    };

    char argv[] = "--test=TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("TEST"), value.value());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
}

TEST(GetOpt, shall_parse_long_value_optional_present2)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::Optional,
            nullptr
        }
    };

    char argv[] = "--test TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());

    ASSERT_EQ(value.arg(), arg.begin()+1);
}

TEST(GetOpt, shall_parse_long_value_required_missing)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::Required,
            nullptr
        }
    };

    char argv[] = "--test";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_TRUE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());
    ASSERT_EQ(arg.begin(), value.arg());
}

TEST(GetOpt, shall_parse_long_value_required_present1)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::Required,
            nullptr
        }
    };

    char argv[] = "--test=TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("TEST"), value.value());
    ASSERT_EQ(arg.end(), value.arg());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());
}

TEST(GetOpt, shall_parse_long_value_required_present2)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "test",
            't',
            Bramble::GetOpt::Value::Required,
            nullptr
        }
    };

    char argv[] = "--test TEST";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("TEST"), value.value());
    ASSERT_EQ(arg.end(), value.arg());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_TRUE(value.value().empty());
}

TEST(GetOpt, shall_parse_short_chain1)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "none",
            'n',
            Bramble::GetOpt::Value::None,
            nullptr
        },
        {
            "required",
            'r',
            Bramble::GetOpt::Value::Required,
            nullptr
        },
        {
            "optional",
            'o',
            Bramble::GetOpt::Value::Optional,
            nullptr
        }
    };

    char argv[] = "-nor=test";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("n"), value.name());
    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("o"), value.name());
    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("r"), value.name());
    ASSERT_EQ(Bramble::StringView("test"), value.value());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());
}

TEST(GetOpt, shall_parse_short_chain2)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "none",
            'n',
            Bramble::GetOpt::Value::None,
            nullptr
        },
        {
            "required",
            'r',
            Bramble::GetOpt::Value::Required,
            nullptr
        },
        {
            "optional",
            'o',
            Bramble::GetOpt::Value::Optional,
            nullptr
        }
    };

    char argv[] = "-rn=test";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_TRUE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("r"), value.name());
    ASSERT_TRUE(value.value().empty());
}

TEST(GetOpt, shall_parse_short_chain3)
{
    const Bramble::GetOpt::Option options[] = {
        {
            "none",
            'n',
            Bramble::GetOpt::Value::None,
            nullptr
        },
        {
            "required",
            'r',
            Bramble::GetOpt::Value::Required,
            nullptr
        },
        {
            "optional",
            'o',
            Bramble::GetOpt::Value::Optional,
            nullptr
        }
    };

    char argv[] = "-on=test";

    Bramble::Argument arg(argv, argv, sizeof(argv));
    Bramble::GetOpt value(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    value.next();

    ASSERT_FALSE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_FALSE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("o"), value.name());
    ASSERT_TRUE(value.value().empty());

    value.next();

    ASSERT_TRUE(value.finished());
    ASSERT_FALSE(value.missing());
    ASSERT_TRUE(value.unexpected());
    ASSERT_FALSE(value.unknown());

    ASSERT_EQ(Bramble::StringView("n"), value.name());
    ASSERT_EQ(Bramble::StringView("test"), value.value());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

