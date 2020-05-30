#include "gtest/gtest.h"

#include "../include/Platform.h"

using namespace bricks;
using namespace bricks::types;

TEST(PlatformTest_, defaultConstructor)
{
    Platform platform;

    EXPECT_EQ(platform.topLeft().x, 0.0);
    EXPECT_EQ(platform.topLeft().y, 0.0);
    EXPECT_EQ(platform.width(), 0.0);
    EXPECT_EQ(platform.height(), 0.0);
    EXPECT_EQ(platform.velocity(), 0.0);
}

class PlatformTest : public ::testing::Test {
protected:
    Point point{10.0, 10.0};
    Width width{1.0};
    Height height{1.0};
    Velocity velocity{2.0};

    Platform makePlatform(const Velocity& velocity)
    {
        return Platform{point,        width,       height, velocity};
    }
};

TEST_F(PlatformTest, move_positive)
{
    auto obj = makePlatform(Velocity{2.0});
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x + oldObj.velocity());
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
}

TEST_F(PlatformTest, move_negative)
{
    auto obj = makePlatform(Velocity{-2.0});
    auto oldObj = obj;
    auto timeInMS = 1000;
    obj.move(timeInMS);

    EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x + oldObj.velocity());
    EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
}