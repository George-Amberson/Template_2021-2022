#pragma once
#include <iostream>
#include <cmath>
#include<string>
#include <map>
using namespace std;
 
const map<char, int> Table = { {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000} };
const map<int, string>Table3 = { {1,"I"},{5,"V"},{10,"X"},{50,"L"},{100,"C"},{500,"D"},{1000,"M"},{900,"CM"},{90,"XC"},{40,"XL"},{9,"IX"},{4,"IV"} };
void MakeNStr(int n, const string& ch,string& res)
{
	for (int i = 0; i < n; i++)res += ch;
	
}
class Arabia
{
public:
	Arabia(int in=0) :data(in) {}
	Arabia(const Arabia& in)
	{
		data = in.data;
	}
	Arabia& operator =(const Arabia& in)
	{
		data = in.data;
		return(*this);
	}
	int get_data()const
	{
		return data;
	}
	
	private:
	int data;
};

class Latina
{
public:
	Latina(const string& in):data(in){}
	Latina(const Latina& in)
	{
		data = in.data;
	}
	string get_data()const 
	{
		return data;
	}
	friend bool operator ==(const Latina& lhs, const Latina& rhs)
	{
		return (lhs.data == rhs.data);
	}
private:
	string data;
};

class Converter
{
public:
	Converter() {}
	Arabia to_Arabia(const Latina& _latina)
	{
		string copy = _latina.get_data();
		int sum = 0;
		int crrnt = Table.at(copy[0]);
		for (int j = 1; j < copy.size(); j++)
		{
			if ((crrnt < Table.at(copy[j])))crrnt *= -1;
			sum += crrnt;
			crrnt = Table.at(copy[j]);
		}
		sum += crrnt;
		
		return Arabia(sum);
	}
	Latina to_Latina(const Arabia& _arabia)
	{
		int copy = _arabia.get_data();
		string res;
		for (auto i = Table3.rbegin(); ((i != Table3.rend())&&(copy>0)); i++)
		{
			int s = copy / (*i).first;
			if (s > 0)
			{
				MakeNStr(s, (*i).second, res);
				copy -= s * (*i).first;
			}
		}
		return Latina(res);
	}
	bool Check_Latina(const Arabia& _arabia, const Latina& _latina)
	{
		return((this->to_Latina(_arabia)) == _latina);
	}
};