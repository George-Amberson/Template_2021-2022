#pragma once
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include<utility>
using namespace std;

template<class A1>
class Node
{
public:
	Node() :next(nullptr) {}
	A1 value;
	Node* next;
};
template<class A2>
class Cycle_List
{
public:
	Cycle_List(int _size=10)
	{
		head = new Node<A2>;
		Node<A2>* tmp = head;
		Node<A2>* back;
		for (int i = 1; i < _size; i++)
		{
			tmp->next = new Node<A2>;
			tmp = tmp->next;
		}
		back = tmp;
		tmp = head;
		srand(time(NULL));
		for (int i = 0; i < (rand()%(_size+1)); i++)
		{
			tmp = tmp->next;
		}
		Node<A2>* tmp2 = head;
		size=_size;
		for (int i = 0; i < size; i++)
		{
			tmp2->value = i;
			tmp2 = tmp2->next;
		}

		back->next = tmp;
	}
	Cycle_List(const Cycle_List& _in)
	{
		head = new Node<A2>;
		Node<A2>* tmp = head;
		size = _in.size;
		for (int i = 1; i < _in.size; i++)
		{
			tmp->next = new Node<A2>;
			tmp = tmp->next;
		}
		tmp = head;
		Node<A2>* tmp2 = _in.head;
		for (int i = 0; i < size; i++)
		{
			tmp->value = tmp2->value;
			tmp2 = tmp2->next;
			tmp = tmp->next;
		}
		if (tmp2->next != nullptr)
		{
			tmp2 = tmp2->next;

			Node<A2>* tmp3 = head;
			while (tmp3->value != tmp2->value)
			{
				tmp3 = tmp3->next;
			}
			tmp->next = tmp3;
		}
	}
	~Cycle_List()
	{
		Node<A2>* tmp = head;
		for (int i = 0; i < size; i++)
		{
			tmp = tmp->next;
			delete head;
			head = tmp;
		}
	}
	bool Check_with_reverse(int j=0)
	{
		
		Node<A2>* prev = nullptr;
		Node<A2>* _next = head->next;
		Node<A2>* rhs = head;
		
		while(_next!=nullptr){
			
				rhs->next = prev;
				prev = rhs;
				rhs = _next;
				_next=_next->next;
				
		}
		head->next = prev;
		if (j == 1) return 1;
		Check_with_reverse(1);
		if (rhs == head) 
			return 1;
		else return 0;
	}
	bool RabbitAndTurtle()
	{
		Node<A2>* rabbit = head;
		Node<A2>* turtle = head;
		int i = 0;
		while (rabbit->next != nullptr)
		{
			if (i % 2 == 0)
				rabbit = rabbit->next->next;
			else turtle = turtle->next;

			if (rabbit == turtle) return 1;
			i++;
		}
		return 0;
	}
	pair<Node<A2>*,int> find_cycle_start()
	{
		Node<A2>* rabbit = head;
		Node<A2>* turtle = head;
		if (RabbitAndTurtle())
		{
			int i = 0;
			while (rabbit->next != nullptr)
			{
				if (i % 2 == 0)
					rabbit = rabbit->next->next;
				else turtle = turtle->next;

				if (rabbit == turtle)
				{
					rabbit = head;
					do {
						rabbit = rabbit->next;
						turtle = turtle->next;
					} while (rabbit != turtle);

					int size = 0;

					while (turtle->next != rabbit)
					{
						turtle = turtle->next;
						size++;
					}
					return make_pair(turtle,(size+1));
				}
				i++;
			}
		}
		else
		{
			return make_pair(nullptr,0);
		}
	}
private:
	Node<A2>* head;
	int size;
};