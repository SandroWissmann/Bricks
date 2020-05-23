#include "gtest/gtest.h"

#include "../../src/OperatorDegree.h"
#include "../../src/types/Angle.h"

using namespace bricks;
using namespace bricks::types::impl;
using Angle = bricks::types::Angle;
using Quadrant = bricks::types::Quadrant;

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
    EXPECT_EQ(calcQuadrant(0.0_deg), Quadrant::I);
    EXPECT_EQ(calcQuadrant(45.0_deg), Quadrant::I);
    EXPECT_EQ(calcQuadrant(90.0_deg), Quadrant::I);
    EXPECT_EQ(calcQuadrant(90.1_deg), Quadrant::II);
    EXPECT_EQ(calcQuadrant(135.0_deg), Quadrant::II);
    EXPECT_EQ(calcQuadrant(180.0_deg), Quadrant::II);
    EXPECT_EQ(calcQuadrant(180.1_deg), Quadrant::III);
    EXPECT_EQ(calcQuadrant(225.0_deg), Quadrant::III);
    EXPECT_EQ(calcQuadrant(270.0_deg), Quadrant::III);
    EXPECT_EQ(calcQuadrant(270.1_deg), Quadrant::IV);
    EXPECT_EQ(calcQuadrant(315.0_deg), Quadrant::IV);
    EXPECT_EQ(calcQuadrant(360.0_deg), Quadrant::IV);
}

TEST(isInQuadrantI, Expect_TRUE)
{
    EXPECT_TRUE(isInQuadrantI(0.0_deg));
    EXPECT_TRUE(isInQuadrantI(45.0_deg));
    EXPECT_TRUE(isInQuadrantI(90.0_deg));
}

TEST(isInQuadrantI, Expect_FALSE)
{
    EXPECT_FALSE(isInQuadrantI(90.1_deg));
    EXPECT_FALSE(isInQuadrantI(135.0_deg));
    EXPECT_FALSE(isInQuadrantI(180.0_deg));
    EXPECT_FALSE(isInQuadrantI(180.1_deg));
    EXPECT_FALSE(isInQuadrantI(225.0_deg));
    EXPECT_FALSE(isInQuadrantI(270.0_deg));
    EXPECT_FALSE(isInQuadrantI(270.1_deg));
    EXPECT_FALSE(isInQuadrantI(315.0_deg));
    EXPECT_FALSE(isInQuadrantI(360.0_deg));
}

TEST(isInQuadrantII, Expect_TRUE)
{
    EXPECT_TRUE(isInQuadrantII(90.1_deg));
    EXPECT_TRUE(isInQuadrantII(135.0_deg));
    EXPECT_TRUE(isInQuadrantII(180.0_deg));
}

TEST(isInQuadrantII, Expect_FALSE)
{
    EXPECT_FALSE(isInQuadrantII(0.0_deg));
    EXPECT_FALSE(isInQuadrantII(45.0_deg));
    EXPECT_FALSE(isInQuadrantII(90.0_deg));
    EXPECT_FALSE(isInQuadrantII(180.1_deg));
    EXPECT_FALSE(isInQuadrantII(225.0_deg));
    EXPECT_FALSE(isInQuadrantII(270.0_deg));
    EXPECT_FALSE(isInQuadrantII(270.1_deg));
    EXPECT_FALSE(isInQuadrantII(315.0_deg));
    EXPECT_FALSE(isInQuadrantII(360.0_deg));
}

TEST(isInQuadrantIII, Expect_TRUE)
{
    EXPECT_TRUE(isInQuadrantIII(180.1_deg));
    EXPECT_TRUE(isInQuadrantIII(225.0_deg));
    EXPECT_TRUE(isInQuadrantIII(270.0_deg));
}

TEST(isInQuadrantIII, Expect_FALSE)
{
    EXPECT_FALSE(isInQuadrantIII(0.0_deg));
    EXPECT_FALSE(isInQuadrantIII(45.0_deg));
    EXPECT_FALSE(isInQuadrantIII(90.0_deg));
    EXPECT_FALSE(isInQuadrantIII(90.1_deg));
    EXPECT_FALSE(isInQuadrantIII(135.0_deg));
    EXPECT_FALSE(isInQuadrantIII(180.0_deg));
    EXPECT_FALSE(isInQuadrantIII(270.1_deg));
    EXPECT_FALSE(isInQuadrantIII(315.0_deg));
    EXPECT_FALSE(isInQuadrantIII(360.0_deg));
}

TEST(isInQuadrantIV, Expect_TRUE)
{
    EXPECT_TRUE(isInQuadrantIV(270.1_deg));
    EXPECT_TRUE(isInQuadrantIV(315.0_deg));
    EXPECT_TRUE(isInQuadrantIV(360.0_deg));
}

TEST(isInQuadrantIV, Expect_FALSE)
{
    EXPECT_FALSE(isInQuadrantIV(0.0_deg));
    EXPECT_FALSE(isInQuadrantIV(45.0_deg));
    EXPECT_FALSE(isInQuadrantIV(90.0_deg));
    EXPECT_FALSE(isInQuadrantIV(90.1_deg));
    EXPECT_FALSE(isInQuadrantIV(135.0_deg));
    EXPECT_FALSE(isInQuadrantIV(180.0_deg));
    EXPECT_FALSE(isInQuadrantIV(180.1_deg));
    EXPECT_FALSE(isInQuadrantIV(225.0_deg));
    EXPECT_FALSE(isInQuadrantIV(270.0_deg));
}

TEST(calcAngleIfOver360, Expect_FALSE)
{
    EXPECT_DOUBLE_EQ(calcAngleIfOver360(0.0_deg), 0.0_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOver360(360.0_deg), 360.0_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOver360(360.1_deg), 0.1_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOver360(540.0_deg), 180.0_deg);
}