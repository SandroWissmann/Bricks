#include "gtest/gtest.h"

#include "../src/GameObject.h"
#include "../src/GameObjectPhysics.h"
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

TEST(move, newPositionCorrect_angle0)
{
    DerivedGameObject obj{Point{10.0, 10.0},    MaxPositionX{1000.0},
                          MaxPositionY{1000.0}, Width{1.0},
                          Height{1.0},          Velocity{2.0},
                          Angle{0.0_deg}};

    DerivedGameObject oldObj = obj;

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y);

    auto timeInMS = 1000;

    move(obj, timeInMS);

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x + oldObj.velocity());
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y);
}

TEST(move, newPositionCorrect_angle90)
{
    DerivedGameObject obj{Point{10.0, 10.0},    MaxPositionX{1000.0},
                          MaxPositionY{1000.0}, Width{1.0},
                          Height{1.0},          Velocity{2.0},
                          Angle{90.0_deg}};

    DerivedGameObject oldObj = obj;

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y);

    auto timeInMS = 1000;

    move(obj, timeInMS);

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y + oldObj.velocity());
}

TEST(move, newPositionCorrect_angle180)
{
    DerivedGameObject obj{Point{10.0, 10.0},    MaxPositionX{1000.0},
                          MaxPositionY{1000.0}, Width{1.0},
                          Height{1.0},          Velocity{2.0},
                          Angle{180.0_deg}};

    DerivedGameObject oldObj = obj;

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y);

    auto timeInMS = 1000;

    move(obj, timeInMS);

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x - oldObj.velocity());
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y);
}

TEST(move, newPositionCorrect_angle270)
{
    DerivedGameObject obj{Point{10.0, 10.0},    MaxPositionX{1000.0},
                          MaxPositionY{1000.0}, Width{1.0},
                          Height{1.0},          Velocity{2.0},
                          Angle{270.0_deg}};

    DerivedGameObject oldObj = obj;

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y);

    auto timeInMS = 1000;

    move(obj, timeInMS);

    EXPECT_EQ(obj.topLeft().x, oldObj.topLeft().x);
    EXPECT_EQ(obj.topLeft().y, oldObj.topLeft().y - oldObj.velocity());
}