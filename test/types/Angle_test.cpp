#include "gtest/gtest.h"

#include "../../include/types/Angle.h"

#include "../../include/utility/OperatorDegree.h"

using namespace bricks;
using namespace bricks::types::impl;
using namespace bricks::utility;

using Angle = bricks::types::Angle;
using Quadrant = bricks::types::Quadrant;

TEST(AngleTest, defaultConstructor)
{
    Angle obj;
    EXPECT_EQ(obj.get(), 0.0);
    EXPECT_EQ(obj.quadrant(), Quadrant::I);
    EXPECT_EQ(obj.quadrantAngle(), 0.0);
}

TEST(AngleTest, getSet)
{
    Angle obj{30.0_deg};
    EXPECT_EQ(obj.get(), 30.0_deg);

    obj.set(65.0_deg);
    EXPECT_EQ(obj.get(), 65.0_deg);
}

TEST(AngleTest, quadrantAngle)
{
    Angle obj{30.0_deg};
    EXPECT_DOUBLE_EQ(obj.get(), 30.0_deg);
    EXPECT_DOUBLE_EQ(obj.quadrantAngle(), 30.0_deg);

    obj.setQuadrantAngle(60.0_deg);
    EXPECT_DOUBLE_EQ(obj.get(), 60.0_deg);
    EXPECT_DOUBLE_EQ(obj.quadrantAngle(), 60.0_deg);
}

TEST(AngleTest, quadrant)
{
    Angle obj{30.0_deg};
    EXPECT_EQ(obj.quadrant(), Quadrant::I);

    obj.setQuadrant(Quadrant::III);
    EXPECT_EQ(obj.quadrant(), Quadrant::III);
}

class AngleMirrorHorizontalMultipleParametersTests
    : public ::testing::TestWithParam<
          std::tuple<Quadrant, Quadrant, double, double>> {
protected:
};

TEST_P(AngleMirrorHorizontalMultipleParametersTests, mirrorHorizontal)
{
    auto quadrantBefore = std::get<0>(GetParam());
    auto quadrantAfter = std::get<1>(GetParam());
    auto angleBefore = std::get<2>(GetParam());
    auto angleAfter = std::get<3>(GetParam());

    Angle obj{angleBefore};
    EXPECT_EQ(obj.quadrant(), quadrantBefore);

    obj.mirrorHorizontal();
    EXPECT_EQ(obj.quadrant(), quadrantAfter);
    EXPECT_NEAR(obj.get(), angleAfter, 0.000000001);
}

INSTANTIATE_TEST_SUITE_P(
    AngleMirrorHorizontalTests, AngleMirrorHorizontalMultipleParametersTests,
    ::testing::Values(
        std::make_tuple(Quadrant::I, Quadrant::IV, 30.0_deg, 330.0_deg),
        std::make_tuple(Quadrant::II, Quadrant::III, 120.0_deg, 240.0_deg),
        std::make_tuple(Quadrant::III, Quadrant::II, 240.0_deg, 120.0_deg),
        std::make_tuple(Quadrant::IV, Quadrant::I, 330.0_deg, 30.0_deg)));

class AngleMirrorVerticalMultipleParametersTests
    : public ::testing::TestWithParam<
          std::tuple<Quadrant, Quadrant, double, double>> {
protected:
};

TEST_P(AngleMirrorVerticalMultipleParametersTests, mirrorVertical)
{
    auto quadrantBefore = std::get<0>(GetParam());
    auto quadrantAfter = std::get<1>(GetParam());
    auto angleBefore = std::get<2>(GetParam());
    auto angleAfter = std::get<3>(GetParam());

    Angle obj{angleBefore};
    EXPECT_EQ(obj.quadrant(), quadrantBefore);

    obj.mirrorVertical();
    EXPECT_EQ(obj.quadrant(), quadrantAfter);
    EXPECT_NEAR(obj.get(), angleAfter, 0.000000001);
}

INSTANTIATE_TEST_SUITE_P(
    AngleMirrorVerticalTests, AngleMirrorVerticalMultipleParametersTests,
    ::testing::Values(
        std::make_tuple(Quadrant::I, Quadrant::II, 30.0_deg, 150.0_deg),
        std::make_tuple(Quadrant::II, Quadrant::I, 150.0_deg, 30.0_deg),
        std::make_tuple(Quadrant::III, Quadrant::IV, 210.0_deg, 330.0_deg),
        std::make_tuple(Quadrant::IV, Quadrant::III, 330.0_deg, 210.0_deg)));

class CalcQuadrantMultipleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, Quadrant>> {
protected:
};

TEST_P(CalcQuadrantMultipleParametersTests, CalcQuadrant)
{
    auto angle = std::get<0>(GetParam());
    auto quadrant = std::get<1>(GetParam());
    EXPECT_EQ(calcQuadrant(angle), quadrant);
}

INSTANTIATE_TEST_SUITE_P(
    CalcQuadrantTests, CalcQuadrantMultipleParametersTests,
    ::testing::Values(std::make_tuple(0.0_deg, Quadrant::I),
                      std::make_tuple(45.0_deg, Quadrant::I),
                      std::make_tuple(90.0_deg, Quadrant::I),
                      std::make_tuple(90.1_deg, Quadrant::II),
                      std::make_tuple(135.0_deg, Quadrant::II),
                      std::make_tuple(180.0_deg, Quadrant::II),
                      std::make_tuple(180.1_deg, Quadrant::III),
                      std::make_tuple(225.0_deg, Quadrant::III),
                      std::make_tuple(270.0_deg, Quadrant::III),
                      std::make_tuple(270.1_deg, Quadrant::IV),
                      std::make_tuple(315.0_deg, Quadrant::IV),
                      std::make_tuple(360.0_deg, Quadrant::IV)));

class IsInQuadrantIMultipleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, bool>> {
protected:
};

TEST_P(IsInQuadrantIMultipleParametersTests, isInQuadrantI)
{
    auto angle = std::get<0>(GetParam());
    auto result = std::get<1>(GetParam());
    EXPECT_EQ(isInQuadrantI(angle), result);
}

INSTANTIATE_TEST_SUITE_P(
    IsInQuadranI, IsInQuadrantIMultipleParametersTests,
    ::testing::Values(
        std::make_tuple(0.0_deg, true), std::make_tuple(45.0_deg, true),
        std::make_tuple(90.0_deg, true), std::make_tuple(90.1_deg, false),
        std::make_tuple(135.0_deg, false), std::make_tuple(180.0_deg, false),
        std::make_tuple(180.1_deg, false), std::make_tuple(225.0_deg, false),
        std::make_tuple(270.0_deg, false), std::make_tuple(270.1_deg, false),
        std::make_tuple(315.0_deg, false), std::make_tuple(360.0_deg, false)));

class IsInQuadrantIIMultipleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, bool>> {
protected:
};

TEST_P(IsInQuadrantIIMultipleParametersTests, isInQuadrantII)
{
    auto angle = std::get<0>(GetParam());
    auto result = std::get<1>(GetParam());
    EXPECT_EQ(isInQuadrantII(angle), result);
}

INSTANTIATE_TEST_SUITE_P(
    IsInQuadranII, IsInQuadrantIIMultipleParametersTests,
    ::testing::Values(
        std::make_tuple(0.0_deg, false), std::make_tuple(45.0_deg, false),
        std::make_tuple(90.0_deg, false), std::make_tuple(90.1_deg, true),
        std::make_tuple(135.0_deg, true), std::make_tuple(180.0_deg, true),
        std::make_tuple(180.1_deg, false), std::make_tuple(225.0_deg, false),
        std::make_tuple(270.0_deg, false), std::make_tuple(270.1_deg, false),
        std::make_tuple(315.0_deg, false), std::make_tuple(360.0_deg, false)));

class IsInQuadrantIIIMultipleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, bool>> {
protected:
};

TEST_P(IsInQuadrantIIIMultipleParametersTests, isInQuadrantIII)
{
    auto angle = std::get<0>(GetParam());
    auto result = std::get<1>(GetParam());
    EXPECT_EQ(isInQuadrantIII(angle), result);
}

INSTANTIATE_TEST_SUITE_P(
    IsInQuadranIII, IsInQuadrantIIIMultipleParametersTests,
    ::testing::Values(
        std::make_tuple(0.0_deg, false), std::make_tuple(45.0_deg, false),
        std::make_tuple(90.0_deg, false), std::make_tuple(90.1_deg, false),
        std::make_tuple(135.0_deg, false), std::make_tuple(180.0_deg, false),
        std::make_tuple(180.1_deg, true), std::make_tuple(225.0_deg, true),
        std::make_tuple(270.0_deg, true), std::make_tuple(270.1_deg, false),
        std::make_tuple(315.0_deg, false), std::make_tuple(360.0_deg, false)));

class IsInQuadrantIVMultipleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, bool>> {
protected:
};

TEST_P(IsInQuadrantIVMultipleParametersTests, isInQuadrantIV)
{
    auto angle = std::get<0>(GetParam());
    auto result = std::get<1>(GetParam());
    EXPECT_EQ(isInQuadrantIV(angle), result);
}

INSTANTIATE_TEST_SUITE_P(
    IsInQuadranIV, IsInQuadrantIVMultipleParametersTests,
    ::testing::Values(
        std::make_tuple(0.0_deg, false), std::make_tuple(45.0_deg, false),
        std::make_tuple(90.0_deg, false), std::make_tuple(90.1_deg, false),
        std::make_tuple(135.0_deg, false), std::make_tuple(180.0_deg, false),
        std::make_tuple(180.1_deg, false), std::make_tuple(225.0_deg, false),
        std::make_tuple(270.0_deg, false), std::make_tuple(270.1_deg, true),
        std::make_tuple(315.0_deg, true), std::make_tuple(360.0_deg, true)));

TEST(calcAngleIfOutOfRange, Expected_result)
{
    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(0.0_deg), 0.0_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(360.0_deg), 360.0_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(360.1_deg), 0.1_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(540.0_deg), 180.0_deg);

    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(-0.1_deg), 359.9_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(-360.0_deg), 0.0_deg);
    EXPECT_DOUBLE_EQ(calcAngleIfOutOfRange(-540.0_deg), 180.0_deg);
}

class CalcAngleIfOutOfRangeMultipleParametersTests
    : public ::testing::TestWithParam<std::tuple<double, double>> {
protected:
};

TEST_P(CalcAngleIfOutOfRangeMultipleParametersTests, CalcAngleIfOutOfRange)
{
    auto angle = std::get<0>(GetParam());
    auto result_angle = std::get<1>(GetParam());
    EXPECT_NEAR(calcAngleIfOutOfRange(angle), result_angle, 0.000000001);
}

INSTANTIATE_TEST_SUITE_P(
    CalcAngleIfOutOfRange, CalcAngleIfOutOfRangeMultipleParametersTests,
    ::testing::Values(std::make_tuple(0.0_deg, 0.0_deg),
                      std::make_tuple(360.0_deg, 360.0_deg),
                      std::make_tuple(360.1_deg, 0.1_deg),
                      std::make_tuple(540.0_deg, 180.0_deg),

                      std::make_tuple(-0.1_deg, 359.9_deg),
                      std::make_tuple(-360.0_deg, 0.0_deg),
                      std::make_tuple(-540.0_deg, 180.0_deg)));