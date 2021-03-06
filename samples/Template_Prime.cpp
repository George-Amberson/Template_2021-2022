
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	Monom* ptr1 = new Monom[3];
	ptr1[0] = Monom(20, 1, 1);
	ptr1[1] = Monom(10, 2, 1);
	ptr1[2] = Monom(10, -1, 1);
	Monom* ptr2 = new Monom[3];
	ptr2[0] = Monom(20, 1, 1);
	ptr2[1] = Monom(10, 1, 1);
	Polynom A(ptr1, 2);
	Polynom B(ptr1 + 2, 1);
	Polynom C(ptr2, 2);
	cout << (A - B);
	return 0;
}
	


