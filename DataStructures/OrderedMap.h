#pragma once
#include <iostream>
using namespace std;

// Map is ordered using a BST
template <typename Key, typename Value>
class OrderedMap
{
private:
	struct Node
	{
		Key key;
		Value value;
		Node* left;
		Node* right;

		Node(Key k = Key{}, Value v = Value{}, Node* l = nullptr, Node* r = nullptr)
			: key(k), value(v), left(l), right(r)
		{
		}
	};

	Node* _root;
	unsigned int _size;

	int sum(const Node* n) const
	{
		if (!n)
			return 0;
		return sum(n->left) + n->value + sum(n->right);
	}

public:
	OrderedMap() : _root(nullptr), _size(0) {}


	Value get(Key key) const
	{
		if (empty())
			throw out_of_range("List is empty");

		Node* curr = _root;

		while (curr != nullptr)
		{
			if (key < curr->key)
				curr = curr->left;
			else if (key > curr->key)
				curr = curr->right;
			else
				return curr->value;
		}
		throw out_of_range("Key not found");
	}

	bool empty() const
	{
		return _root == nullptr;
	}

	void insert(Key key, Value value)
	{

	}

	void remove(Key key)
	{

	}

	Value sum_all_nodes() const
	{
		return sum(_root);
	}
};


