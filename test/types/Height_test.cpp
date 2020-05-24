#include "gtest/gtest.h"

#include "../../src/types/Height.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(HeightTest, defaultConstructor)
{
    Height h;
    EXPECT_EQ(h(), 0.0);
}

TEST(HeightTest, Constructor)
{
    Height h{3.5};
    EXPECT_EQ(h(), 3.5);
}

TEST(HeightTest, operatorIsWorks1)
{
    std::string test{"H 3.5"};

    std::istringstream ist{test};

    Height h;
    ist >> h;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(h(), 3.5);
}

TEST(HeightTest, operatorIsWorks2)
{
    std::string test{"H 3"};

    std::istringstream ist{test};

    Height h;
    ist >> h;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(h(), 3.0);
}

TEST(HeightTest, operatorIsFails1)
{
    std::string test{" 3.5"};

    std::istringstream ist{test};

    Height h;
    ist >> h;

    EXPECT_TRUE(ist.fail());
}

TEST(HeightTest, operatorIsFails2)
{
    std::string test{"W 3.5"};

    std::istringstream ist{test};

    Height h;
    ist >> h;

    EXPECT_TRUE(ist.fail());
}