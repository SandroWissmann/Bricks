#include "gtest/gtest.h"

#include "../../include/game_objects/Brick.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::types;

Brick makeBrick(int hitpoints)
{
    return Brick{
        Point{0.0, 0.0},
        Width{1},
        Height{1},
        Hitpoints{hitpoints}
    };
}

TEST(BrickTest, defaultConstructor)
{
    Brick brick;

    EXPECT_EQ(brick.topLeft().x, 0.0);
    EXPECT_EQ(brick.topLeft().y, 0.0);
    EXPECT_EQ(brick.width(), 0.0);
    EXPECT_EQ(brick.height(), 0.0);
}

TEST(BrickTest, Constructor_throws_invald_argument)
{
    EXPECT_THROW(makeBrick(0), std::invalid_argument);
    EXPECT_THROW(makeBrick(10), std::invalid_argument);
}

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