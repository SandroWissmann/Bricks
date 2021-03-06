#include "gtest/gtest.h"

#include "../../include/game_objects/MoveableGameObject.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::types;

class DerivedGameObject : public MoveableGameObject {
public:
    DerivedGameObject()  
        
    {
    }

    DerivedGameObject(Point topLeft, Width width, Height height,
                      Velocity velocity)
        : MoveableGameObject(topLeft, width, height, velocity)
    {
    }

    void move(double /*elapsedTimeInMS*/) override
    {
    }

    ~DerivedGameObject() override = default;
    DerivedGameObject(const DerivedGameObject&) = default;
    DerivedGameObject(DerivedGameObject&&) = default;
    DerivedGameObject& operator=(const DerivedGameObject& other) = default;
    DerivedGameObject& operator=(DerivedGameObject&& other) = default;
};

TEST(MoveableGameObjectTest_F, defaultConstructor)
{
    DerivedGameObject obj;

    EXPECT_EQ(obj.topLeft().x, 0.0);
    EXPECT_EQ(obj.topLeft().y, 0.0);
    EXPECT_EQ(obj.width(), 0.0);
    EXPECT_EQ(obj.height(), 0.0);
}

class MoveableGameObjectTest : public ::testing::Test {
protected:
    DerivedGameObject obj{Point{10.1, 20.2}, Width{10.5}, Height{20.6},
                          Velocity{2.0}};
};

TEST_F(MoveableGameObjectTest, velocity)
{
    EXPECT_EQ(obj.velocity(), 2.0);

    obj.setVelocity(5.3);

    EXPECT_EQ(obj.velocity(), 5.3);
}