#include "gtest/gtest.h"

#include "../../include/types/GridHeight.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(GridHeight, defaultConstructor)
{
    GridHeight h;
    EXPECT_EQ(h(), 0.0);
}

TEST(GridHeight, Constructor)
{
    GridHeight h{3};
    EXPECT_EQ(h(), 3);
}

TEST(GridHeight, operatorIsWorks1)
{
    std::string test{"H 3"};

    std::istringstream ist{test};

    GridHeight h;
    ist >> h;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(h(), 3);
}

TEST(GridHeight, operatorIsFails1)
{
    std::string test{" 3"};

    std::istringstream ist{test};

    GridHeight h;
    ist >> h;

    EXPECT_TRUE(ist.fail());
}

TEST(GridHeight, operatorIsFails2)
{
    std::string test{"W 3"};

    std::istringstream ist{test};

    GridHeight h;
    ist >> h;

    EXPECT_TRUE(ist.fail());
}