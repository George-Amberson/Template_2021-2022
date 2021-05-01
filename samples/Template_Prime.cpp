
#include <iomanip>
#include "Template.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	AVL_table<int, int>A2(Node<int, int>(-1, 2));
	for (int i = 0; i < 10; i++)A2.add(i, i + 1);
	bool f = A2.find(4);
	A2.erase(4);
	cout<<(f==A2.find(4));
}
	


