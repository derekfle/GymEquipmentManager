#include "gtest/gtest.h"

#include "Equipment.h"

TEST(TestTest, TestyTestTest)
{
	Equipment equip;
	EXPECT_EQ(equip.id, 999);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE"); // Nasty...
}