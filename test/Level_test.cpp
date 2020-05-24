#include "gtest/gtest.h"

#include "../src/Level.h"

#include <iostream>
#include <sstream>

using namespace bricks;

TEST(LevelTest, operatorIsWorks1)
{
    std::string test{
        R"(# 
X 1.2 Y 3.4 L 5.6 W 7.8 HP 9
#
X 9.8 Y 7.6 L 5.4 W 3.2
#)"};

    std::istringstream ist{test};

    Level level;
    ist >> level;

    EXPECT_EQ(ist.rdbuf()->in_avail(), 0);

    auto bricks = level.bricks;
    auto indestructibleBricks = level.indestructibleBricks;

    ASSERT_EQ(bricks.size(), 1);
    ASSERT_EQ(indestructibleBricks.size(), 1);

    EXPECT_EQ(bricks[0].topLeft().x, 1.2);
    EXPECT_EQ(bricks[0].topLeft().y, 3.4);
    EXPECT_EQ(bricks[0].length(), 5.6);
    EXPECT_EQ(bricks[0].width(), 7.8);
    EXPECT_EQ(bricks[0].hitpoints(), 9);

    EXPECT_EQ(indestructibleBricks[0].topLeft().x, 9.8);
    EXPECT_EQ(indestructibleBricks[0].topLeft().y, 7.6);
    EXPECT_EQ(indestructibleBricks[0].length(), 5.4);
    EXPECT_EQ(indestructibleBricks[0].width(), 3.2);
}
