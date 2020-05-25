#include "gtest/gtest.h"

#include "../include/RGBColor.h"

// using namespace bricks;
// using namespace bricks::types;

// class PlatformTest : public ::testing::Test {
// protected:
//     Point point{10.0, 10.0};
//     Length length{1.0};
//     Width width{1.0};
//     MaxPositionX maxPositionX{1000.0};
//     MaxPositionY maxPositionY{1000.0};
//     Velocity velocity{2.0};

//     Platform makePlatform(const Velocity &velocity)
//     {
//         return Platform{point,        length,       width,
//                         maxPositionX, maxPositionY, velocity};
//     }
// };

// TEST_F(PlatformTest, move_positive)
// {
//     auto obj = makePlatform(Velocity{2.0});
//     auto oldObj = obj;
//     auto timeInMS = 1000;
//     obj.move(timeInMS);

//     EXPECT_DOUBLE_EQ(obj.topLeft().x, oldObj.topLeft().x + oldObj.velocity());
//     EXPECT_DOUBLE_EQ(obj.topLeft().y, oldObj.topLeft().y);
// }
