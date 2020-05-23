#include "gtest/gtest.h"

#include "../src/Brick.h"

using namespace bricks;

TEST(BrickTest, startHitpoints)
{
    Brick obj{Point{0, 0}, Width{1}, Height{1}, Hitpoints{2}};
    EXPECT_EQ(obj.startHitpoints(), 2);
}

TEST(BrickTest, hitpoints)
{
    Brick obj{Point{0, 0}, Width{1}, Height{1}, Hitpoints{2}};
    EXPECT_EQ(obj.hitpoints(), 2);
}

TEST(BrickTest, decreaseHitpoints)
{
    Brick obj{Point{0, 0}, Width{1}, Height{1}, Hitpoints{2}};
    EXPECT_EQ(obj.hitpoints(), 2);
    EXPECT_EQ(obj.startHitpoints(), 2);

    obj.decreaseHitpoints();

    EXPECT_EQ(obj.hitpoints(), 1);
    EXPECT_EQ(obj.startHitpoints(), 2);
}

TEST(BrickTest, isDestroyed)
{
    Brick obj{Point{0, 0}, Width{1}, Height{1}, Hitpoints{1}};
    EXPECT_FALSE(obj.isDestroyed());

    obj.decreaseHitpoints();

    EXPECT_TRUE(obj.isDestroyed());
}