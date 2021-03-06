#pragma once
#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;
class Monom
{
	double K; //коэфициент перед мономом
	int Pow; // число в разрядах которого соджеражтся степени неизвестных, (принимается условие что каждая степень не превосходит 4), при этом самый правый разряд числа игнорируется
	int dim; //число неизвестных в мономе
public:
	Monom(int _pow = 0, double _k = 0, int _dim = 0) :dim(_dim), K(_k),Pow(_pow){}
	Monom(const Monom& _in):K(_in.K),dim(_in.dim),Pow(_in.Pow){}
	Monom& operator =(const Monom& _in)
	{
		K = _in.get_K();
		Pow = _in.get_pow();
		dim = _in.get_dim();
		return(*this);
	}
	friend bool operator ==(const Monom& lhs,const Monom& rhs)
	{
		if ((lhs.K != rhs.K) || (lhs.dim != rhs.dim)||(lhs.Pow!=rhs.Pow)) return 0;
		return 1;
		
	}
	friend bool operator !=(const Monom& lhs, const Monom& rhs)
	{
		return !(lhs == rhs);
	}
	friend bool operator <(const Monom& lhs, const Monom& rhs)
	{
		return((lhs.Pow / 10) < (rhs.Pow / 10));
	}
	int get_pow()const
	{
		return Pow;
	}
	int get_pow_i(const int index)const // метод возвращающий конкретный разряд числа
	{
		return (Pow / pow(10, index));
	}
	int get_dim()const
	{
		return dim;
	}
	double get_K()const
	{
		return K;
	}
	friend Monom operator*(const Monom& lhs, const Monom& rhs)
	{
		return Monom(lhs.get_pow() + rhs.get_pow(), lhs.K*rhs.K, max(lhs.get_dim(), rhs.get_dim()));
	}
	friend ostream& operator <<(ostream& out, const Monom& _ot)
	{
		if (_ot.K > 0) out << '+' << _ot.K;
		else
		out << _ot.K;
		for (int i = 1; i <= _ot.get_dim(); i++) out << 'x' << i << '^' << _ot.get_pow_i(i);
		return out;
		
	}
};

class Polynom : public set<Monom> // класс полином наследник класса множество с параметром моном. Это сделано чтобы обеспечить поиск монома с эквивалентным набором степеней за log(n)
{
public:
	Polynom(Monom* ptr=0,int size=0) :set<Monom>() 
	{
		for (int i = 0; i < size; i++) this->insert(ptr[i]);
	}
	Polynom(const Polynom& _in) :set<Monom>(_in) {}
	
	friend Polynom operator +(const Polynom& lhs, const Polynom& rhs)
	{
		Polynom res(rhs);
		for (auto i=lhs.begin();i!=lhs.end();i++)
		{
			auto j=res.find(*i);
			if (j != res.end())
			{ 
				double _k = j->get_K() + i->get_K();
				res.erase(j);
				res.insert(Monom(i->get_pow(),_k,i->get_dim()));
			}
			else
				res.insert(*i);
			
		}
		return res;
	}
	friend Polynom operator -(const Polynom& lhs, const Polynom& rhs)
	{
		Polynom res(lhs);
		for (auto i = rhs.begin(); i != rhs.end(); i++)
		{
			auto j = res.find(*i);
			if (j != res.end())
			{
				double _k = j->get_K() - i->get_K();
				res.erase(j);
				res.insert(Monom(i->get_pow(), _k, i->get_dim()));
			}
			else {
				res.insert(Monom(i->get_pow(),i->get_K()*-1,i->get_dim()));
			}

		}
		return res;
	}
	Polynom& operator +=(const Monom& rhs)
	{
		auto j = this->find(rhs);
		if ( j!= this->end())
		{
			double _k = j->get_K() + rhs.get_K();
			this->erase(j);
			if (_k != 0) {
				this->insert(Monom(rhs.get_pow(), _k, rhs.get_dim()));
			}
			return (*this);
		}
		this->insert(rhs);
		return (*this);
	}
	friend Polynom operator*(const Polynom& lhs, const Polynom& rhs)
	{
		Polynom res;
		for (auto i= lhs.begin();i!=lhs.end();i++)
		{
			for (auto j = rhs.begin(); j != rhs.end(); j++)
			{
				res += ((*i)*(*j));
			}
		}
		return res;
	}
	friend bool operator ==(const Polynom& lhs, const Polynom& rhs)
	{
		if (lhs.size() != rhs.size()) return 0;
		else
		{
			auto i = lhs.begin();
			auto j = rhs.begin();
			for (int t = 0; t < lhs.size(); t++)
			{
				if ((*i)!=(*j)) return 0;
				i++;
				j++;
			}
			return 1;
		}

	}
	friend ostream& operator <<(ostream& _out, const Polynom& o_ct)
	{
		for (auto i = o_ct.begin(); i != o_ct.end(); i++) _out << (*i);
		return _out;
	}
};