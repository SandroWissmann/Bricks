#include "gtest/gtest.h"

#include "../src/GameObject.h"
#include "../src/OperatorDegree.h"

using namespace bricks;

class DerivedGameObject : public GameObject {
public:
    DerivedGameObject(Point topLeft, MaxPositionX maxPositionX,
                      MaxPositionY maxPositionY, Width width, Height height,
                      Velocity velocity, Angle angle)
        : GameObject(topLeft, maxPositionX, maxPositionY, width, height,
                     velocity, angle)
    {
    }

    ~DerivedGameObject() override = default;
    DerivedGameObject(const DerivedGameObject &) = default;
    DerivedGameObject(DerivedGameObject &&) = default;
    DerivedGameObject &operator=(const DerivedGameObject &other) = default;
    DerivedGameObject &operator=(DerivedGameObject &&other) = default;
};

class GameObjectTest : public ::testing::Test {
protected:
    DerivedGameObject obj{
        Point{10.1, 20.2}, MaxPositionX{50.3}, MaxPositionY{70.4}, Width{10.5},
        Height{20.6},      Velocity{2.0},      Angle{30.0_deg}};
};

TEST_F(GameObjectTest, topLeft)
{
    EXPECT_EQ(obj.topLeft().x, 10.1);
    EXPECT_EQ(obj.topLeft().y, 20.2);

    obj.setTopLeft(Point{20.3, 30.5});

    EXPECT_EQ(obj.topLeft().x, 20.3);
    EXPECT_EQ(obj.topLeft().y, 30.5);
}

TEST(GameObjectTest_F, topLeftGetsClampedOnX)
{
    DerivedGameObject obj{
        Point{10.0, 20.0}, MaxPositionX{50.0}, MaxPositionY{70.0}, Width{10.0},
        Height{20.0},      Velocity{0.0},      Angle{0.0_deg}};

    constexpr double maxPointX = 50.0 - 10.0;
    constexpr double maxPointY = 70.0 - 20.0;

    obj.setTopLeft(Point{maxPointX + 10, maxPointY + 10});

    EXPECT_EQ(obj.topLeft().x, maxPointX);
    EXPECT_EQ(obj.topLeft().y, maxPointY);
}

TEST_F(GameObjectTest, bottomRight)
{
    EXPECT_EQ(obj.bottomRight().x, 10.1 + obj.width());
    EXPECT_EQ(obj.bottomRight().y, 20.2 + obj.height());
}

TEST_F(GameObjectTest, width) { EXPECT_EQ(obj.width(), 10.5); }

TEST_F(GameObjectTest, height) { EXPECT_EQ(obj.height(), 20.6); }

TEST_F(GameObjectTest, maxPositionX) { EXPECT_EQ(obj.maxPositionX(), 50.3); }

TEST_F(GameObjectTest, maxPositionY) { EXPECT_EQ(obj.maxPositionY(), 70.4); }

TEST_F(GameObjectTest, velocity)
{
    EXPECT_EQ(obj.velocity(), 2.0);

    obj.setVelocity(5.3);

    EXPECT_EQ(obj.velocity(), 5.3);
}

TEST_F(GameObjectTest, angle)
{
    EXPECT_EQ(obj.angle().angle(), 30.0_deg);

    obj.setAngle(65.0_deg);

    EXPECT_EQ(obj.angle().angle(), 65.0_deg);
}

