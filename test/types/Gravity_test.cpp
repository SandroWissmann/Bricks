#include "gtest/gtest.h"

#include "../../include/types/Gravity.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(GravityTest, defaultConstructor)
{
    Gravity g;
    EXPECT_EQ(g(), 0.0);
}

TEST(GravityTest, Constructor)
{
    Gravity g{3.5};
    EXPECT_EQ(g(), 3.5);
}