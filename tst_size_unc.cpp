#include <gtest/gtest.h>
#include "size_unc.h"

using namespace testing;

TEST(size_unc, size_unc)
{
    size_unc x = 1;
    EXPECT_EQ(x, int(1));
    EXPECT_EQ(x.GetValue(), int(1));
}


TEST(size_unc, size_unc2)
{
    size_unc x =1;
    size_unc y = 3;

    EXPECT_EQ(x+y, 1);
}
