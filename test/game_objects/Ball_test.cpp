#include "gtest/gtest.h"

#include "../../include/game_objects/Ball.h"
#include "../../include/utility/OperatorDegree.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::game_objects::impl;
using namespace bricks::types;
using namespace bricks::utility;

TEST(BallTest_, defaultConstructor)
{
    Ball ball;

    EXPECT_EQ(ball.topLeft().x, 0.0);
    EXPECT_EQ(ball.topLeft().y, 0.0);
    EXPECT_EQ(ball.width(), 0.0);
    EXPECT_EQ(ball.height(), 0.0);
    EXPECT_EQ(ball.velocity(), 0.0);
    EXPECT_EQ(ball.angle().get(), 0.0);
    EXPECT_EQ(ball.gravity(), 0.0);
    EXPECT_EQ(ball.isActive(), false);
}

class BallTest : public ::testing::Test {
protected:
    Point point{10.0, 10.0};
    Width width{1.0};
    Height height{1.0};
    Velocity velocity{2.0};
    Angle angle{30.0_deg};
    Gravity gravity{0.0};

    Ball makeBall(const Velocity& velocity, const Angle& angle,
                  const Gravity& gravity)
    {
        return Ball{point, width, height, velocity, angle, gravity};
    }
};

TEST_F(BallTest, angle)
{
    auto obj = makeBall(velocity, Angle{30.0_deg}, gravity);

    EXPECT_DOUBLE_EQ(obj.angle().get(), 30.0_deg);

    obj.setAngle(Angle{65.0_deg});

    EXPECT_DOUBLE_EQ(obj.angle().get(), 65.0_deg);
}

TEST_F(BallTest, gravity)
{
    auto obj = makeBall(velocity, angle, Gravity{2.0});

    EXPECT_DOUBLE_EQ(obj.gravity(), 2.0);

    obj.setGravity(4.0);

    EXPECT_DOUBLE_EQ(obj.gravity(), 4.0);
}

class BallMoveMultipleParametersTests
    : public ::testing::TestWithParam<
          std::tuple<bool, double, double, double, Point>> {
protected:
};

TEST_P(BallMoveMultipleParametersTests, CheckIfMovesCorrectly)
{
    // bool active = std::get<0>(GetParam());
    // Velocity velocity{std::get<1>(GetParam())};
    // Angle angle{std::get<2>(GetParam())};
    // Gravity gravity{std::get<3>(GetParam())};
    // Point endPoint = std::get<4>(GetParam());

    // Ball obj{Point{0.0, 0.0}, Width{3.1}, Height{4.2},
    //          velocity,        angle,      gravity};
    // if (active) {
    //     obj.activate();
    // }
    // auto timeInMS = 1000;
    // obj.move(timeInMS);

    // EXPECT_DOUBLE_EQ(obj.topLeft().x, endPoint.x);
    // EXPECT_DOUBLE_EQ(obj.topLeft().y, endPoint.y);
}

INSTANTIATE_TEST_CASE_P(
    BallMoveTests, BallMoveMultipleParametersTests,
    ::testing::Values(
        // not active
        std::make_tuple(false, 2.0, 0.0, 0.0, Point{0.0, 0.0}),
        // only gravity
        std::make_tuple(true, 0.0, 0.0, 2.0, Point{0.0, 2.0}),
        // 0 degrees
        std::make_tuple(true, 2.0, 0.0, 0.0, Point{2.0, 0.0}),
        // 30 degrees
        std::make_tuple(true, 2.0, 30.0, 0.0, Point{1.732050807568877, 1}),
        // 45 degrees
        std::make_tuple(true, 2.0, 45.0, 0.0,
                        Point{1.414213562373096, 1.414213562373096}),
        // 60 degrees
        std::make_tuple(true, 2.0, 60.0, 0.0, Point{1.0, 1.732050807568877}),
        // 90 degrees
        std::make_tuple(true, 2.0, 90.0, 0.0, Point{0.0, 2.0}),
        // 90 degrees + gravity
        std::make_tuple(true, 2.0, 90.0, 2.0, Point{0.0, 4.0}),
        // 120 degrees
        std::make_tuple(true, 2.0, 12.0, 0.0, Point{-1, 1.732050807568877}),
        // 135 degrees
        std::make_tuple(true, 2.0, 135.0, 0.0,
                        Point{-1.41421356237, 1.414213562373096}),
        // 180 degrees
        std::make_tuple(true, 2.0, 180.0, 0.0, Point{-2.0, 0.0}),
        // 230 degrees
        std::make_tuple(true, 2.0, 230.0, 0.0,
                        Point{-1.28557521937, -1.53208888624}),
        // 270 degrees
        std::make_tuple(true, 2.0, 270.0, 0.0, Point{0.0, -2.0}),
        // 270 degrees + gravity
        std::make_tuple(true, 2.0, 270.0, 2.0, Point{0.0, -2.0})));

// INSTANTIATE_TEST_CASE_P(BallMoveTests, BallMoveMultipleParametersTests,
//                         ::testing::Values(std::make_tuple(
//                             false, 2.0, 0.0, 0.0,
//                             bricks::types::Point{0.0, 0.0}) // not active
//                                           ));