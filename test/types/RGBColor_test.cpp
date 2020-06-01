#include "gtest/gtest.h"

#include "../../include/types/RGBColor.h"

using namespace bricks::types;

TEST(RGBColorTest, Constructor)
{
    RGBColor rgbColor{0x20, 0x10, 0x30, 0x40};
    EXPECT_EQ(rgbColor.r(), 0x20);
    EXPECT_EQ(rgbColor.g(), 0x10);
    EXPECT_EQ(rgbColor.b(), 0x30);
    EXPECT_EQ(rgbColor.a(), 0x40);
}
