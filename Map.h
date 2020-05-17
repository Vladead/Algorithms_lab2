#pragma once

#include "Node.h"
#include <iostream>
#include "List.h"
#include <windows.h>

using namespace std;

template <typename Key, typename Value1, class Value2>
class Map
{
private:
	Node<Key, Value1, Value2>* root;
	
	//Sets color of console
	void SetColor(int text, int background)
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
	}
	
	//Fixes tree after insertation
	void balanceTree(Node<Key, Value1, Value2>*& node) 
	{
		if (root == node) 
		{
			node->setColor(black);
			return;
		}
		
		Color color;
		
		Node<Key, Value1, Value2>* parent = nullptr, * grandparent = nullptr, * uncle = nullptr;
		
		while (node != root && node->getColor() == red && node->getParent()->getColor() == red) 
		{
			parent = node->getParent();
			grandparent = parent->getParent();
			if (parent == grandparent->getLeft()) 
			{
				uncle = grandparent->getRight();
				if (uncle->getColor() == red) 
				{
					parent->setColor(black);
					grandparent->setColor(red);
					uncle->setColor(black);
					node = grandparent;
				}
				else 
				{
					if (node == parent->getRight()) 
					{
						leftRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					rightRotate(grandparent);
					color = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(color);
					node = parent;
				}
			}
			else 
			{
				uncle = grandparent->getLeft();
				if (uncle->getColor() == red) 
				{
					parent->setColor(black);
					grandparent->setColor(red);
					uncle->setColor(black);
					node = grandparent;
				}
				else 
				{
					if (node == parent->getLeft()) 
					{
						rightRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					leftRotate(grandparent);
					color = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(color);
					node = parent;
				}
			}
		}
		root->setColor(black);
	}

	//Returns extreme left element
	Node<Key, Value1, Value2>* minValueNode(Node<Key, Value1, Value2>* node) 
	{

		Node<Key, Value1, Value2>* ptr = node;

		while (ptr->getLeft() != nullptr)
			ptr = ptr->getLeft();

		return ptr;
	}

	void leftRotate(Node<Key, Value1, Value2>* node) 
	{
		Node<Key, Value1, Value2>* rightChild = node->getRight();
		node->setRight(rightChild->getLeft());

		if (node->getRight() != nullptr)
			node->getRight()->setParent(node);

		rightChild->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = rightChild;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(rightChild);
		else
			node->getParent()->setRight(rightChild);

		rightChild->setLeft(node);
		node->setParent(rightChild);
	}
	
	void rightRotate(Node<Key, Value1, Value2>* node) 
	{
		Node<Key, Value1, Value2>* leftChild = node->getLeft();
		node->setLeft(leftChild->getRight());

		if (node->getLeft() != nullptr)
			node->getLeft()->setParent(node);

		leftChild->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = leftChild;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(leftChild);
		else
			node->getParent()->setRight(leftChild);

		leftChild->setRight(node);
		node->setParent(leftChild);
	}
	
	//Auxiliary function for deleting map
	void delSubTree(Node<Key, Value1, Value2>* node) 
	{
		while (node != nullptr) {
			delSubTree(node->getLeft());
			delSubTree(node->getRight());
			delete node;
			node = nullptr;
		}
		root = nullptr;
	}
	
	//Auxiliary function for output
	void print_node(Node<Key, Value1, Value2>* node, int level, bool side)
	{
		for (int i = 0; i < level; i++)
			cout << ' ';
		if (level != 0)
		{
			cout << '|';
			cout << "->";
			if (side == false)
				cout << "L: ";
			else
				cout << "R: ";
		}
		else
			cout << ' ';
		if (node) 
		{
			if (node->getColor() == black)
				SetColor(9, 0);
			else
				SetColor(12, 0);
			cout << node->getKey() << '(' << node->getValue1() << ')' << endl;
			SetColor(7, 0);
		}
		else 
		{
			SetColor(9, 0);
			cout << "nil" << endl;
			SetColor(7, 0);
		}
		if (node)
		{
			if (level > 0)
			{
				if (node->getLeft() || node->getRight())
				{
					print_node(node->getLeft(), level + 3, false);
					print_node(node->getRight(), level + 3, true);
				}
			}
			else
			{
				if (node->getLeft() || node->getRight())
				{
					print_node(node->getLeft(), level + 1, false);
					print_node(node->getRight(), level + 1, true);
				}
			}
		}
	}

	void setKeys(List<Key>& key, Node<Key, Value1, Value2>* node) 
	{
		while (node) 
		{
			setKeys(key, node->getLeft());
			key.push_back(node->getKey());
			setKeys(key, node->getRight());
			return;
		}
	}

	void setValues1(List<Value1>& value, Node<Key, Value1, Value2>* node) 
	{
		while (node) 
		{
			setValues1(value, node->getLeft());
			value.push_back(node->getValue1());
			setValues1(value, node->getRight());
			return;
		}
	}

	void setValues2(List<Value2>& key, Node<Key, Value1, Value2>* node) 
	{
		while (node) 
		{
			setValues2(key, node->getLeft());
			key.push_back(node->getValue2());
			setValues2(key, node->getRight());
			return;
		}
	}

	// finds node that replaces a deleted node in BST 
	Node<Key, Value1, Value2>* replace(Node<Key, Value1, Value2>* x) 
	{
		// when node have 2 children 
		if (x->getLeft() != nullptr && x->getRight() != nullptr)
			return minValueNode(x->getRight());

		// when leaf 
		if (x->getLeft() == nullptr && x->getRight() == nullptr)
			return nullptr;

		// when single child 
		if (x->getLeft() != nullptr)
			return x->getLeft();
		else
			return x->getRight();
	}

	// returns pointer to element with required key 
	Node<Key, Value1, Value2>* search(Key key) 
	{
		Node<Key, Value1, Value2>* temp = root;
		while (temp != nullptr && key != temp->getKey()) 
		{
			if (key < temp->getKey()) 
			{
				temp = temp->getLeft();
			}
			else 
			{
				temp = temp->getRight();
			}
		}
		return temp;
	}

	void swapValues(Node<Key, Value1, Value2>* firstNode, Node<Key, Value1, Value2>* secondNode) 
	{
		Key key = firstNode->getKey();
		firstNode->setKey(secondNode->getKey());
		secondNode->setKey(key);
		Value1 value1 = firstNode->getValue1();
		firstNode->setValue1(secondNode->getValue1());
		secondNode->setValue1(value1);
		Value2 value2 = firstNode->getValue2();
		firstNode->setValue2(secondNode->getValue2());
		secondNode->setValue2(value2);
	}
	
	// deletes the given node 
	void deleteNode(Node<Key, Value1, Value2>* deletedNode) 
	{
		Node<Key, Value1, Value2>* temp = replace(deletedNode);

		// True when temp and deletedNode are both black 
		bool uvBlack = ((temp == nullptr || temp->getColor() == black) && (deletedNode->getColor() == black));
		Node<Key, Value1, Value2>* parent = deletedNode->getParent();

		if (temp == nullptr) 
		{
			// temp is nullptr therefore deletedNode is leaf 
			if (deletedNode == root) 
			{
				// deletedNode is root, making root nullptr 
				root = nullptr;
			}
			else 
			{
				if (uvBlack) 
				{
					// temp and deletedNode both black 
					// deletedNode is leaf, fix double black at deletedNode 
					fixTree(deletedNode);
				}
				else 
				{
					// temp or deletedNode is red 
					if (deletedNode->sibling() != nullptr)
						// sibling is not nullptr, make it red" 
						deletedNode->sibling()->setColor(red);
				}

				// delete deletedNode from the tree 
				if (deletedNode->isOnLeft()) 
				{
					parent->setLeft(nullptr);
				}
				else 
				{
					parent->setRight(nullptr);
				}
			}
			delete deletedNode;
			return;
		}

		if (deletedNode->getLeft() == nullptr || deletedNode->getRight() == nullptr) 
		{
			// deletedNode has 1 child 
			if (deletedNode == root) 
			{
				// deletedNode is root, assign the value of temp to deletedNode, and delete temp 
				deletedNode->setKey(temp->getKey());
				deletedNode->setLeft(nullptr);
				deletedNode->setRight(nullptr);
				delete temp;
			}
			else 
			{
				// Detach deletedNode from tree and move temp up 
				if (deletedNode->isOnLeft()) 
				{
					parent->setLeft(temp);
				}
				else 
				{
					parent->setRight(temp);
				}
				delete deletedNode;
				temp->setParent(parent);
				if (uvBlack) 
				{
					// temp and deletedNode both black, fix double black at temp 
					fixTree(temp);
				}
				else 
				{
					// temp or deletedNode red, color temp black 
					temp->setColor(black);
				}
			}
			return;
		}
		// deletedNode has 2 children, swap values 
		swapValues(temp, deletedNode);
		deleteNode(temp);
	}

	// fixes tree after deletion
	void fixTree(Node<Key, Value1, Value2>* rootNode) 
	{
		if (rootNode == root)
			// Reached root 
			return;

		Node<Key, Value1, Value2>* sibling = rootNode->sibling(), * parent = rootNode->getParent();
		if (sibling == nullptr) 
		{
			// No sibiling, double black pushed up 
			fixTree(parent);
		}
		else 
		{
			if (sibling->getColor() == red) 
			{
				// Sibling red 
				parent->setColor(red);
				sibling->setColor(black);
				if (sibling->isOnLeft()) 
				{
					// left case 
					rightRotate(parent);
				}
				else 
				{
					// right case 
					leftRotate(parent);
				}
				fixTree(rootNode);
			}
			else 
			{
				// Sibling black 
				if (sibling->hasRedChild()) 
				{
					// at least 1 red children 
					if (sibling->getLeft() != nullptr && sibling->getLeft()->getColor() == red) 
					{
						if (sibling->isOnLeft()) 
						{
							// left left 
							sibling->getLeft()->setColor(sibling->getColor());
							sibling->setColor(parent->getColor());
							rightRotate(parent);
						}
						else 
						{
							// right left 
							sibling->getLeft()->setColor(parent->getColor());
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else 
					{
						if (sibling->isOnLeft()) 
						{
							// left right 
							sibling->getRight()->setColor(parent->getColor());
							leftRotate(sibling);
							rightRotate(parent);
						}
						else 
						{
							// right right 
							sibling->getRight()->setColor(sibling->getColor());
							sibling->setColor(parent->getColor());
							leftRotate(parent);
						}
					}
					parent->setColor(black);
				}
				else 
				{
					// 2 black children 
					sibling->setColor(red);
					if (parent->getColor() == black)
						fixTree(parent);
					else
						parent->setColor(black);
				}
			}
		}
	}

public:
	Map() : root(nullptr) {}
	
	~Map() 
	{
		delSubTree(root);
	}

	//Inserts node using key with value
	void insert(Key key, Value1 value1, Value1 value2) 
	{
		Node<Key, Value1, Value2>* insertedNode = new Node<Key, Value1, Value2>(key, value1);
		if (!root) 
		{
			root = insertedNode;
		}
		else 
		{
			Node<Key, Value1, Value2>* rootNode = root;
			Node<Key, Value1, Value2>* temp = nullptr;
			while (rootNode != nullptr) 
			{
				temp = rootNode;
				if (rootNode->getKey() < insertedNode->getKey()) 
				{
					rootNode = rootNode->getRight();
				}
				else if (rootNode->getKey() == insertedNode->getKey())
				{
					delete insertedNode;
					rootNode->setValue1(rootNode->getValue1() + value2);
					return;
				}
				else 
				{
					rootNode = rootNode->getLeft();
				}
			}
			insertedNode->setParent(temp);
			if (temp->getKey() <= insertedNode->getKey()) 
			{
				temp->setRight(insertedNode);
			}
			else 
			{
				temp->setLeft(insertedNode);
			}
		}
		balanceTree(insertedNode);
	}

	//Removes an element
	void remove(Key key) 
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty");

		Node<Key, Value1, Value2>* node = search(key);

		if (node->getKey() != key) 
		{
			throw invalid_argument("This element isn't in the map");
		}

		deleteNode(node);
	}

	//Returns the value using key
	Value1 findValue1(Key key) 
	{
		if (!root)
			throw invalid_argument("Map is empty");
		Node<Key, Value1, Value2>* temp = root;
		while (temp && temp->getKey() != key) 
		{
			if (temp->getKey() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		if (!temp)
			throw invalid_argument("This element isn't in the map");
		return temp->getValue1();
	}

	Value2 findValue2(Key key) 
	{
		if (!root)
			throw invalid_argument("Map is empty");
		Node<Key, Value1, Value2>* temp = root;
		while (temp && temp->getKey() != key) 
		{
			if (temp->getKey() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		if (!temp)
			throw invalid_argument("This element isn't in the map");
		return temp->getValue2();
	}

	//Cleans the map
	void clear() 
	{
		if (root == nullptr)
			throw runtime_error("The map is empty");
		delSubTree(root);
	}

	//Returns a copy of list that contains keys of map
	List<Key> get_keys() 
	{
		List<Key> temp;
		setKeys(temp, root);
		return temp;
	}

	//Returns a copy of list that contains values of map
	List<Value1> getValue1() 
	{
		List<Value1> temp;
		setValues1(temp, root);
		return temp;
	}
	List<Value2> getValue2() 
	{
		List<Value2> temp;
		setValues2(temp, root);
		return temp;
	}

	//Prints red-black map
	void print()
	{
		if (root == nullptr)
			throw runtime_error("Map is empty");
		int level = 0;
		print_node(root, level, false);
		cout << endl;
	}

	void value1Increase(Key key, Value1 value) 
	{
		Node<Key, Value1, Value2>* temp = search(key);
		temp->setValue1(temp->getValue1() + value);
	}

	void setValue2(Key key, Value2& value) 
	{
		Node<Key, Value1, Value2>* temp = search(key);
		temp->setValue2(value);
	}

	Key findKey(Value2 code) 
	{
		Key key = NULL;
		bool is_found = false;
		auxiliaryFindKey(root, code, key, is_found);
		return key;
	}

	bool codeInDict(Value2 code) 
	{
		bool is_found = false;
		return auxiliaryCodeInDict(root, code, is_found);
	}

	void auxiliaryFindKey(Node<Key, Value1, Value2>* node, Value2 code, Key& key, bool& isFound) 
	{
		if (node) 
		{
			if (node->getValue2().compare(code)) 
			{
				key = node->getKey();
				isFound = true;
				return;
			}
			else 
			{
				auxiliaryFindKey(node->getLeft(), code, key, isFound);
				if (isFound)
					return;
				auxiliaryFindKey(node->getRight(), code, key, isFound);
			}
		}
	}

	bool auxiliaryCodeInDict(Node<Key, Value1, Value2>* node, Value2 code, bool& isFound) 
	{
		if (node) 
		{
			if (node->getValue2().compare(code)) 
			{
				isFound = true;
				return true;
			}
			else 
			{
				auxiliaryCodeInDict(node->getLeft(), code, isFound);
				if (isFound)
					return true;
				auxiliaryCodeInDict(node->getRight(), code, isFound);
				return isFound;
			}
		}
	}
};

