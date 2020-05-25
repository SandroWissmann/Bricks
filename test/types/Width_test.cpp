#include "gtest/gtest.h"

#include "../../include/types/Width.h"

#include <iostream>
#include <sstream>

using namespace bricks::types;

TEST(WidthTest, defaultConstructor)
{
    Width w;
    EXPECT_EQ(w(), 0.0);
}

TEST(WidthTest, Constructor)
{
    Width w{3.5};
    EXPECT_EQ(w(), 3.5);
}

TEST(WidthTest, operatorIsWorks1)
{
    std::string test{"W 3.5"};

    std::istringstream ist{test};

    Width w;
    ist >> w;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(w(), 3.5);
}

TEST(WidthTest, operatorIsWorks2)
{
    std::string test{"W 3"};

    std::istringstream ist{test};

    Width w;
    ist >> w;

    EXPECT_FALSE(ist.fail());

    EXPECT_EQ(w(), 3.0);
}

TEST(WidthTest, operatorIsFails1)
{
    std::string test{" 3.5"};

    std::istringstream ist{test};

    Width w;
    ist >> w;

    EXPECT_TRUE(ist.fail());
}

TEST(WidthTest, operatorIsFails2)
{
    std::string test{"H 3.5"};

    std::istringstream ist{test};

    Width w;
    ist >> w;

    EXPECT_TRUE(ist.fail());
}