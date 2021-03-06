#include "Template.h"

#include <gtest.h>

TEST(POLYNOM, can_create_Polynom)
{
	Monom* ptr = new Monom[4];
	ptr[0] = Monom(30, 1, 1);
	ptr[1] = Monom(20, 1, 1);
	ptr[2] = Monom(1, -1, 1);
	
	ASSERT_NO_THROW(Polynom b(ptr, 3));
}



TEST(POLYNOM, Can_copy_Polynom)
{
	Monom* ptr = new Monom[4];
	ptr[0] = Monom(30, 1, 1);
	ptr[1] = Monom(20, 1, 1);
	ptr[2] = Monom(1, -1, 1);
	Polynom b(ptr, 3);
	ASSERT_NO_THROW(Polynom c(b));
}
TEST(POLYNOM, correct_sum)
{
	Monom* ptr1 = new Monom[3];
	ptr1[0] = Monom(20, 1, 1);
	ptr1[1] = Monom(10, 1, 1);
	ptr1[2] = Monom(0, 1, 0);
	Polynom A(ptr1, 1);
	Polynom B(ptr1 + 1, 2);
	Polynom C(ptr1, 3);
	ASSERT_EQ((A + B), C);

	
}

TEST(POLYNOM, correct_sum1)
{
	Monom* ptr1 = new Monom[3];
	ptr1[0] = Monom(20, 2, 1);
	ptr1[1] = Monom(10, 1, 1);
	ptr1[2] = Monom(20, 1, 1);
	Polynom C(ptr1, 2);
	Polynom B(ptr1 + 1, 2);
	Polynom A(ptr1+2, 1);
	ASSERT_EQ((A + B), C);
}

TEST(POLYNOM, correct_raz)
{

	Monom* ptr1 = new Monom[3];
	ptr1[0] = Monom(20, 1, 1);
	ptr1[1] = Monom(10, -1, 1);
	ptr1[2] = Monom(10, 1, 1);
	Polynom A(ptr1, 1);
	Polynom B(ptr1 + 2, 1);
	Polynom C(ptr1, 2);
	ASSERT_EQ((A - B), C);
}
TEST(POLYNOM, correct_raz1)
{
	Monom* ptr1 = new Monom[3];
	ptr1[0] = Monom(20, 1, 1);
	ptr1[1] = Monom(10, 2, 1);
	ptr1[2] = Monom(10, 1, 1);
	Monom* ptr2 = new Monom[3];
	ptr2[0] = Monom(20, 1, 1);
	ptr2[1] = Monom(10, 1, 1);
	Polynom A(ptr1, 2);
	Polynom B(ptr1 + 2, 1);
	Polynom C(ptr2, 2);
	ASSERT_EQ((A - B), C);
}
TEST(POLYNOM, correct_umn)
{
	Monom* ptr1 = new Monom[3];
	ptr1[1] = Monom(10, 1, 1);
	ptr1[0] = Monom(0, 1, 0);
	ptr1[2]= Monom(0, -1, 0);
	Monom* ptr2 = new Monom[3];
	ptr2[0] = Monom(20, 1, 1);
	ptr2[1] = Monom(0, -1, 0);
	Polynom A(ptr1, 2);
	Polynom B(ptr1 + 1, 2);
	Polynom C(ptr2, 2);
	ASSERT_EQ((A*B), C);
}
TEST(POLYNOM, correct_umn1)
{
	Monom* ptr1 = new Monom[3];
	ptr1[1] = Monom(20, 1, 1);
	ptr1[0] = Monom(10, 2, 1);
	ptr1[2] = Monom(0, 1, 0);
	Monom* ptr2 = new Monom(10, 1, 1);
	Monom* ptr3 = new Monom[3];
	ptr3[0] = Monom(30, 1, 1);
	ptr3[1] = Monom(20, 2, 1);
	ptr3[2] = Monom(10, 1, 1);
	Polynom A(ptr1, 3);
	Polynom B(ptr2, 1);
	Polynom C(ptr3, 3);
	ASSERT_EQ((A*B), C);
}








