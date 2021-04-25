
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string s1="My poshli na plaz. Love u.";
	string s22="Sanitary fuck u.";
	{
		Text s2(s22);
		cout << s2 << "\n";
	}
 Text ss(s22);
	cout << ss<< endl;
	//Text sss;
	//sss += move(ss);
	//cin >> sss;
	//cout << sss;
	ifstream s("C:\\Users\\George\\Desktop\\s.txt");

	Text q;
	
	s>>q;

	cout << q;
}  


