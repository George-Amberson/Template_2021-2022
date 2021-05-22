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

	Node& operator++()
	{
		value++;
		return(*this);
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
	AVL_tree() :root(nullptr) {}
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
		if (_root->v == n)
		{
			++(_root->v);
			return;
		}
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
	
	bool empty()
	{
		return(root == nullptr);
	}
	void set_root(AVL_tree_node<A, B>* p)
	{
		root = p;
	}
	void cout(AVL_tree_node<A, B>* ptr, ostream& out)
	{
		if (ptr->left != nullptr)cout(ptr->left,out);
		if (ptr->rigth != nullptr)cout(ptr->rigth,out);
		out << ptr->v.get_key() << " "<<ptr->v.get_value() << endl;
	}
};


template<class K,class V>
class AVL_table
{
protected:
	AVL_tree<K,V> t;

public:
	AVL_table() {}
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
		if (t.empty())
		{
			t.set_root( new  AVL_tree_node<K, V>(Node<K,V>(k,v)));
			return;
		}
		 t.insert(Node<K, V>(k, v), t.get_root());
	}
	void erase(const K& k)
	{
		t.erase(Node<K, V>(k), t.get_root());
	}
	friend ostream& operator<< (ostream& o, AVL_table<K, V>& _t)
	{
		_t.t.cout(_t.t.get_root(),o);
		return o;
	}
};