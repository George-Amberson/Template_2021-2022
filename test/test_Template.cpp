
#include <gtest.h>

#include "Template.h"
using namespace std;
TEST(UNSORTED_TABLE,ADD_TO_TABLE)
{
	unsorted_table<int, int>A1(2);
	A1.add(1, 2);
	A1.add(3, 4);
	EXPECT_EQ(A1[1], 2);
}
TEST(UNSORTED_TABLE, CHECK_TABLE_WITH_FIND)
{
	unsorted_table<int, int>A2(1);
	A2.add(1, 2);
	EXPECT_EQ(A2.find(1), 1);
}
TEST(UNSORTED_TABLE, CHECK_TABLE_WITH_NO_FIND)
{
	unsorted_table<int, int>A2(1);
	A2.add(2, 2);
	EXPECT_EQ(A2.find(1), 0);
}
TEST(UNSORTED_TABLE, NO_ACCESS_WITH_KEY)
{
	unsorted_table<int, int>A2(1);
	A2.add(2, 2);
	ASSERT_ANY_THROW(A2[1]);
}

TEST(UNSORTED_TABLE,ERASE_AND_FIND )
{

	unsorted_table<int, int>A2(1);
	A2.add(2, 2);
	bool f = A2.find(2);
	A2.erase(2);
	EXPECT_EQ(!f, A2.find(2));
}
TEST(UNSORTED_TABLE, MORE_NODES_ERASE_AND_FIND)
{

	unsorted_table<int, int>A2(1);
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	A2.erase(4);
	EXPECT_EQ(!f, A2.find(4));
}
TEST(UNSORTED_TABLE, MORE_NODES_CHECK_TABLE_WITH_FIND)
{

	unsorted_table<int, int>A2(1);
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	EXPECT_EQ(f, 1);
}
TEST(UNSORTED_TABLE, MORE_NODES_CHECK_TABLE_WITH_NO_FIND)
{

	unsorted_table<int, int>A2(1);
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(48);
	EXPECT_EQ(f, 0);
}
//-----------------------------------
TEST(SORTED_TABLE, ADD_TO_TABLE)
{
	sorted_table<int, int>A1(2);
	A1.add(1, 2);
	A1.add(3, 4);
	EXPECT_EQ(A1[1], 2);
}
TEST(SORTED_TABLE, CHECK_TABLE_WITH_FIND)
{
	sorted_table<int, int>A2(1);
	A2.add(1, 2);
	EXPECT_EQ(A2.find(1), 1);
}
TEST(SORTED_TABLE, CHECK_TABLE_WITH_FIND_AND_NO_FIND)
{
	sorted_table<int, int>A2(1);
	A2.add(2, 2);
	EXPECT_EQ(A2.find(1), 0);
}
TEST(SORTED_TABLE, NO_ACCESS_WITH_KEY)
{
	sorted_table<int, int>A2(1);
	A2.add(2, 2);
	ASSERT_ANY_THROW(A2[1]);
}

TEST(SORTED_TABLE, ERASE_AND_FIND)
{

	sorted_table<int, int>A2(1);
	A2.add(2, 2);
	bool f = A2.find(2);
	A2.erase(2);
	EXPECT_EQ(!f, A2.find(2));
}
TEST(SORTED_TABLE, MORE_NODES_ERASE_AND_FIND)
{

	sorted_table<int, int>A2(1);
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	A2.erase(4);
	EXPECT_EQ(!f, A2.find(4));
}
TEST(SORTED_TABLE, MORE_NODES_CHECK_TABLE_WITH_FIND)
{

	sorted_table<int, int>A2(1);
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	EXPECT_EQ(f, 1);
}
TEST(SORTED_TABLE, MORE_NODES_CHECK_TABLE_WITH_NO_FIND)
{

	sorted_table<int, int>A2(1);
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(48);
	EXPECT_EQ(f, 0);
}
//--------------------------------------
TEST(AVL_TABLE, ADD_TO_TABLE)
{
	AVL_table<int, int>A1(Node<int,int>(1,2));
	
	A1.add(3, 4);
	EXPECT_EQ(A1[1], 2);
}
TEST(AVL_TABLE, CHECK_TABLE_WITH_FIND)
{
	AVL_table<int, int>A2(Node<int, int>(1, 2));
	EXPECT_EQ(A2.find(1), 1);
}
TEST(AVL_TABLE, CHECK_TABLE_WITH_FIND_AND_NO_FIND)
{
	AVL_table<int, int>A2(Node<int, int>(3, 2));
	A2.add(2, 2);
	EXPECT_EQ(A2.find(1), 0);
}
TEST(AVL_TABLE, NO_ACCESS_WITH_KEY)
{
	AVL_table<int, int>A2(Node<int, int>(3, 2));
	A2.add(2, 2);
	ASSERT_ANY_THROW(A2[1]);
}

TEST(AVL_TABLE, ERASE_AND_FIND)
{

	AVL_table<int, int>A2(Node<int, int>(1, 2));
	A2.add(2, 2);
	bool f = A2.find(2);
	A2.erase(2);
	EXPECT_EQ(!f, A2.find(2));
}
TEST(AVL_TABLE, MORE_NODES_ERASE_AND_FIND)
{

	AVL_table<int, int>A2(Node<int,int>(-1,2));
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	A2.erase(4);
	EXPECT_EQ(!f, A2.find(4));
}
TEST(AVL_TABLE, MORE_NODES_CHECK_TABLE_WITH_FIND)
{

	AVL_table<int, int>A2(Node<int, int>(-1, 2));
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	EXPECT_EQ(f, 1);
}
TEST(AVL_TABLE, MORE_NODES_CHECK_TABLE_WITH_NO_FIND)
{

	AVL_table<int, int>A2(Node<int, int>(-1, 2));
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(48);
	EXPECT_EQ(f, 0);
}