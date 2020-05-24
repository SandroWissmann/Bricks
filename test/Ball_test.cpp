#include "gtest/gtest.h"

#include "../src/Ball.h"
#include "../src/OperatorDegree.h"

using namespace bricks;
using namespace bricks::types;

class BallTest : public ::testing::Test {
protected:
    Point point{10.0, 10.0};
    Length length{1.0};
    Width width{1.0};
    MaxPositionX maxPositionX{1000.0};
    MaxPositionY maxPositionY{1000.0};
    Velocity velocity{2.0};
    Angle angle{30.0_deg};
    Gravity gravity{0.0};

    Ball makeBall(const Velocity &velocity, const Angle &angle,
                  const Gravity &gravity)
    {
        return Ball{point,        length,   width, maxPositionX,
                    maxPositionY, velocity, angle, gravity};
    }
};

TEST_F(BallTest, angle)
{
    auto obj = makeBall(velocity, Angle{30.0_deg}, gravity);

    EXPECT_DOUBLE_EQ(obj.angle().angle(), 30.0_deg);

    obj.setAngle(65.0_deg);

    EXPECT_DOUBLE_EQ(obj.angle().angle(), 65.0_deg);
}

TEST_F(BallTest, gravity)
{
    auto obj = makeBall(velocity, angle, Gravity{2.0});

    EXPECT_DOUBLE_EQ(obj.gravity(), 2.0);

    obj.setGravity(4.0);

    EXPECT_DOUBLE_EQ(obj.gravity(), 4.0);
}

TEST_F(BallTest, move_no_move_if_disabled)
{
    auto obj = makeBall(Velocity{2.0}, Angle{0.0_deg}, Gravity{0.0});
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
}

TEST_F(BallTest, move_onlyGravity)
{
    auto obj = makeBall(Velocity{0.0}, Angle{90.0_deg}, Gravity{2.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y + oldObj.gravity());
}

TEST_F(BallTest, move_angle0)
{
    auto obj = makeBall(Velocity{2.0}, Angle{0.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x + oldObj.velocity());
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
}

TEST_F(BallTest, move_angle30)
{
    auto obj = makeBall(Velocity{2.0}, Angle{30.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 11.732050807568877);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 11);
}

TEST_F(BallTest, move_angle45)
{
    auto obj = makeBall(Velocity{2.0}, Angle{45.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 11.414213562373096);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 11.414213562373096);
}

TEST_F(BallTest, move_angle60)
{
    auto obj = makeBall(Velocity{2.0}, Angle{60.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 11);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 11.732050807568877);
}

TEST_F(BallTest, move_angle90)
{
    auto obj = makeBall(Velocity{2.0}, Angle{90.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y + oldObj.velocity());
}

TEST_F(BallTest, move_angle90_gravity)
{
    auto obj = makeBall(Velocity{2.0}, Angle{90.0_deg}, Gravity{2.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_DOUBLE_EQ(obj.topLeft().y,
                     oldObj.topLeft().y + oldObj.velocity() * 2);
}

TEST_F(BallTest, move_angle120)
{
    auto obj = makeBall(Velocity{2.0}, Angle{120.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 9);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 11.732050807568877);
}

TEST_F(BallTest, move_angle135)
{
    auto obj = makeBall(Velocity{2.0}, Angle{135.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 8.5857864376269042);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 11.414213562373096);
}

TEST_F(BallTest, move_angle180)
{
    auto obj = makeBall(Velocity{2.0}, Angle{180.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x - oldObj.velocity());
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
}

TEST_F(BallTest, move_angle230)
{
    auto obj = makeBall(Velocity{2.0}, Angle{230.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 8.7144247806269206);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 8.4679111137620442);
}

TEST_F(BallTest, move_angle270)
{
    auto obj = makeBall(Velocity{2.0}, Angle{270.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y - oldObj.velocity());
}

TEST_F(BallTest, move_angle315)
{
    auto obj = makeBall(Velocity{2.0}, Angle{315.0_deg}, Gravity{0.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, 11.414213562373096);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, 8.5857864376269042);
}

TEST_F(BallTest, move_angle270_gravity)
{
    auto obj = makeBall(Velocity{2.0}, Angle{270.0_deg}, Gravity{2.0});
    obj.activate();
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
}