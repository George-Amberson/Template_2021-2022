
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string s = "DCCXCIX";
	Latina r(s);
	Arabia a;
	Converter c;
	a = c.to_Arabia(r);
	Latina e = c.to_Latina(a);
	cout << c.Check_Latina(a, e);
	return 0;
}
	


