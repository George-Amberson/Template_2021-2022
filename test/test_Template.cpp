#include "Template.h"

#include <gtest.h>

TEST(ARABIA, can_create)
{
	Arabia a(2019);
	EXPECT_EQ(a.get_data(), 2019);
}



TEST(ARABIA, Can_copy)
{
	Arabia a(2019);
	Arabia b(a);
	EXPECT_EQ(a.get_data(), b.get_data());
}
TEST(LATINA, Can_create)
{
	Latina a("IX");
	EXPECT_EQ(a.get_data(), "IX");
}

TEST(LATINA, Can_copy)
{
	Latina a("IX");
	Latina b(a);
	EXPECT_EQ(a.get_data(), b.get_data());
}

TEST(LATINA_PLUS_ARABIA, can_convert1)
{
	Latina a("MDCCXCII");

	Converter c;
	Arabia b =c.to_Arabia(a);
	EXPECT_EQ(b.get_data(), 1792);
}
TEST(LATINA_PLUS_ARABIA, can_convert2)
{
	Converter c;
	Arabia a(2907),d;
	Latina b = c.to_Latina(a);
	d = c.to_Arabia(b);
	EXPECT_EQ(d.get_data(), a.get_data());
}








