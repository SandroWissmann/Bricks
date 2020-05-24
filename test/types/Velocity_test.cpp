#include "gtest/gtest.h"

#include "../../src/types/Velocity.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(VelocityTest, defaultConstructor)
{
    Velocity v;
    EXPECT_EQ(v(), 0.0);
}

TEST(VelocityTest, Constructor)
{
    Velocity v{3.5};
    EXPECT_EQ(v(), 3.5);
}