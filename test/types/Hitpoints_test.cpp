#include "gtest/gtest.h"

#include "../../include/types/Hitpoints.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(HitpointsTest, defaultConstructor)
{
    Hitpoints hp;
    EXPECT_EQ(hp(), 0);
}

TEST(HitpointsTest, Constructor)
{
    Hitpoints hp{3};
    EXPECT_EQ(hp(), 3);
}

TEST(HitpointsTest, Constructor_throws_invald_argument)
{
    EXPECT_THROW(Hitpoints{-1}, std::invalid_argument);
}

TEST(HitpointsTest, operatorIsWorks1)
{
    std::string test{"HP 3"};

    std::istringstream ist{test};

    Hitpoints hp;
    ist >> hp;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(hp(), 3);
}

TEST(HitpointsTest, operatorIsFails1)
{
    std::string test{" 3"};

    std::istringstream ist{test};

    Hitpoints hp;
    ist >> hp;

    EXPECT_TRUE(ist.fail());
}

TEST(HitpointsTest, operatorIsFails2)
{
    std::string test{"HP 3.5"};

    std::istringstream ist{test};

    Hitpoints hp;
    ist >> hp;

    EXPECT_TRUE(ist.fail());
}

TEST(HitpointsTest, operatorIsFails3)
{
    std::string test{"H 3"};

    std::istringstream ist{test};

    Hitpoints hp;
    ist >> hp;

    EXPECT_TRUE(ist.fail());
}