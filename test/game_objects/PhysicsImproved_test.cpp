#include "gtest/gtest.h"

#include "../../include/game_objects/Ball.h"
#include "../../include/game_objects/Brick.h"
#include "../../include/game_objects/IndestructibleBrick.h"
#include "../../include/game_objects/PhysicsImproved.h"
#include "../../include/game_objects/Wall.h"

#include "../../include/utility/OperatorDegree.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::game_objects::improved;
using namespace bricks::types;
using namespace bricks::utility;

class ReflectHorizontalParametersTests
    : public ::testing::TestWithParam<
          std::tuple<Point, double, Point, double, int>> {
protected:
};

TEST_P(ReflectHorizontalParametersTests, CheckResults)
{
    auto ballTopLeft = std::get<0>(GetParam());
    auto ballAngle = std::get<1>(GetParam());
    auto ballResultTopLeft = std::get<2>(GetParam());
    auto ballResultAngle = std::get<3>(GetParam());
    auto hitObjectsCount = std::get<4>(GetParam());

    Ball ball{ballTopLeft,   Width{3.0},       Height{2.5},
              Velocity{1.0}, Angle{ballAngle}, Gravity{0.0}};

    std::vector<Brick> bricks{
        Brick{Point{3.0, 1.0}, Width{4.0}, Height{4.0}, Hitpoints{1}},
        Brick{Point{3.0, 5.0}, Width{4.0}, Height{4.0}, Hitpoints{1}},
        Brick{Point{3.0, 9.0}, Width{4.0}, Height{4.0}, Hitpoints{1}},
    };

    std::vector<std::shared_ptr<GameObject>> hitObjects =
        reflectFromGameObjects(ball, std::vector<Wall>{},
                               std::vector<IndestructibleBrick>{}, bricks);

    EXPECT_EQ(hitObjects.size(), hitObjectsCount);
    EXPECT_EQ(ball.topLeft().x, ballResultTopLeft.x);
    EXPECT_EQ(ball.topLeft().y, ballResultTopLeft.y);
    EXPECT_NEAR(ball.angle().get(), ballResultAngle, 0.1);
}

INSTANTIATE_TEST_SUITE_P(
    ReflectHorizontalTests, ReflectHorizontalParametersTests,
    ::testing::Values(std::make_tuple(Point{1.0, 0.0}, 30.0_deg,
                                      Point{0.0, 0.0}, 150.0_deg, 1),
                      std::make_tuple(Point{1.0, 3.0}, 30.0_deg,
                                      Point{0.0, 3.0}, 150.0_deg, 2),
                      std::make_tuple(Point{1.0, 6.0}, 30.0_deg,
                                      Point{0.0, 6.0}, 150.0_deg, 1),
                      std::make_tuple(Point{1.0, 8.0}, 30.0_deg,
                                      Point{0.0, 8.0}, 150.0_deg, 2),
                      std::make_tuple(Point{1.0, 11.0}, 30.0_deg,
                                      Point{0.0, 11.0}, 150.0_deg, 1),
                      std::make_tuple(Point{1.0, 0.0}, 330.0_deg,
                                      Point{0.0, 0.0}, 210.0_deg, 1),
                      std::make_tuple(Point{1.0, 3.0}, 330.0_deg,
                                      Point{0.0, 3.0}, 210.0_deg, 2),
                      std::make_tuple(Point{1.0, 6.0}, 330.0_deg,
                                      Point{0.0, 6.0}, 210.0_deg, 1),
                      std::make_tuple(Point{1.0, 8.0}, 330.0_deg,
                                      Point{0.0, 8.0}, 210.0_deg, 2),
                      std::make_tuple(Point{1.0, 11.0}, 330.0_deg,
                                      Point{0.0, 11.0}, 210.0_deg, 1),
                      std::make_tuple(Point{6.0, 0.0}, 150.0_deg,
                                      Point{7.0, 0.0}, 30.0_deg, 1),
                      std::make_tuple(Point{6.0, 3.0}, 150.0_deg,
                                      Point{7.0, 3.0}, 30.0_deg, 2),
                      std::make_tuple(Point{6.0, 6.0}, 150.0_deg,
                                      Point{7.0, 6.0}, 30.0_deg, 1),
                      std::make_tuple(Point{6.0, 8.0}, 150.0_deg,
                                      Point{7.0, 8.0}, 30.0_deg, 2),
                      std::make_tuple(Point{6.0, 11.0}, 150.0_deg,
                                      Point{7.0, 11.0}, 30.0_deg, 1),
                      std::make_tuple(Point{6.0, 0.0}, 210.0_deg,
                                      Point{7.0, 0.0}, 330.0_deg, 1),
                      std::make_tuple(Point{6.0, 3.0}, 210.0_deg,
                                      Point{7.0, 3.0}, 330.0_deg, 2),
                      std::make_tuple(Point{6.0, 6.0}, 210.0_deg,
                                      Point{7.0, 6.0}, 330.0_deg, 1),
                      std::make_tuple(Point{6.0, 8.0}, 210.0_deg,
                                      Point{7.0, 8.0}, 330.0_deg, 2),
                      std::make_tuple(Point{6.0, 11.0}, 210.0_deg,
                                      Point{7.0, 11.0}, 330.0_deg, 1)));

class ReflectVerticalParametersTests
    : public ::testing::TestWithParam<
          std::tuple<Point, double, Point, double, int>> {
protected:
};

TEST_P(ReflectVerticalParametersTests, CheckResults)
{
    auto ballTopLeft = std::get<0>(GetParam());
    auto ballAngle = std::get<1>(GetParam());
    auto ballResultTopLeft = std::get<2>(GetParam());
    auto ballResultAngle = std::get<3>(GetParam());
    auto hitObjectsCount = std::get<4>(GetParam());

    Ball ball{ballTopLeft,   Width{2.5},       Height{3.0},
              Velocity{1.0}, Angle{ballAngle}, Gravity{0.0}};

    std::vector<Brick> bricks{
        Brick{Point{1.0, 3.0}, Width{4.0}, Height{4.0}, Hitpoints{1}},
        Brick{Point{5.0, 3.0}, Width{4.0}, Height{4.0}, Hitpoints{1}},
        Brick{Point{9.0, 3.0}, Width{4.0}, Height{4.0}, Hitpoints{1}},
    };

    std::vector<std::shared_ptr<GameObject>> hitObjects =
        reflectFromGameObjects(ball, std::vector<Wall>{},
                               std::vector<IndestructibleBrick>{}, bricks);

    EXPECT_EQ(hitObjects.size(), hitObjectsCount);
    EXPECT_EQ(ball.topLeft().x, ballResultTopLeft.x);
    EXPECT_EQ(ball.topLeft().y, ballResultTopLeft.y);
    EXPECT_NEAR(ball.angle().get(), ballResultAngle, 0.1);
}

INSTANTIATE_TEST_SUITE_P(
    ReflectVerticalTests, ReflectVerticalParametersTests,
    ::testing::Values(std::make_tuple(Point{0.0, 1.0}, 30.0_deg,
                                      Point{0.0, 0.0}, 330.0_deg, 1),
                      std::make_tuple(Point{3.0, 1.0}, 30.0_deg,
                                      Point{3.0, 0.0}, 330.0_deg, 2),
                      std::make_tuple(Point{6.0, 1.0}, 30.0_deg,
                                      Point{6.0, 0.0}, 330.0_deg, 1),
                      std::make_tuple(Point{8.0, 1.0}, 30.0_deg,
                                      Point{8.0, 0.0}, 330.0_deg, 2),
                      std::make_tuple(Point{11.0, 1.0}, 30.0_deg,
                                      Point{11.0, 0.0}, 330.0_deg, 1),
                      std::make_tuple(Point{0.0, 1.0}, 150.0_deg,
                                      Point{0.0, 0.0}, 210.0_deg, 1),
                      std::make_tuple(Point{3.0, 1.0}, 150.0_deg,
                                      Point{3.0, 0.0}, 210.0_deg, 2),
                      std::make_tuple(Point{6.0, 1.0}, 150.0_deg,
                                      Point{6.0, 0.0}, 210.0_deg, 1),
                      std::make_tuple(Point{8.0, 1.0}, 150.0_deg,
                                      Point{8.0, 0.0}, 210.0_deg, 2),
                      std::make_tuple(Point{11.0, 1.0}, 150.0_deg,
                                      Point{11.0, 0.0}, 210.0_deg, 1),
                      std::make_tuple(Point{0.0, 6.0}, 330.0_deg,
                                      Point{0.0, 7.0}, 30.0_deg, 1),
                      std::make_tuple(Point{3.0, 6.0}, 330.0_deg,
                                      Point{3.0, 7.0}, 30.0_deg, 2),
                      std::make_tuple(Point{6.0, 6.0}, 330.0_deg,
                                      Point{6.0, 7.0}, 30.0_deg, 1),
                      std::make_tuple(Point{8.0, 6.0}, 330.0_deg,
                                      Point{8.0, 7.0}, 30.0_deg, 2),
                      std::make_tuple(Point{11.0, 6.0}, 330.0_deg,
                                      Point{11.0, 7.0}, 30.0_deg, 1),
                      std::make_tuple(Point{0.0, 6.0}, 210.0_deg,
                                      Point{0.0, 7.0}, 150.0_deg, 1),
                      std::make_tuple(Point{3.0, 6.0}, 210.0_deg,
                                      Point{3.0, 7.0}, 150.0_deg, 2),
                      std::make_tuple(Point{6.0, 6.0}, 210.0_deg,
                                      Point{6.0, 7.0}, 150.0_deg, 1),
                      std::make_tuple(Point{8.0, 6.0}, 210.0_deg,
                                      Point{8.0, 7.0}, 150.0_deg, 2),
                      std::make_tuple(Point{11.0, 6.0}, 210.0_deg,
                                      Point{11.0, 7.0}, 150.0_deg, 1)));

class ReflectFromTwoObjectsWithStraightAndCornerParametersTests
    : public ::testing::TestWithParam<
          std::tuple<Point, Point, Point, double, Point, double>> {
protected:
};

TEST_P(ReflectFromTwoObjectsWithStraightAndCornerParametersTests, CheckResults)
{
    auto brick1TopLeft = std::get<0>(GetParam());
    auto brick2TopLeft = std::get<1>(GetParam());
    auto ballTopLeft = std::get<2>(GetParam());
    auto ballAngle = std::get<3>(GetParam());
    auto ballResultTopLeft = std::get<4>(GetParam());
    auto ballResultAngle = std::get<5>(GetParam());

    Ball ball{ballTopLeft,   Width{2.0},       Height{2.0},
              Velocity{1.0}, Angle{ballAngle}, Gravity{0.0}};

    std::vector<Brick> bricks{
        Brick{brick1TopLeft, Width{6.0}, Height{2.0}, Hitpoints{1}},
        Brick{brick2TopLeft, Width{2.0}, Height{6.0}, Hitpoints{1}},
    };

    std::vector<std::shared_ptr<GameObject>> hitObjects =
        reflectFromGameObjects(ball, std::vector<Wall>{},
                               std::vector<IndestructibleBrick>{}, bricks);

    EXPECT_EQ(hitObjects.size(), 2);
    EXPECT_EQ(ball.topLeft().x, ballResultTopLeft.x);
    EXPECT_EQ(ball.topLeft().y, ballResultTopLeft.y);
    EXPECT_NEAR(ball.angle().get(), ballResultAngle, 0.1);
}

INSTANTIATE_TEST_SUITE_P(
    ReflectFromTwoObjectsWithStraightAndCornerTests,
    ReflectFromTwoObjectsWithStraightAndCornerParametersTests,
    ::testing::Values(
        std::make_tuple(Point{2.0, 0.0}, Point{0.0, 0.0}, Point{1.0, 1.0},
                        225.0_deg, Point{2.0, 2.0}, 45.0_deg),
        std::make_tuple(Point{0.0, 0.0}, Point{0.0, 2.0}, Point{1.0, 1.0},
                        225.0_deg, Point{2.0, 2.0}, 45.0_deg),
        std::make_tuple(Point{0.0, 0.0}, Point{6.0, 0.0}, Point{5.0, 1.0},
                        315.0_deg, Point{4.0, 2.0}, 135.0_deg),
        std::make_tuple(Point{0.0, 0.0}, Point{4.0, 2.0}, Point{3.0, 1.0},
                        315.0_deg, Point{2.0, 2.0}, 135.0_deg),
        std::make_tuple(Point{0.0, 6.0}, Point{0.0, 0.0}, Point{1.0, 5.0},
                        135.0_deg, Point{2.0, 4.0}, 315.0_deg),
        std::make_tuple(Point{2.0, 4.0}, Point{0.0, 0.0}, Point{1.0, 3.0},
                        135.0_deg, Point{2.0, 2.0}, 315.0_deg),
        std::make_tuple(Point{0.0, 6.0}, Point{4.0, 0.0}, Point{3.0, 5.0},
                        45.0_deg, Point{2.0, 4.0}, 225.0_deg),
        std::make_tuple(Point{0.0, 4.0}, Point{6.0, 0.0}, Point{5.0, 3.0},
                        45.0_deg, Point{4.0, 2.0}, 225.0_deg)));

class ReflectFromThreeObjectsInCornerParametersTests
    : public ::testing::TestWithParam<
          std::tuple<Point, Point, Point, Point, double, Point, double>> {
protected:
};

TEST_P(ReflectFromThreeObjectsInCornerParametersTests, CheckResults)
{
    auto brick1TopLeft = std::get<0>(GetParam());
    auto brick2TopLeft = std::get<1>(GetParam());
    auto brick3TopLeft = std::get<2>(GetParam());
    auto ballTopLeft = std::get<3>(GetParam());
    auto ballAngle = std::get<4>(GetParam());
    auto ballResultTopLeft = std::get<5>(GetParam());
    auto ballResultAngle = std::get<6>(GetParam());

    Ball ball{ballTopLeft,   Width{2.0},       Height{2.0},
              Velocity{1.0}, Angle{ballAngle}, Gravity{0.0}};

    std::vector<Brick> bricks{
        Brick{brick1TopLeft, Width{3.0}, Height{3.0}, Hitpoints{1}},
        Brick{brick2TopLeft, Width{3.0}, Height{3.0}, Hitpoints{1}},
        Brick{brick3TopLeft, Width{3.0}, Height{3.0}, Hitpoints{1}},
    };

    std::vector<std::shared_ptr<GameObject>> hitObjects =
        reflectFromGameObjects(ball, std::vector<Wall>{},
                               std::vector<IndestructibleBrick>{}, bricks);

    EXPECT_EQ(hitObjects.size(), 3);
    EXPECT_EQ(ball.topLeft().x, ballResultTopLeft.x);
    EXPECT_EQ(ball.topLeft().y, ballResultTopLeft.y);
    EXPECT_NEAR(ball.angle().get(), ballResultAngle, 0.1);
}

INSTANTIATE_TEST_SUITE_P(
    ReflectFromThreeObjectsInCornerTests,
    ReflectFromThreeObjectsInCornerParametersTests,
    ::testing::Values(
        std::make_tuple(Point{0.0, 3.0}, Point{3.0, 3.0}, Point{3.0, 0.0},
                        Point{2.0, 2.0}, 45.0_deg, Point{1.0, 1.0}, 225.0_deg),
        std::make_tuple(Point{3.0, 3.0}, Point{0.0, 3.0}, Point{0.0, 0.0},
                        Point{2.0, 2.0}, 135.0_deg, Point{3.0, 1.0}, 315.0_deg),
        std::make_tuple(Point{0.0, 0.0}, Point{3.0, 0.0}, Point{3.0, 3.0},
                        Point{2.0, 2.0}, 315.0_deg, Point{1.0, 3.0}, 135.0_deg),
        std::make_tuple(Point{0.0, 3.0}, Point{0.0, 0.0}, Point{3.0, 0.0},
                        Point{2.0, 2.0}, 225.0_deg, Point{3.0, 3.0},
                        45.0_deg)));

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

INSTANTIATE_TEST_SUITE_P(
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

INSTANTIATE_TEST_SUITE_P(
    ClampAngleTests, ClampAngleParametersTests,
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
                      std::make_tuple(360.0_deg, 360.0_deg)));
