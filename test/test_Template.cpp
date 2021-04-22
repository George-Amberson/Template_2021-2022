#include "Template.h"
#include <map>
#include <gtest.h>

using namespace std;
TEST(ut, ccut)
{
	map<int, int> q;
	q[0] = 1;
	EXPECT_EQ(q[0],1);
}







