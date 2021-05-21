#pragma once
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

size_t strf(const string& s, size_t sp);


class TTextNode
{
protected:
	static TTextNode* firstfree;
	static  vector<TTextNode*> textNodes;
	TTextNode* next;
	TTextNode* down;
	char c;
	int level; //0-text,1-string,2-word,3-letter -1 not-use


public:
	TTextNode(int l = 3, char _c = 0) :next(nullptr), down(nullptr), c(_c), level(l) {}
	TTextNode(const TTextNode& rhs) :next(nullptr), down(nullptr)
	{
		c = rhs.c;
		level = rhs.level;
	}
	TTextNode(const string& s, int l = 0) :next(nullptr), level(l), down(nullptr)
	{
		if (l == 0)
		{
			TTextNode::inizial();
			down = new TTextNode(s, l + 1);
			TTextNode::inizial();
		}
		if (l == 1)
		{
			down = new TTextNode(s, l + 1);
			if (TTextNode::get_sum_length() < s.size())next = new TTextNode(s, l);
		}
		if (l == 2)
		{
			down = new TTextNode(s, l + 1);
			if ((s[TTextNode::get_sum_length()-1] != '.')&&
				(s[TTextNode::get_sum_length() - 1] != '!')&&
				(s[TTextNode::get_sum_length() - 1] != '?'))next = new TTextNode(s, l);
		}
		if (l == 3)
		{
			this->c = s[TTextNode::get_sum_length()];
			this->down = nullptr;
			TTextNode* ptr = this;
			TTextNode::add(1);
			size_t j = strf(s,TTextNode::get_sum_length());
			for (size_t i= TTextNode::get_sum_length(); i != j; i++)
			{
				ptr->next = new TTextNode(3, s[i]);
				TTextNode::add(1);
				ptr = ptr->get_next();
			}

		}
	}
	
	~TTextNode(){}
	TTextNode* get_next()
	{
		return next;
	}
	TTextNode* get_down()
	{
		return down;
	}
	char get_c()
	{
		return c;
	}
	int get_level()
	{
		return level;
	}
	void set_next(TTextNode* rhs)
	{
		next = rhs;
	}
	void set_down(TTextNode* rhs)
	{
		down = rhs;
	}
	void set_c(const char& rhs)
	{
		c = rhs;
	}
	void set_level(const int& rhs)
	{
		if ((rhs <= 3) && (rhs >= 1))
			level = rhs;
		else throw logic_error("incorrect parametr");
	}

	friend ostream& operator<<(ostream& out, TTextNode& _out)
	{
		if (_out.level == 3)
		{
			out << _out.c;
			if (_out.next != nullptr)
			{
				out << (*(_out.next));
			}
		}
		else
		{
			if (_out.down != nullptr)
			{
				out << (*(_out.down));
			}
			if (_out.next != nullptr)
			{
				out << (*(_out.next));
			}
		}
		return out;
	}
	

	static void InitMem()
	{
		
		if ((firstfree == nullptr) && (textNodes.empty()))
		{
			textNodes.push_back(new TTextNode[100000]);
			for (int i = 1; i < 100000; i++) textNodes.back()[i - 1].next = &(textNodes.back()[i]);
			firstfree = &(textNodes.back()[0]);
		}
		else if ((firstfree != nullptr) && (textNodes.empty())) throw logic_error("memory missing");
		else
		{
			if (firstfree == nullptr) {
				
				if (TTextNode::get_trash_count() > 0) TTextNode::Trash_Taker();
				else {
					textNodes.push_back(new TTextNode[100000]);
					for (int i = 0; i < 100000; i++) { textNodes.back()[i - 1].next = &(textNodes.back()[i]); textNodes.back()[i].level = -1; }
					firstfree = &(textNodes.back()[0]);
				}
				
			}
		}
	}
	static void FreeMem()
	{
		textNodes.clear();
		firstfree = nullptr;
	}
	void* operator new(size_t)
	{
		if ((firstfree == nullptr))
		{
			InitMem();
		}
		TTextNode* ptr = firstfree;
		firstfree = firstfree->get_next();
		ptr->next = nullptr;
		ptr->down = nullptr;
		return ptr;
	}
	void operator delete(void* ptr)
	{
		TTextNode* _ptr = (TTextNode*)ptr;
		_ptr->down = nullptr;
		_ptr->c = 0;
		_ptr->level = -1;
		_ptr->next = firstfree;
		firstfree = _ptr;
	


	}

	void checker(TTextNode* ptr)
	{

		ptr->level = -1;
		TTextNode::add_or_sub_trash_count(1);
		if (ptr->down != nullptr) checker(ptr->down);
		if (ptr->next != nullptr) checker(ptr->next);
	}
private:
	static int  sum_length;
	static void add(int plus);
	static void inizial();
	static int get_sum_length();

	static int trash_count;
	static int get_trash_count();
	public:
	static void add_or_sub_trash_count(const int& s);

	static void Trash_Taker()
	{
		for (auto &i : TTextNode::textNodes)
		{
			for (int j = 0; j < 100000; j++)
			{
				if (i[j].get_level() == -1)
				{
					delete &(i[j]);
					TTextNode::add_or_sub_trash_count(-1);
				}
			}
		}
	}
};

int TTextNode::trash_count = 0;
int TTextNode::sum_length = 0;
vector<TTextNode*> TTextNode::textNodes = {};
TTextNode* TTextNode::firstfree = nullptr;

void TTextNode::add(int plus)
{
	sum_length += plus;
}
void TTextNode::inizial()
{
	sum_length = 0;
}
int TTextNode::get_sum_length()
{
	return sum_length;
}

 int TTextNode::get_trash_count()
{
	return trash_count;
}

void TTextNode::add_or_sub_trash_count(const int & s)
{
	 trash_count += s;
}

size_t strf(const string& s, size_t sp)
{
	for (size_t i = sp; i < s.size(); i++)
	{
		if ((s[i] == ' ') || (s[i] == '.')||(s[i]=='?')||(s[i]=='!')) return i + 1;
	}
	return sp + 1;
}


class Text
{
private:
	TTextNode text;
	
	Text& operator+=(Text& rhs);
	
public:
	Text():text(0) {}
	Text(const string& str):text(str,0){}
	Text(const Text& rhs) :text(rhs.text) {}
	~Text()
	{
		if(text.get_down()!=nullptr) text.checker(text.get_down());
	}
	bool empty_text()
	{
		return(text.get_down() == nullptr);
	}
	friend ostream& operator <<(ostream& out, Text& TEXT)
	{
		out << TEXT.text;
		return out;
	}
	friend istream& operator >>(istream& in, Text& TEXT)
	{
		std::string line;
		
		while (getline(in, line))
		{
		
			TEXT += Text(line);
		
		}
		return in;
	}
	
};


Text& Text::operator+=( Text& rhs)
{
	
	if (this->empty_text())
	{
		this->text.set_down(rhs.text.get_down());
		rhs.text.set_down(nullptr);
		
		return(*this);
	}
	
	TTextNode* ptr = this->text.get_down();
	while (ptr->get_next() != nullptr)ptr = ptr->get_next();
	ptr->set_next(rhs.text.get_down());
	
	rhs.text.set_down(nullptr);
	
	return(*this);
}