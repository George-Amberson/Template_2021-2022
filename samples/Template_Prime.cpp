
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string s1="ABCDEF.";
	string s22="Sanitary fuck u.";
	{
		Text s2(s22);
		cout << s2 << "\n";
	}
 Text ss(s1);
	cout << ss<< endl;
	
	//Text sss;
	//sss += move(ss);
	//cin >> sss;
	//cout << sss;
	ifstream u("D:\\List-Lab1\\1.txt");
	
	Text q;
	
	u>>q;

	cout << q;
}  


