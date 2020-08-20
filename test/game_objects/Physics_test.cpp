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

class ClampAngleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, double>> {
protected:
};

TEST_P(ClampAngleParametersTests, CheckResults)
{
    auto input_angle = std::get<0>(GetParam());
    auto output_angle = std::get<1>(GetParam());

    EXPECT_NEAR((clampAngle(Angle{input_angle}).get()), output_angle, 0.1);
}

INSTANTIATE_TEST_CASE_P(ClampAngleTests, ClampAngleParametersTests,
                        ::testing::Values(std::make_tuple(0.0_deg, 30.0_deg),
                                          std::make_tuple(5.0_deg, 30.0_deg),
                                          std::make_tuple(10.0_deg, 30.0_deg),
                                          std::make_tuple(15.0_deg, 30.0_deg),
                                          std::make_tuple(20.0_deg, 30.0_deg),
                                          std::make_tuple(25.0_deg, 30.0_deg),
                                          std::make_tuple(30.0_deg, 30.0_deg),
                                          std::make_tuple(35.0_deg, 35.0_deg),
                                          std::make_tuple(40.0_deg, 40.0_deg),
                                          std::make_tuple(45.0_deg, 45.0_deg),
                                          std::make_tuple(50.0_deg, 50.0_deg),
                                          std::make_tuple(55.0_deg, 55.0_deg),
                                          std::make_tuple(60.0_deg, 60.0_deg),
                                          std::make_tuple(65.0_deg, 65.0_deg),
                                          std::make_tuple(70.0_deg, 70.0_deg),
                                          std::make_tuple(75.0_deg, 75.0_deg),
                                          std::make_tuple(80.0_deg, 75.0_deg),
                                          std::make_tuple(85.0_deg, 75.0_deg),
                                          std::make_tuple(90.0_deg, 105.0_deg),
                                          std::make_tuple(95.0_deg, 105.0_deg),
                                          std::make_tuple(100.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(105.0_deg, 105.0_deg),
                                          std::make_tuple(110.0_deg, 110.0_deg),
                                          std::make_tuple(115.0_deg, 115.0_deg),
                                          std::make_tuple(120.0_deg, 120.0_deg),
                                          std::make_tuple(125.0_deg, 125.0_deg),
                                          std::make_tuple(130.0_deg, 130.0_deg),
                                          std::make_tuple(135.0_deg, 135.0_deg),
                                          std::make_tuple(140.0_deg, 140.0_deg),
                                          std::make_tuple(145.0_deg, 145.0_deg),
                                          std::make_tuple(150.0_deg, 150.0_deg),
                                          std::make_tuple(155.0_deg, 150.0_deg),
                                          std::make_tuple(160.0_deg, 150.0_deg),
                                          std::make_tuple(165.0_deg, 150.0_deg),
                                          std::make_tuple(170.0_deg, 150.0_deg),
                                          std::make_tuple(175.0_deg, 150.0_deg),
                                          std::make_tuple(180.0_deg, 210.0_deg),
                                          std::make_tuple(185.0_deg, 210.0_deg),
                                          std::make_tuple(190.0_deg, 210.0_deg),
                                          std::make_tuple(195.0_deg, 210.0_deg),
                                          std::make_tuple(200.0_deg, 210.0_deg),
                                          std::make_tuple(205.0_deg, 210.0_deg),
                                          std::make_tuple(210.0_deg, 210.0_deg),
                                          std::make_tuple(215.0_deg, 215.0_deg),
                                          std::make_tuple(220.0_deg, 220.0_deg),
                                          std::make_tuple(225.0_deg, 225.0_deg),
                                          std::make_tuple(230.0_deg, 230.0_deg),
                                          std::make_tuple(235.0_deg, 235.0_deg),
                                          std::make_tuple(240.0_deg, 240.0_deg),
                                          std::make_tuple(245.0_deg, 245.0_deg),
                                          std::make_tuple(250.0_deg, 250.0_deg),
                                          std::make_tuple(255.0_deg, 255.0_deg),
                                          std::make_tuple(260.0_deg, 255.0_deg),
                                          std::make_tuple(265.0_deg, 255.0_deg),
                                          std::make_tuple(270.0_deg, 285.0_deg),
                                          std::make_tuple(275.0_deg, 285.0_deg),
                                          std::make_tuple(280.0_deg, 285.0_deg),
                                          std::make_tuple(285.0_deg, 285.0_deg),
                                          std::make_tuple(290.0_deg, 290.0_deg),
                                          std::make_tuple(295.0_deg, 295.0_deg),
                                          std::make_tuple(300.0_deg, 300.0_deg),
                                          std::make_tuple(305.0_deg, 305.0_deg),
                                          std::make_tuple(310.0_deg, 310.0_deg),
                                          std::make_tuple(315.0_deg, 315.0_deg),
                                          std::make_tuple(320.0_deg, 320.0_deg),
                                          std::make_tuple(325.0_deg, 325.0_deg),
                                          std::make_tuple(330.0_deg, 330.0_deg),
                                          std::make_tuple(335.0_deg, 330.0_deg),
                                          std::make_tuple(340.0_deg, 330.0_deg),
                                          std::make_tuple(345.0_deg, 330.0_deg),
                                          std::make_tuple(350.0_deg, 330.0_deg),
                                          std::make_tuple(355.0_deg, 330.0_deg),
                                          std::make_tuple(360.0_deg,
                                                          360.0_deg)));

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
