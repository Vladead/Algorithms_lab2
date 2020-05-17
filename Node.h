#pragma once

enum Color {
	black,
	red,
};

template <typename Key, typename Value1, class Value2>
class Node
{
private :
	Color color;

	Node<Key, Value1, Value2>* left, * right, * parent;

	Key key;

	Value1 value1;

	Value2 value2;

public:
	Node() : color(red), left(nullptr), right(nullptr), parent(nullptr) {}

	Node(Key key, Value1 value1) : color(red), left(nullptr), right(nullptr), parent(nullptr), key(key), value1(value1) {}
	
	Node(Key key, Value1 value1, Value2 value2) : color(red), left(nullptr), right(nullptr), parent(nullptr), key(key), value1(value1), value2(value2) {}
	
	bool isOnLeft() {
		return this == parent->getLeft(); 
	}

	Node<Key, Value1, Value2>* sibling() 
	{
		// sibling null if no parent 
		if (parent == nullptr)
			return nullptr;

		if (isOnLeft())
			return parent->right;

		return parent->left;
	}

	bool hasRedChild() 
	{
		return (left != nullptr && left->getColor() == red) || (right != nullptr && right->getColor() == red);
	}

	void setColor(Color color) 
	{
		this->color = color;
	}

	Color getColor() 
	{
		if (this == nullptr)
			return black;
		return color;
	}

	void setLeft(Node* ptr)
	{
		left = ptr;
	}

	Node* getLeft()
	{
		return left;
	}

	void setRight(Node* ptr)
	{
		right = ptr;
	}

	Node* getRight()
	{
		return right;
	}

	void setParent(Node* parent) 
	{
		this->parent = parent;
	}

	Node* getParent() 
	{
		return parent;
	}

	void setKey(Key key)
	{
		this->key = key;
	}

	Key getKey()
	{
		return key;
	}

	void setValue1(Value1 value)
	{
		this->value1 = value;
	}

	Value1 getValue1()
	{
		return value1;
	}

	void setValue2(Value2 value)
	{
		value2.push_front(value);
	}

	Value2 getValue2()
	{
		return value2;
	}
};