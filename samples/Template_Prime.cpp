
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

int main()
{
	AVL_table<string, int>A2;
	ifstream f("C:\\Users\\George\\Desktop\\sometext.txt");
	string w;
	while (f)
	{
		f >> w;
		if (w.back() == '.') w.erase(w.begin()+w.size()-1);
		if ((w.front() >= 'A') && (w.front() <= 'Z')) w[0] = tolower(w[0]);
		A2.add(w, 1);
	}
	cout << A2;
	return 0;
}
	


