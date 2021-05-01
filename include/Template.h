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
	Node(const k& _k, const v& _v=0):key(_k),value(_v){}

	Node(const Node& l) :key(l.key), value(l.value) {}
	k get_key()const
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
	friend bool operator<(const Node& lhs, const Node& rhs) {
		return lhs.get_key() < rhs.get_key();
	}
	friend bool operator>(const Node& lhs, const Node& rhs)
	{
		return lhs.get_key() > rhs.get_key();
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
	unsorted_table(int _size=1): count(0),size(_size)
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
protected:
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
		return binarySearch(this->mas, 0, this->count-1, k)>=0;
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

template<class K,class V>
class AVL_tree_node 
{
public:
	//todo add 3-rd pointer to the parent's node
	Node<K, V>v;
	AVL_tree_node<K,V>* left;
	AVL_tree_node<K, V>* rigth;
	AVL_tree_node<K, V>* parrent;
	int heigth;


	AVL_tree_node() :heigth(0), left(nullptr), rigth(nullptr),parrent(nullptr){}
	AVL_tree_node(const Node<K, V>& _node) :v(_node) ,heigth(0), left(nullptr), rigth(nullptr), parrent(nullptr)
	{
	}
	
};


template<class A,class B>
class AVL_tree
{
protected:
	AVL_tree_node<A, B>* root;
	void check_parrent(AVL_tree_node<A, B>* _node, AVL_tree_node<A, B>* _node1, AVL_tree_node<A, B>* _node3=nullptr)
	{
		if (_node->parrent != nullptr) {
			if (_node->parrent->left == _node1)_node->parrent->left = _node3;
			else _node->parrent->rigth = _node3;
		}
		else root = _node3;
		
	}
	void ll_turn(AVL_tree_node<A,B>* _n)
	{
		AVL_tree_node<A, B>* p = _n->rigth;
		_n->rigth = _n->rigth->left;
		p->left = _n;
		p->parrent = _n->parrent;
		_n->parrent = p;
		check_parrent(p, _n,p);
		
		_n->heigth = max(get_heigth(_n->left), get_heigth(_n->rigth));
		p->heigth = max(get_heigth(p->left), get_heigth(p->rigth));
	}

	void lr_turn(AVL_tree_node<A, B>* _n)
	{
		AVL_tree_node<A, B>* p = _n->left;
		_n->left = p->rigth;
		p->rigth = _n;
		p->parrent = _n->parrent;
		_n->parrent = p;
		check_parrent(p, _n,p);
	
		_n->heigth = max(get_heigth(_n->left), get_heigth(_n->rigth));
		p->heigth = max(get_heigth(p->left), get_heigth(p->rigth));
	}
	void bl_turn(AVL_tree_node<A, B>* _n)
	{
		lr_turn(_n->rigth);
		ll_turn(_n);
	}
	void br_turn(AVL_tree_node<A, B>* _n)
	{
		ll_turn(_n->left);
		lr_turn(_n);
	}
	friend int get_heigth(AVL_tree_node<A, B>* ptr)
	{
		if (ptr)return ptr->heigth;
		else return 0;
	}
	void balance(AVL_tree_node<A, B>* _n)
	{
		if (get_heigth(_n->rigth) - get_heigth(_n->left) == 2) {
			if (get_heigth(_n->rigth->left) <= get_heigth(_n->rigth->rigth)) ll_turn(_n);
			else
				bl_turn(_n);
		}
		if (get_heigth(_n->left) - get_heigth(_n->rigth) == 2) {
			if (get_heigth(_n->left->rigth) <= get_heigth(_n->left->left)) lr_turn(_n);
			else
				br_turn(_n);
		}
	}

	void find_min(AVL_tree_node<A, B>* ptr,AVL_tree_node<A,B>* node)
	{
		if (get_heigth(ptr) == 0)
		{
			if(ptr!=node)swap(ptr->v, node->v);
			check_parrent(ptr,ptr);
			delete ptr;
			return;
		}
		if (get_heigth(ptr->left) <= get_heigth(ptr->rigth))find_min(ptr->rigth,node);
		else find_min(ptr->left,node);
		balance(ptr);
	}
	void delete_nodes(AVL_tree_node<A, B>* _node)
	{
		if (_node->left != nullptr)
		{
			delete_nodes(_node->left);
			_node->left = nullptr;
		}
		if (_node->rigth != nullptr)
		{
			delete_nodes(_node->rigth);
			_node->rigth = nullptr;
		}
		if ((_node->rigth == _node->rigth)) delete _node;
	}
	
public:
	AVL_tree(Node<A, B>& r)
	{
		root = new AVL_tree_node<A,B>(r);
	}
	~AVL_tree()
	{
		delete_nodes(root);
	}
	void insert( Node<A, B>& n, AVL_tree_node<A,B>*_root)
	{
		if (_root->v> n)
		{
			if (_root->left != nullptr)
			{
				insert(n, _root->left);
			}
			else
			{
				_root->left = new AVL_tree_node<A, B>(n);
				_root->left->parrent = _root;
				
			}
			_root->heigth = max(get_heigth(_root->left)+1, get_heigth(_root->rigth));
		}
		if(_root->v< n)
		{
			if (_root->rigth != nullptr)
			{
				insert(n, _root->rigth);
			}
			else
			{
				_root->rigth = new AVL_tree_node<A, B>(n);
				_root->rigth->parrent = _root;
				
			}
			_root->heigth=max(get_heigth(_root->left), get_heigth(_root->rigth)+1);
		}
		balance(_root);
		
	}
	AVL_tree_node<A,B>* get_root()
	{
		return root;
	}
	bool find(const Node<A, B>& n, AVL_tree_node<A,B>* _root)
	{
		if (_root == nullptr)return 0;
		if (n == _root->v)return 1;
		if (n < _root->v) {
			return find(n, _root->left);
		}
		if (n > _root->v) {
			return find(n, _root->rigth);
		}
	}
	B& find_and_get(const Node<A, B>& n, AVL_tree_node<A,B>* _root)
	{
		if (_root == nullptr) throw runtime_error("key doesn't exist");
		if (n == _root->v) return _root->v.get_access_value();
		if (n < _root->v) return find_and_get(n, _root->left);
		if (n > _root->v)return find_and_get(n, _root->rigth);
	}
	void erase(const Node<A, B>& n, AVL_tree_node<A,B>* _root)
	{
		if (_root == nullptr) throw runtime_error("key doesn't exist");
		if (n < _root->v) erase(n, _root->left);
		if (n > _root->v)erase(n, _root->rigth);
		if (n == _root->v)
		{
			find_min(_root,_root);
			return;
		}
		balance(_root);
	}

	
};


template<class K,class V>
class AVL_table
{
protected:
	AVL_tree<K,V> t;

public:
	AVL_table(Node<K,V>& sp):t(sp){}
	V& operator[](const K& k)
	{
		 return t.find_and_get(Node<K, V>(k), t.get_root());
	}
	bool find(const K& k)
	{
		return t.find(Node<K, V>(k), t.get_root());
	}
	void add(const K& k, const V& v)
	{
		 t.insert(Node<K, V>(k, v), t.get_root());
	}
	void erase(const K& k)
	{
		t.erase(Node<K, V>(k), t.get_root());
	}
	
};