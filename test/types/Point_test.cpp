#include "gtest/gtest.h"

#include "../../src/types/Point.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(PointTest, operatorIsWorks1)
{
    std::string test{"X 3.5 Y 5.2"};

    std::istringstream ist{test};

    Point p;
    ist >> p;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(p.x, 3.5);
    EXPECT_EQ(p.y, 5.2);
}

TEST(PointTest, operatorIsWorks2)
{
    std::string test{"X 3 Y 5"};

    std::istringstream ist{test};

    Point p;
    ist >> p;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(p.x, 3.0);
    EXPECT_EQ(p.y, 5.0);
}

TEST(PointTest, operatorIsFails1)
{
    std::string test{" 3.5 Y 5.2"};

    std::istringstream ist{test};

    Point p;
    ist >> p;

    EXPECT_TRUE(ist.fail());
}

TEST(PointTest, operatorIsFails2)
{
    std::string test{"X 3.5  5.2"};

    std::istringstream ist{test};

    Point p;
    ist >> p;

    EXPECT_TRUE(ist.fail());
}

TEST(PointTest, operatorIsFails3)
{
    std::string test{"Y 3.5 X 5.2"};

    std::istringstream ist{test};

    Point p;
    ist >> p;

    EXPECT_TRUE(ist.fail());
}