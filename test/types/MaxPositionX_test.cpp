#include "gtest/gtest.h"

#include "../../include/types/MaxPositionX.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(MaxPositionXTest, defaultConstructor)
{
    MaxPositionX obj;
    EXPECT_EQ(obj(), 0.0);
}

TEST(MaxPositionXTest, Constructor)
{
    MaxPositionX obj{3.5};
    EXPECT_EQ(obj(), 3.5);
}