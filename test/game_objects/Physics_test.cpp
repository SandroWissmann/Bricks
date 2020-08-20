#include "gtest/gtest.h"

#include "../../include/game_objects/Ball.h"
#include "../../include/game_objects/Brick.h"
#include "../../include/game_objects/Physics.h"

#include "../../include/utility/OperatorDegree.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::types;
using namespace bricks::utility;

class CalcAngleFactorParametersTests
    : public ::testing::TestWithParam<std::tuple<double, double>> {
protected:
};

TEST_P(CalcAngleFactorParametersTests, CheckResults)
{
    auto xBall = std::get<0>(GetParam());
    auto expectedResult = std::get<1>(GetParam());

    constexpr double xLeft = 0.0;
    constexpr double xCenter = 1.0;
    constexpr double xRight = 2.0;
    EXPECT_NEAR(calcAngleFactor(xBall, xLeft, xCenter, xRight), expectedResult,
                0.000000001);
}

INSTANTIATE_TEST_CASE_P(
    CalcAngleFactorTests, CalcAngleFactorParametersTests,
    ::testing::Values(std::make_tuple(0.0, 1.0), std::make_tuple(0.25, 0.75),
                      std::make_tuple(0.5, 0.5), std::make_tuple(1.0, 0.0),
                      std::make_tuple(1.5, 0.5), std::make_tuple(1.75, 0.75),
                      std::make_tuple(2.0, 1.0)));

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

TEST_F(CollisionTest, intersectsWithRightX)
{
    EXPECT_FALSE(intersectsWithRightX(ball, brickTopLeft));
    EXPECT_FALSE(intersectsWithRightX(ball, brickTop));
    EXPECT_TRUE(intersectsWithRightX(ball, brickTopRight));
    EXPECT_TRUE(intersectsWithRightX(ball, brickRight));
    EXPECT_TRUE(intersectsWithRightX(ball, brickBottomRight));
    EXPECT_FALSE(intersectsWithRightX(ball, brickBottom));
    EXPECT_FALSE(intersectsWithRightX(ball, brickBottomLeft));
    EXPECT_FALSE(intersectsWithRightX(ball, brickLeft));
}

TEST_F(CollisionTest, intersectsWithLeftX)
{
    EXPECT_TRUE(intersectsWithLeftX(ball, brickTopLeft));
    EXPECT_FALSE(intersectsWithLeftX(ball, brickTop));
    EXPECT_FALSE(intersectsWithLeftX(ball, brickTopRight));
    EXPECT_FALSE(intersectsWithLeftX(ball, brickRight));
    EXPECT_FALSE(intersectsWithLeftX(ball, brickBottomRight));
    EXPECT_FALSE(intersectsWithLeftX(ball, brickBottom));
    EXPECT_TRUE(intersectsWithLeftX(ball, brickBottomLeft));
    EXPECT_TRUE(intersectsWithLeftX(ball, brickLeft));
}

TEST_F(CollisionTest, intersectsWithBottomY)
{
    EXPECT_FALSE(intersectsWithBottomY(ball, brickTopLeft));
    EXPECT_FALSE(intersectsWithBottomY(ball, brickTop));
    EXPECT_FALSE(intersectsWithBottomY(ball, brickTopRight));
    EXPECT_FALSE(intersectsWithBottomY(ball, brickRight));
    EXPECT_TRUE(intersectsWithBottomY(ball, brickBottomRight));
    EXPECT_TRUE(intersectsWithBottomY(ball, brickBottom));
    EXPECT_TRUE(intersectsWithBottomY(ball, brickBottomLeft));
    EXPECT_FALSE(intersectsWithBottomY(ball, brickLeft));
}

TEST_F(CollisionTest, intersectsWithTopY)
{
    EXPECT_TRUE(intersectsWithTopY(ball, brickTopLeft));
    EXPECT_TRUE(intersectsWithTopY(ball, brickTop));
    EXPECT_TRUE(intersectsWithTopY(ball, brickTopRight));
    EXPECT_FALSE(intersectsWithTopY(ball, brickRight));
    EXPECT_FALSE(intersectsWithTopY(ball, brickBottomRight));
    EXPECT_FALSE(intersectsWithTopY(ball, brickBottom));
    EXPECT_FALSE(intersectsWithTopY(ball, brickBottomLeft));
    EXPECT_FALSE(intersectsWithTopY(ball, brickLeft));
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
