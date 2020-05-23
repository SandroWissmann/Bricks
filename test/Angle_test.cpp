#include "gtest/gtest.h"

#include "../src/Angle.h"
#include "../src/OperatorDegree.h"

using namespace bricks;

TEST(AngleTest, angle)
{
    Angle obj{30.0_deg};

    EXPECT_EQ(obj.angle(), 30.0_deg);

    obj.setAngle(65.0_deg);

    EXPECT_EQ(obj.angle(), 65.0_deg);
}

TEST(AngleTest, quadrantAngle)
{
    Angle obj{30.0_deg};

    EXPECT_DOUBLE_EQ(obj.angle(), 30.0_deg);
    EXPECT_DOUBLE_EQ(obj.quadrantAngle(), 30.0_deg);

    obj.setQuadrantAngle(60.0_deg);

    EXPECT_DOUBLE_EQ(obj.angle(), 60.0_deg);
    EXPECT_DOUBLE_EQ(obj.quadrantAngle(), 60.0_deg);
}

TEST(AngleTest, quadrant)
{
    Angle obj{30.0_deg};

    EXPECT_EQ(obj.quadrant(), Quadrant::I);

    obj.setQuadrant(Quadrant::III);

    EXPECT_EQ(obj.quadrant(), Quadrant::III);
}

TEST(calcQuadrant, Expect_FALSE)
{
    EXPECT_EQ(impl::calcQuadrant(0.0_deg), Quadrant::I);
    EXPECT_EQ(impl::calcQuadrant(45.0_deg), Quadrant::I);
    EXPECT_EQ(impl::calcQuadrant(90.0_deg), Quadrant::I);
    EXPECT_EQ(impl::calcQuadrant(90.1_deg), Quadrant::II);
    EXPECT_EQ(impl::calcQuadrant(135.0_deg), Quadrant::II);
    EXPECT_EQ(impl::calcQuadrant(180.0_deg), Quadrant::II);
    EXPECT_EQ(impl::calcQuadrant(180.1_deg), Quadrant::III);
    EXPECT_EQ(impl::calcQuadrant(225.0_deg), Quadrant::III);
    EXPECT_EQ(impl::calcQuadrant(270.0_deg), Quadrant::III);
    EXPECT_EQ(impl::calcQuadrant(270.1_deg), Quadrant::IV);
    EXPECT_EQ(impl::calcQuadrant(315.0_deg), Quadrant::IV);
    EXPECT_EQ(impl::calcQuadrant(360.0_deg), Quadrant::IV);
}

TEST(isInQuadrantI, Expect_TRUE)
{
    EXPECT_TRUE(impl::isInQuadrantI(0.0_deg));
    EXPECT_TRUE(impl::isInQuadrantI(45.0_deg));
    EXPECT_TRUE(impl::isInQuadrantI(90.0_deg));
}

TEST(isInQuadrantI, Expect_FALSE)
{
    EXPECT_FALSE(impl::isInQuadrantI(90.1_deg));
    EXPECT_FALSE(impl::isInQuadrantI(135.0_deg));
    EXPECT_FALSE(impl::isInQuadrantI(180.0_deg));
    EXPECT_FALSE(impl::isInQuadrantI(180.1_deg));
    EXPECT_FALSE(impl::isInQuadrantI(225.0_deg));
    EXPECT_FALSE(impl::isInQuadrantI(270.0_deg));
    EXPECT_FALSE(impl::isInQuadrantI(270.1_deg));
    EXPECT_FALSE(impl::isInQuadrantI(315.0_deg));
    EXPECT_FALSE(impl::isInQuadrantI(360.0_deg));
}

TEST(isInQuadrantII, Expect_TRUE)
{
    EXPECT_TRUE(impl::isInQuadrantII(90.1_deg));
    EXPECT_TRUE(impl::isInQuadrantII(135.0_deg));
    EXPECT_TRUE(impl::isInQuadrantII(180.0_deg));
}

TEST(isInQuadrantII, Expect_FALSE)
{
    EXPECT_FALSE(impl::isInQuadrantII(0.0_deg));
    EXPECT_FALSE(impl::isInQuadrantII(45.0_deg));
    EXPECT_FALSE(impl::isInQuadrantII(90.0_deg));
    EXPECT_FALSE(impl::isInQuadrantII(180.1_deg));
    EXPECT_FALSE(impl::isInQuadrantII(225.0_deg));
    EXPECT_FALSE(impl::isInQuadrantII(270.0_deg));
    EXPECT_FALSE(impl::isInQuadrantII(270.1_deg));
    EXPECT_FALSE(impl::isInQuadrantII(315.0_deg));
    EXPECT_FALSE(impl::isInQuadrantII(360.0_deg));
}

TEST(isInQuadrantIII, Expect_TRUE)
{
    EXPECT_TRUE(impl::isInQuadrantIII(180.1_deg));
    EXPECT_TRUE(impl::isInQuadrantIII(225.0_deg));
    EXPECT_TRUE(impl::isInQuadrantIII(270.0_deg));
}

TEST(isInQuadrantIII, Expect_FALSE)
{
    EXPECT_FALSE(impl::isInQuadrantIII(0.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(45.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(90.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(90.1_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(135.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(180.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(270.1_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(315.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIII(360.0_deg));
}

TEST(isInQuadrantIV, Expect_TRUE)
{
    EXPECT_TRUE(impl::isInQuadrantIV(270.1_deg));
    EXPECT_TRUE(impl::isInQuadrantIV(315.0_deg));
    EXPECT_TRUE(impl::isInQuadrantIV(360.0_deg));
}

TEST(isInQuadrantIV, Expect_FALSE)
{
    EXPECT_FALSE(impl::isInQuadrantIV(0.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(45.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(90.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(90.1_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(135.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(180.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(180.1_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(225.0_deg));
    EXPECT_FALSE(impl::isInQuadrantIV(270.0_deg));
}

TEST(calcAngleIfOver360, Expect_FALSE)
{
    EXPECT_DOUBLE_EQ(impl::calcAngleIfOver360(0.0_deg), 0.0_deg);
    EXPECT_DOUBLE_EQ(impl::calcAngleIfOver360(360.0_deg), 360.0_deg);
    EXPECT_DOUBLE_EQ(impl::calcAngleIfOver360(360.1_deg), 0.1_deg);
    EXPECT_DOUBLE_EQ(impl::calcAngleIfOver360(540.0_deg), 180.0_deg);
}