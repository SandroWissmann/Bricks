#include "gtest/gtest.h"

#include "../src/NearlyEqual.h"

using namespace bricks;

TEST(NearlyEqual, ValuesAreEqual_1) {
    EXPECT_TRUE(bricks::nearlyEqual<double>(1.0, 1.0));
}
