#include "gtest/gtest.h"

#include "../src/OperatorDegree.h"

using namespace bricks;

TEST(OperatorDegree, ValuesAreEqual_0) { EXPECT_DOUBLE_EQ(0.0_deg, 0.0); }

TEST(OperatorDegree, ValuesAreEqual_90) {
    EXPECT_DOUBLE_EQ(90.0_deg, 1.5707963267948966);
}

TEST(OperatorDegree, ValuesAreEqual_180) {
    EXPECT_DOUBLE_EQ(180.0_deg, 3.1415926535897931);
}

TEST(OperatorDegree, ValuesAreEqual_270) {
    EXPECT_DOUBLE_EQ(270.0_deg, 4.7123889803846897);
}

TEST(OperatorDegree, ValuesAreEqual_360) {
    EXPECT_DOUBLE_EQ(360.0_deg, 6.2831853071795862);
}