#include "gtest/gtest.h"

#include "../../include/types/Length.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(LengthTest, defaultConstructor)
{
    Length l;
    EXPECT_EQ(l(), 0.0);
}

TEST(LengthTest, Constructor)
{
    Length l{3.5};
    EXPECT_EQ(l(), 3.5);
}

TEST(LengthTest, operatorIsWorks1)
{
    std::string test{"L 3.5"};

    std::istringstream ist{test};

    Length l;
    ist >> l;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(l(), 3.5);
}

TEST(LengthTest, operatorIsWorks2)
{
    std::string test{"L 3"};

    std::istringstream ist{test};

    Length l;
    ist >> l;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(l(), 3.0);
}

TEST(LengthTest, operatorIsFails1)
{
    std::string test{" 3.5"};

    std::istringstream ist{test};

    Length l;
    ist >> l;

    EXPECT_TRUE(ist.fail());
}

TEST(LengthTest, operatorIsFails2)
{
    std::string test{"W 3.5"};

    std::istringstream ist{test};

    Length l;
    ist >> l;

    EXPECT_TRUE(ist.fail());
}