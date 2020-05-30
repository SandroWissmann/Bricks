#include "gtest/gtest.h"

#include "../include/Ball.h"
#include "../include/Brick.h"
#include "../include/GameObjectPhysics.h"
#include "../include/OperatorDegree.h"

using namespace bricks;
using namespace bricks::types;

Ball makeBall(Point p, Width w, Height h)
{
    return Ball{p, w, h, Velocity{10}, Angle{0.0_deg}, Gravity{0}};
}

Brick makeBrick(Point p, Width w, Height h)
{
    return Brick{p, w, h, Hitpoints{1}};
}

class CollisionTest : public ::testing::Test {
protected:
    virtual void SetUp()
    {
        brickTopLeft = makeBrick(Point{0.0, 0.0}, Width{2}, Height{2});
        brickTop = makeBrick(Point{0.0, 0.0}, Width{5}, Height{2});
        brickTopRight = makeBrick(Point{3.0, 0.0}, Width{2}, Height{2});
        brickRight = makeBrick(Point{3.0, 0.0}, Width{2}, Height{5});
        brickBottomRight = makeBrick(Point{3.0, 3.0}, Width{2}, Height{2});
        brickBottom = makeBrick(Point{0.0, 3.0}, Width{5}, Height{2});
        brickBottomLeft = makeBrick(Point{0.0, 3.0}, Width{2}, Height{2});
        brickLeft = makeBrick(Point{0.0, 0.0}, Width{2}, Height{5});

        ball = makeBall(Point{1.0, 1.0}, Width{3}, Height{3});
    }

    Brick brickTopLeft;
    Brick brickTop;
    Brick brickTopRight;
    Brick brickRight;
    Brick brickBottomRight;
    Brick brickBottom;
    Brick brickBottomLeft;
    Brick brickLeft;

    Ball ball;
};

TEST_F(CollisionTest, interectsWithRightX)
{
    EXPECT_FALSE(interectsWithRightX(ball, brickTopLeft));
    EXPECT_FALSE(interectsWithRightX(ball, brickTop));
    EXPECT_TRUE(interectsWithRightX(ball, brickTopRight));
    EXPECT_TRUE(interectsWithRightX(ball, brickRight));
    EXPECT_TRUE(interectsWithRightX(ball, brickBottomRight));
    EXPECT_FALSE(interectsWithRightX(ball, brickBottom));
    EXPECT_FALSE(interectsWithRightX(ball, brickBottomLeft));
    EXPECT_FALSE(interectsWithRightX(ball, brickLeft));
}

TEST_F(CollisionTest, interectsWithLeftX)
{
    EXPECT_TRUE(interectsWithLeftX(ball, brickTopLeft));
    EXPECT_FALSE(interectsWithLeftX(ball, brickTop));
    EXPECT_FALSE(interectsWithLeftX(ball, brickTopRight));
    EXPECT_FALSE(interectsWithLeftX(ball, brickRight));
    EXPECT_FALSE(interectsWithLeftX(ball, brickBottomRight));
    EXPECT_FALSE(interectsWithLeftX(ball, brickBottom));
    EXPECT_TRUE(interectsWithLeftX(ball, brickBottomLeft));
    EXPECT_TRUE(interectsWithLeftX(ball, brickLeft));
}

TEST_F(CollisionTest, interectsWithBottomY)
{
    EXPECT_FALSE(interectsWithBottomY(ball, brickTopLeft));
    EXPECT_FALSE(interectsWithBottomY(ball, brickTop));
    EXPECT_FALSE(interectsWithBottomY(ball, brickTopRight));
    EXPECT_FALSE(interectsWithBottomY(ball, brickRight));
    EXPECT_TRUE(interectsWithBottomY(ball, brickBottomRight));
    EXPECT_TRUE(interectsWithBottomY(ball, brickBottom));
    EXPECT_TRUE(interectsWithBottomY(ball, brickBottomLeft));
    EXPECT_FALSE(interectsWithBottomY(ball, brickLeft));
}

TEST_F(CollisionTest, interectsWithTopY)
{
    EXPECT_TRUE(interectsWithTopY(ball, brickTopLeft));
    EXPECT_TRUE(interectsWithTopY(ball, brickTop));
    EXPECT_TRUE(interectsWithTopY(ball, brickTopRight));
    EXPECT_FALSE(interectsWithTopY(ball, brickRight));
    EXPECT_FALSE(interectsWithTopY(ball, brickBottomRight));
    EXPECT_FALSE(interectsWithTopY(ball, brickBottom));
    EXPECT_FALSE(interectsWithTopY(ball, brickBottomLeft));
    EXPECT_FALSE(interectsWithTopY(ball, brickLeft));
}

TEST_F(CollisionTest, isInsideWithX)
{
    EXPECT_FALSE(isInsideWithX(ball, brickTopLeft));
    EXPECT_TRUE(isInsideWithX(ball, brickTop));
    EXPECT_FALSE(isInsideWithX(ball, brickTopRight));
    EXPECT_FALSE(isInsideWithX(ball, brickRight));
    EXPECT_FALSE(isInsideWithX(ball, brickBottomRight));
    EXPECT_TRUE(isInsideWithX(ball, brickBottom));
    EXPECT_FALSE(isInsideWithX(ball, brickBottomLeft));
    EXPECT_FALSE(isInsideWithX(ball, brickLeft));
}

TEST_F(CollisionTest, isInsideWithY)
{
    EXPECT_FALSE(isInsideWithY(ball, brickTopLeft));
    EXPECT_FALSE(isInsideWithY(ball, brickTop));
    EXPECT_FALSE(isInsideWithY(ball, brickTopRight));
    EXPECT_TRUE(isInsideWithY(ball, brickRight));
    EXPECT_FALSE(isInsideWithY(ball, brickBottomRight));
    EXPECT_FALSE(isInsideWithY(ball, brickBottom));
    EXPECT_FALSE(isInsideWithY(ball, brickBottomLeft));
    EXPECT_TRUE(isInsideWithY(ball, brickLeft));
}

TEST_F(CollisionTest, notThroughWithRightX)
{
    EXPECT_FALSE(notThroughWithRightX(ball, brickTopLeft));
    EXPECT_TRUE(notThroughWithRightX(ball, brickTop));
    EXPECT_TRUE(notThroughWithRightX(ball, brickTopRight));
    EXPECT_TRUE(notThroughWithRightX(ball, brickRight));
    EXPECT_TRUE(notThroughWithRightX(ball, brickBottomRight));
    EXPECT_TRUE(notThroughWithRightX(ball, brickBottom));
    EXPECT_FALSE(notThroughWithRightX(ball, brickBottomLeft));
    EXPECT_FALSE(notThroughWithRightX(ball, brickLeft));
}

TEST_F(CollisionTest, notThroughWithLeftX)
{
    EXPECT_TRUE(notThroughWithLeftX(ball, brickTopLeft));
    EXPECT_TRUE(notThroughWithLeftX(ball, brickTop));
    EXPECT_FALSE(notThroughWithLeftX(ball, brickTopRight));
    EXPECT_FALSE(notThroughWithLeftX(ball, brickRight));
    EXPECT_FALSE(notThroughWithLeftX(ball, brickBottomRight));
    EXPECT_TRUE(notThroughWithLeftX(ball, brickBottom));
    EXPECT_TRUE(notThroughWithLeftX(ball, brickBottomLeft));
    EXPECT_TRUE(notThroughWithLeftX(ball, brickLeft));
}

TEST_F(CollisionTest, notThroughWithTopY)
{
    EXPECT_TRUE(notThroughWithTopY(ball, brickTopLeft));
    EXPECT_TRUE(notThroughWithTopY(ball, brickTop));
    EXPECT_TRUE(notThroughWithTopY(ball, brickTopRight));
    EXPECT_TRUE(notThroughWithTopY(ball, brickRight));
    EXPECT_FALSE(notThroughWithTopY(ball, brickBottomRight));
    EXPECT_FALSE(notThroughWithTopY(ball, brickBottom));
    EXPECT_FALSE(notThroughWithTopY(ball, brickBottomLeft));
    EXPECT_TRUE(notThroughWithTopY(ball, brickLeft));
}

TEST_F(CollisionTest, notThroughWithBottomY)
{
    EXPECT_FALSE(notThroughWithBottomY(ball, brickTopLeft));
    EXPECT_FALSE(notThroughWithBottomY(ball, brickTop));
    EXPECT_FALSE(notThroughWithBottomY(ball, brickTopRight));
    EXPECT_TRUE(notThroughWithBottomY(ball, brickRight));
    EXPECT_TRUE(notThroughWithBottomY(ball, brickBottomRight));
    EXPECT_TRUE(notThroughWithBottomY(ball, brickBottom));
    EXPECT_TRUE(notThroughWithBottomY(ball, brickBottomLeft));
    EXPECT_TRUE(notThroughWithBottomY(ball, brickLeft));
}

TEST_F(CollisionTest, putBeforeIntersectsWithRightX)
{
    EXPECT_FALSE(ball.bottomRight().x == brickRight.topLeft().x);
    putBeforeIntersectsWithRightX(ball, brickRight);
    EXPECT_TRUE(ball.bottomRight().x == brickRight.topLeft().x);
}

TEST_F(CollisionTest, putBeforeIntersectsWithLeftX)
{
    EXPECT_FALSE(ball.topLeft().x == brickLeft.bottomRight().x);
    putBeforeIntersectsWithLeftX(ball, brickLeft);
    EXPECT_TRUE(ball.topLeft().x == brickLeft.bottomRight().x);
}

TEST_F(CollisionTest, putBeforeIntersectsWithBottomY)
{
    EXPECT_FALSE(ball.bottomRight().y == brickBottom.topLeft().y);
    putBeforeIntersectsWithBottomY(ball, brickBottom);
    EXPECT_TRUE(ball.bottomRight().y == brickBottom.topLeft().y);
}

TEST_F(CollisionTest, putBeforeIntersectsWithTopY)
{
    EXPECT_FALSE(ball.topLeft().y == brickTop.bottomRight().y);
    putBeforeIntersectsWithTopY(ball, brickTop);
    EXPECT_TRUE(ball.topLeft().y == brickTop.bottomRight().y);
}
