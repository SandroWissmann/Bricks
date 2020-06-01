#include "gtest/gtest.h"

#include "../../include/utility/IsNumber.h"

using namespace bricks::utility;

TEST(IsNumberTest, int_expect_true)
{
    EXPECT_TRUE(isNumber<int>("10"));
    EXPECT_TRUE(isNumber<int>("0"));
    EXPECT_TRUE(isNumber<int>("-10"));
}

TEST(IsNumberTest, int_expect_false)
{
    EXPECT_FALSE(isNumber<int>("10N"));
    EXPECT_FALSE(isNumber<int>("0.0"));
    EXPECT_FALSE(isNumber<int>("-10.0"));
}

TEST(IsNumberTest, double_expect_true)
{
    EXPECT_TRUE(isNumber<double>("10.0"));
    EXPECT_TRUE(isNumber<double>("0.0"));
    EXPECT_TRUE(isNumber<double>("-10.0"));
    EXPECT_TRUE(isNumber<double>("0"));
    EXPECT_TRUE(isNumber<double>("-10"));
}

TEST(IsNumberTest, double_expect_false)
{
    EXPECT_FALSE(isNumber<double>("10N"));
}
