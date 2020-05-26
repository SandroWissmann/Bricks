#include "gtest/gtest.h"

#include "../../include/types/GridWidth.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(GridWidth, defaultConstructor)
{
    GridWidth w;
    EXPECT_EQ(w(), 0.0);
}

TEST(GridWidth, Constructor)
{
    GridWidth w{3};
    EXPECT_EQ(w(), 3);
}

TEST(GridWidth, operatorIsWorks1)
{
    std::string test{"W 3"};

    std::istringstream ist{test};

    GridWidth w;
    ist >> w;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(w(), 3);
}

TEST(GridWidth, operatorIsFails1)
{
    std::string test{" 3"};

    std::istringstream ist{test};

    GridWidth w;
    ist >> w;

    EXPECT_TRUE(ist.fail());
}

TEST(GridWidth, operatorIsFails2)
{
    std::string test{"H 3"};

    std::istringstream ist{test};

    GridWidth w;
    ist >> w;

    EXPECT_TRUE(ist.fail());
}