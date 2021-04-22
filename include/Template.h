#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <algorithm>
using namespace std;

template<class k, class v>
class Node
{
private:
	k key;
	v value;

public:
	Node() {}
	Node(const Node& l) :key(l.key), value(l.value) {}
	k get_key()
	{
		return key;
	}
	v& get_access_value()
	{
		return value;
	}
	v get_value()
	{
		return value;
	}
	void set_key(k _key)
	{
		key = _key;
	}
	void set_value(v _value)
	{
		value = _value;
	}
	Node& operator =(const Node& rhs)
	{
		key = rhs.key;
		value = rhs.value;
		return(*this);
	}
	friend bool operator ==(const Node& lhs, const Node& rhs)
	{
		return lhs.get_key() == rhs.get_key();
	}
	friend bool operator<( Node& lhs,  Node& rhs) {
		return lhs.get_key() < rhs.get_key();
	}
	friend bool operator>(const Node& lhs, const Node& rhs)
	{
		return lhs.key > rhs.get_key;
	}
};

template<class K,class V>
int binarySearch(Node<K,V>* arr, int l, int r, const K& key)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle
		// itself
		if (arr[mid].get_key() == key)
			return mid;

		// If element is smaller than mid, then
		// it can only be present in left subarray
		if (arr[mid].get_key() > key)
			return binarySearch(arr, l, mid - 1, key);

		// Else the element can only be present
		// in right subarray
		return binarySearch(arr, mid + 1, r, key);
	}

	// We reach here when element is not
	// present in array
	return -1;
}


template<class Key,class Value>
class unsorted_table
{
protected:
	Node<Key,Value>* mas;
	int count;
	int size;
public:
	unsorted_table(int _size=0): count(0),size(_size)
	{
		if (_size < 0) throw logic_error("size<0");
		mas = new Node<Key,Value>[size];
	}
	unsorted_table(const unsorted_table& rhs):count(rhs.count),size(rhs.size)
	{
		mas = new Node<Key, Value>[size];
		for (int i = 0; i < count; i++)mas[i] = rhs.mas[i];
	}
	virtual ~unsorted_table()
	{
		if (mas != nullptr)
		{
			delete[] mas;
		}
	}
	
	virtual Value& operator[](const Key& k)
	{
		for (int i = 0; i < count; i++)
		{
			if (mas[i].get_key() == k)return mas[i].get_access_value();
		}
		throw runtime_error("key doesn't exist");
	}
	 virtual bool find(const Key& k)
	{

		for (int i = 0; i < count; i++)
		{
			if (mas[i].get_key() == k)return true;
		}
		return false;
	}
	virtual void add(const Key& k, const Value& v)
	{
		if (count == size)realloc(2 * size);
		mas[count].set_key(k);
		mas[count].set_value(v);
		count++;
	}
	virtual void erase(const Key& k)
	{
		for (int i = 0; i < count; i++)
		{
			if (mas[i].get_key() == k) {
				shift(i);
				return;
			}
			
		}
		throw runtime_error("key doesn't exist and coudn't be erased");
	}
	void realloc(int ns)
	{
		Node<Key,Value>* p = new Node<Key,Value>[ns];
		for (int i = 0; i < count; i++)
		{
			p[i] = mas[i];
		}
		size = ns;
		delete[]mas;
		mas = p;
	}
	void shift(int i)
	{
		for (int j = i; j < count - 1; j++)
		{
			mas[j] = mas[j + 1];
		}
		count--;
	}
};

template<class K,class V>
class sorted_table: public unsorted_table<K,V>
{
public:
	sorted_table(int size = 0) :unsorted_table(size) {}
	sorted_table(const sorted_table<K,V>& rhs) :unsorted_table(rhs) {}
	
	V& operator[](const K& k)override
	{
		int idx = binarySearch(this->mas, 0, this->count, k);
		if (idx != -1) return mas[idx].get_access_value();
			else throw runtime_error("key doesn't exist");
	}
	bool find(const K& k)override
	{
		return binarySearch(this->mas, 0, this->count, k)>=0;
	}
	void erase(const K& k)override
	{
		int idx= binarySearch(this->mas, 0, this->count, k);
		if (idx != -1)
		{
			this->shift(idx);
			return;
		}
		throw runtime_error("key doesn't exist and coudn't be erased");
	}
	void add(const K& k, const V& v)override
	{
		if (this->count == this->size)this->realloc(2 * this->size);
		this->mas[count].set_key(k);
		this->mas[count].set_value(v);
		count++;
		sort(this->mas, this->mas + this->count);
	}
};