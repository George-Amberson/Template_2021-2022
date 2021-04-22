
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	sorted_table<int,double> b(4);
	b.add(1, 2);
	b.add(3, 4);
	b.find(3);
	return 0;
}
	


