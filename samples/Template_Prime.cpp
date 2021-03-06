
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	Cycle_List<int>A(8);
	cout << A.Check_with_reverse();
	cout << A.RabbitAndTurtle();
	cout << A.find_cycle_start().second;
}
	


