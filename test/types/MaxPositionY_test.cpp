#include "gtest/gtest.h"

#include "../../src/types/MaxPositionY.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(MaxPositionYTest, defaultConstructor)
{
    MaxPositionY obj;
    EXPECT_EQ(obj(), 0.0);
}

TEST(MaxPositionYTest, Constructor)
{
    MaxPositionY obj{3.5};
    EXPECT_EQ(obj(), 3.5);
}