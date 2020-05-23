#include "gtest/gtest.h"

#include "../src/MoveableGameObject.h"

using namespace bricks;

class DerivedGameObject : public MoveableGameObject {
public:
    DerivedGameObject(Point topLeft, Width width, Height height, 
    MaxPositionX maxPositionX, MaxPositionY maxPositionY, Velocity velocity)
        : MoveableGameObject(
            topLeft, width, height, maxPositionX, maxPositionY, velocity)
    {
    }

    void move(double /*elapsedTimeInMS*/) override
    {
    }

    ~DerivedGameObject() override = default;
    DerivedGameObject(const DerivedGameObject &) = default;
    DerivedGameObject(DerivedGameObject &&) = default;
    DerivedGameObject &operator=(const DerivedGameObject &other) = default;
    DerivedGameObject &operator=(DerivedGameObject &&other) = default;
};

TEST(MoveableGameObjectTest_F, topLeftGetsClampedOnX)
{
    DerivedGameObject obj{
        Point{10.0, 20.0}, Width{10.0}, Height{20.0},  
        MaxPositionX{50.0}, MaxPositionY{70.0}, Velocity{0.0}};

    constexpr double maxPointX = 50.0 - 10.0;
    constexpr double maxPointY = 70.0 - 20.0;

    obj.setTopLeft(Point{maxPointX + 10, maxPointY + 10});

    EXPECT_EQ(obj.topLeft().x, maxPointX);
    EXPECT_EQ(obj.topLeft().y, maxPointY);
}

class MoveableGameObjectTest : public ::testing::Test {
protected:
    DerivedGameObject obj{
        Point{10.1, 20.2}, Width{10.5},
        Height{20.6}, MaxPositionX{50.3}, MaxPositionY{70.4}, Velocity{2.0} };
};


TEST_F(MoveableGameObjectTest, maxPositionX) { EXPECT_EQ(obj.maxPositionX(), 50.3); }

TEST_F(MoveableGameObjectTest, maxPositionY) { EXPECT_EQ(obj.maxPositionY(), 70.4); }

TEST_F(MoveableGameObjectTest, velocity)
{
    EXPECT_EQ(obj.velocity(), 2.0);

    obj.setVelocity(5.3);

    EXPECT_EQ(obj.velocity(), 5.3);
}