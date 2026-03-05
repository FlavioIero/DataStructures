#pragma once

// this is a simple BST with the rule 
// left < node < right and a node counter
// size is the sum of all node->count
template <typename Value>
class BinarySearchTree
{
private:
	struct Node
	{
		Value val;
		unsigned int count;
		Node* left;
		Node* right;

		Node(Value v = Value{}, Node* l = nullptr, Node* r = nullptr) : val(v), left(l), right(r), count(1) {}
	};

	Node* _root;
	unsigned int _size;

public:
	BinarySearchTree() : _root(nullptr), _size(0) {}

	inline bool empty() const
	{
		return _root == nullptr;
	}

	inline int size() const
	{
		return _size;
	}

	void insert(Value value)
	{
		insert(value, _root);
	}

	void remove(Value value)
	{
		remove(value, _root);
	}

	Value sum() const
	{
		return sum(_root);
	}

private:
	void insert(Value value, Node*& node)
	{
		if (!node)
		{
			node = new Node(value);
			_size++;
			return;
		}

		if (value < node->val)
		{
			insert(value, node->left);
		}
		else if (value > node->val)
		{
			insert(value, node->right);
		}
		else
		{
			node->count++;
			_size++;
		}
	}

	// da finire
	void remove(Value value, Node*& node, Node*& parent)
	{
		if (!node)
			return;

		if (value < node->val)
		{
			remove(value, node->left, node);
		}
		else if (value > node->val)
		{
			remove(value, node->right, node);
		}
		else
		{
			node->count--;
			_size--;
			if (node->count == 0)
			{

			}
		}
	}

	Value sum(const Node* node) const
	{
		if (!node)
			return 0;
		return sum(node->left) + node->value + sum(node->right);
	}
};
