#include "gtest/gtest.h"

#include "../../include/game_objects/Ball.h"
#include "../../include/game_objects/Brick.h"
#include "../../include/game_objects/Physics.h"
#include "../../include/OperatorDegree.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::types;

class CalcAngleFactorTest : public ::testing::Test {
protected:
    static constexpr double xLeft = 30.0;
    static constexpr double xCenter = 60.0;
    static constexpr double xRight = 90.0;
};

TEST_F(CalcAngleFactorTest, xBallIsXLeft)
{
    auto xBall = xLeft;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 1.0);
}

TEST_F(CalcAngleFactorTest, xBallIsXCenter)
{
    auto xBall = xCenter;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 0.0);
}

TEST_F(CalcAngleFactorTest, xBallIsXRight)
{
    auto xBall = xRight;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 1.0);
}

TEST_F(CalcAngleFactorTest, xBallIsXBetweenLeftAndCenter)
{
    auto xBall = xLeft + (xCenter - xLeft) / 2;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 0.5);
}

TEST_F(CalcAngleFactorTest, xBallIsXBetweenLeftAndCenter2)
{
    auto xBall = xLeft + (xCenter - xLeft) / 4;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 0.75);
}

TEST_F(CalcAngleFactorTest, xBallIsXBetweenCenterAndRight)
{
    auto xBall = xRight - (xRight - xCenter) / 2;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 0.5);
}

TEST_F(CalcAngleFactorTest, xBallIsXBetweenCenterAndRight2)
{
    auto xBall = xRight - (xRight - xCenter) / 4;
    EXPECT_EQ(calcAngleFactor(xBall, xLeft, xCenter, xRight), 0.75);
}


TEST(clampAngle, AngleGetsClamped)
{
    EXPECT_EQ((clampAngle(Angle{0.0_deg}).get()), 30.0_deg);   
    EXPECT_EQ((clampAngle(Angle{5.0_deg}).get()), 30.0_deg); 
    EXPECT_EQ((clampAngle(Angle{10.0_deg}).get()), 30.0_deg); 
    EXPECT_EQ((clampAngle(Angle{15.0_deg}).get()), 30.0_deg); 
    EXPECT_EQ((clampAngle(Angle{20.0_deg}).get()), 30.0_deg); 
    EXPECT_EQ((clampAngle(Angle{25.0_deg}).get()), 30.0_deg); 
    EXPECT_EQ((clampAngle(Angle{30.0_deg}).get()), 30.0_deg); 
    EXPECT_EQ((clampAngle(Angle{35.0_deg}).get()), 35.0_deg); 
    EXPECT_EQ((clampAngle(Angle{40.0_deg}).get()), 40.0_deg); 
    EXPECT_EQ((clampAngle(Angle{45.0_deg}).get()), 45.0_deg); 
    EXPECT_EQ((clampAngle(Angle{50.0_deg}).get()), 50.0_deg); 
    EXPECT_EQ((clampAngle(Angle{55.0_deg}).get()), 55.0_deg); 
    EXPECT_EQ((clampAngle(Angle{60.0_deg}).get()), 60.0_deg); 
    EXPECT_EQ((clampAngle(Angle{65.0_deg}).get()), 65.0_deg); 
    EXPECT_EQ((clampAngle(Angle{70.0_deg}).get()), 70.0_deg); 
    EXPECT_EQ((clampAngle(Angle{75.0_deg}).get()), 75.0_deg);  
    EXPECT_EQ((clampAngle(Angle{80.0_deg}).get()), 75.0_deg); 
    EXPECT_EQ((clampAngle(Angle{85.0_deg}).get()), 75.0_deg); 
    EXPECT_EQ((clampAngle(Angle{90.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{95.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{100.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{105.0_deg}).get()), 105.0_deg); 
    EXPECT_EQ((clampAngle(Angle{110.0_deg}).get()), 110.0_deg); 
    EXPECT_EQ((clampAngle(Angle{115.0_deg}).get()), 115.0_deg); 
    EXPECT_EQ((clampAngle(Angle{120.0_deg}).get()), 120.0_deg); 
    EXPECT_EQ((clampAngle(Angle{125.0_deg}).get()), 125.0_deg); 
    EXPECT_EQ((clampAngle(Angle{130.0_deg}).get()), 130.0_deg); 
    EXPECT_EQ((clampAngle(Angle{135.0_deg}).get()), 135.0_deg); 
    EXPECT_EQ((clampAngle(Angle{140.0_deg}).get()), 140.0_deg); 
    EXPECT_EQ((clampAngle(Angle{145.0_deg}).get()), 145.0_deg); 
    EXPECT_EQ((clampAngle(Angle{150.0_deg}).get()), 150.0_deg); 
    EXPECT_EQ((clampAngle(Angle{155.0_deg}).get()), 150.0_deg); 
    EXPECT_EQ((clampAngle(Angle{160.0_deg}).get()), 150.0_deg); 
    EXPECT_EQ((clampAngle(Angle{165.0_deg}).get()), 150.0_deg); 
    EXPECT_EQ((clampAngle(Angle{170.0_deg}).get()), 150.0_deg); 
    EXPECT_EQ((clampAngle(Angle{175.0_deg}).get()), 150.0_deg); 
    EXPECT_EQ((clampAngle(Angle{180.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{185.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{190.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{195.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{200.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{205.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{210.0_deg}).get()), 210.0_deg); 
    EXPECT_EQ((clampAngle(Angle{215.0_deg}).get()), 215.0_deg); 
    EXPECT_EQ((clampAngle(Angle{220.0_deg}).get()), 220.0_deg); 
    EXPECT_EQ((clampAngle(Angle{225.0_deg}).get()), 225.0_deg); 
    EXPECT_EQ((clampAngle(Angle{230.0_deg}).get()), 230.0_deg); 
    EXPECT_EQ((clampAngle(Angle{235.0_deg}).get()), 235.0_deg); 
    EXPECT_EQ((clampAngle(Angle{240.0_deg}).get()), 240.0_deg); 
    EXPECT_EQ((clampAngle(Angle{245.0_deg}).get()), 245.0_deg); 
    EXPECT_EQ((clampAngle(Angle{250.0_deg}).get()), 250.0_deg); 
    EXPECT_EQ((clampAngle(Angle{255.0_deg}).get()), 255.0_deg); 
    EXPECT_EQ((clampAngle(Angle{260.0_deg}).get()), 255.0_deg); 
    EXPECT_EQ((clampAngle(Angle{265.0_deg}).get()), 255.0_deg);     
    EXPECT_EQ((clampAngle(Angle{270.0_deg}).get()), 285.0_deg); 
    EXPECT_EQ((clampAngle(Angle{275.0_deg}).get()), 285.0_deg); 
    EXPECT_EQ((clampAngle(Angle{280.0_deg}).get()), 285.0_deg); 
    EXPECT_EQ((clampAngle(Angle{285.0_deg}).get()), 285.0_deg); 
    EXPECT_EQ((clampAngle(Angle{290.0_deg}).get()), 290.0_deg); 
    EXPECT_EQ((clampAngle(Angle{295.0_deg}).get()), 295.0_deg); 
    EXPECT_EQ((clampAngle(Angle{300.0_deg}).get()), 300.0_deg); 
    EXPECT_EQ((clampAngle(Angle{305.0_deg}).get()), 305.0_deg); 
    EXPECT_EQ((clampAngle(Angle{310.0_deg}).get()), 310.0_deg); 
    EXPECT_EQ((clampAngle(Angle{315.0_deg}).get()), 315.0_deg); 
    EXPECT_EQ((clampAngle(Angle{320.0_deg}).get()), 320.0_deg); 
    EXPECT_EQ((clampAngle(Angle{325.0_deg}).get()), 325.0_deg); 
    EXPECT_EQ((clampAngle(Angle{330.0_deg}).get()), 330.0_deg); 
    EXPECT_EQ((clampAngle(Angle{335.0_deg}).get()), 330.0_deg); 
    EXPECT_EQ((clampAngle(Angle{340.0_deg}).get()), 330.0_deg); 
    EXPECT_EQ((clampAngle(Angle{345.0_deg}).get()), 330.0_deg); 
    EXPECT_EQ((clampAngle(Angle{350.0_deg}).get()), 330.0_deg); 
    EXPECT_EQ((clampAngle(Angle{355.0_deg}).get()), 330.0_deg); 
    EXPECT_EQ((clampAngle(Angle{360.0_deg}).get()), 360.0_deg); 
}


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
