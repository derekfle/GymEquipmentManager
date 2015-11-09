#include "gtest/gtest.h"

TEST(TestTest, TestyTestTest)
{
	EXPECT_EQ(1, 1);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
}