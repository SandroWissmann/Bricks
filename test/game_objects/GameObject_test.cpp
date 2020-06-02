#include "gtest/gtest.h"

#include "../../include/game_objects/GameObject.h"

using namespace bricks;
using namespace bricks::game_objects;
using namespace bricks::types;

class DerivedGameObject : public GameObject {
public:
    DerivedGameObject() : GameObject{}
    {
    }

    DerivedGameObject(Point topLeft, Width width, Height height)
        : GameObject(topLeft, width, height)
    {
    }

    ~DerivedGameObject() override = default;
    DerivedGameObject(const DerivedGameObject&) = default;
    DerivedGameObject(DerivedGameObject&&) = default;
    DerivedGameObject& operator=(const DerivedGameObject& other) = default;
    DerivedGameObject& operator=(DerivedGameObject&& other) = default;
};

TEST(GameObjectTest_, defaultConstructor)
{
    DerivedGameObject obj;

    EXPECT_EQ(obj.topLeft().x, 0.0);
    EXPECT_EQ(obj.topLeft().y, 0.0);
    EXPECT_EQ(obj.width(), 0.0);
    EXPECT_EQ(obj.height(), 0.0);
}

DerivedGameObject makeDerrivedGameObject(Point point)
{
    return DerivedGameObject{
        point,
        Width{1},
        Height{1}
    };
}

TEST(GameObjectTest_, Constructor_throws_invald_argument)
{
    EXPECT_THROW((makeDerrivedGameObject(Point{-1,0})), std::invalid_argument);
    EXPECT_THROW((makeDerrivedGameObject(Point{0,-1})), std::invalid_argument);
}

class GameObjectTest : public ::testing::Test {
protected:
    DerivedGameObject obj{Point{10.1, 20.2}, Width{10.5}, Height{20.6}};
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
    EXPECT_EQ(obj.bottomRight().x, 10.1 + obj.width());
    EXPECT_EQ(obj.bottomRight().y, 20.2 + obj.height());
}

TEST_F(GameObjectTest, bottomLeft)
{
    EXPECT_EQ(obj.bottomLeft().x, 10.1);
    EXPECT_EQ(obj.bottomLeft().y, 20.2 + obj.height());
}

TEST_F(GameObjectTest, topRight)
{
    EXPECT_EQ(obj.topRight().x, 10.1 + obj.width());
    EXPECT_EQ(obj.topRight().y, 20.2);
}

TEST_F(GameObjectTest, width)
{
    EXPECT_EQ(obj.width(), 10.5);
}

TEST_F(GameObjectTest, height)
{
    EXPECT_EQ(obj.height(), 20.6);
}
