
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	char s[] = "My poshli na plaz. Love u.";
	char d[] = "Sanitary fuck u.";
	{
		Text s2(d);
		cout << s2 << "\n";
	}
	Text ss(&s[0]);
	cout << ss<< endl;
	
}  


