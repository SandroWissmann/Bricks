#include "gtest/gtest.h"

#include "../../include/utility/NearlyEqual.h"

#include <limits>

using namespace bricks::utility;

TEST(NearlyEqual, ValuesAreEqual_1)
{
    EXPECT_TRUE(nearlyEqual<double>(1.0, 1.0));
}
