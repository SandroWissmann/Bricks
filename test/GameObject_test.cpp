#include "gtest/gtest.h"

#include "../src/GameObject.h"

using namespace bricks;
using namespace bricks::types;

class DerivedGameObject : public GameObject {
public:
    DerivedGameObject(Point topLeft, Length length, Height height)
        : GameObject(topLeft, length, height)
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
    DerivedGameObject obj{Point{10.1, 20.2}, Length{10.5}, Height{20.6}};
};

TEST_F(GameObjectTest, topLeft)
{
    EXPECT_EQ(obj.topLeft().x, 10.1);
    EXPECT_EQ(obj.topLeft().y, 20.2);

    obj.setTopLeft(Point{20.3, 30.5});

    EXPECT_EQ(obj.topLeft().x, 20.3);
    EXPECT_EQ(obj.topLeft().y, 30.5);
}

TEST_F(GameObjectTest, bottomRight)
{
    EXPECT_EQ(obj.bottomRight().x, 10.1 + obj.length());
    EXPECT_EQ(obj.bottomRight().y, 20.2 + obj.height());
}

TEST_F(GameObjectTest, length)
{
    EXPECT_EQ(obj.length(), 10.5);
}

TEST_F(GameObjectTest, height)
{
    EXPECT_EQ(obj.height(), 20.6);
}
