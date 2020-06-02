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

TEST(RGBColorTest, Constructor_throws_invald_argument)
{
    EXPECT_THROW((RGBColor{0x00 - 1, 0x00, 0x00, 0x00}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0x00, 0x00 - 1, 0x00, 0x00}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0x00, 0x00, 0x00 - 1, 0x00}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0x00, 0x00, 0x00, 0x00 - 1}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0xFF + 1, 0x00, 0x00, 0x00}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0x00, 0xFF + 1, 0x00, 0x00}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0x00, 0x00, 0xFF + 1, 0x00}), std::invalid_argument);
    EXPECT_THROW((RGBColor{0x00, 0x00, 0x00, 0xFF + 1}), std::invalid_argument);
}