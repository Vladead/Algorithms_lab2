#pragma once

#include "List.h"

template<typename T1, typename T2>
class ListWithTwoValues
{
private:
	T2 value2;

	class Node
	{
	private:
		T1 data1;
		T2 data2;
		Node* next, * prev;

	public:
		Node() : next(nullptr), prev(nullptr) {};

		Node(T1 data1, T2 data2) 
		{
			this->data1 = data1;
			this->data2 = data2;
			next = nullptr;
			prev = nullptr;
		}

		~Node() 
		{
			next = nullptr;
			prev = nullptr;
		}

		void setFirstValue(T1 data) 
		{
			this->data1 = data;
		}

		void setSecondValue(T2 data) 
		{
			this->data2 = data;
		}

		T1 getFirstValue() 
		{
			return data1;
		}

		T2 getSecondValue() 
		{
			return data2;
		}

		Node* getNext() 
		{
			return next;
		}

		Node* getPrevious() 
		{
			return prev;
		}

		void setNext(Node* pointer) 
		{
			next = pointer;
		}

		void setPrevious(Node* pointer) 
		{
			prev = pointer;
		}
	};

	Node* head, * tail;
	
	Node* getPointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->getNext();
			}
			return temp;
		}
	}
public:
	ListWithTwoValues() {};

	void push_back(T1 data1, T2 data2)
	{
		Node* temp = new Node;
		temp->setFirstValue(data1);
		temp->setSecondValue(data2);
		if (head)
		{
			temp->setPrevious(tail);
			tail->setNext(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	T1 atFirstValue(size_t index)
	{
		Node* temp;
		temp = getPointer(index);
		return temp->getFirstValue();
	}

	void push_front(T1 data1, T2 data2)
	{
		Node* temp = new Node;
		temp->setFirstValue(data1);
		temp->setSecondValue(data2);
		if (head)
		{
			temp->setNext(head);
			head->setPrevious(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	void sorted_insert(T1 data1, T2 data2) {
		if (!head || head->getSecondValue() < data2) 
		{
			push_front(data1, data2);
			return;
		}
		Node* newElem = new Node;
		newElem->setFirstValue(data1);
		newElem->setSecondValue(data2);
		int i = 0;
		Node* temp = head;
		while (temp) 
		{
			if (temp->getSecondValue() < data2) 
			{
				temp->getPrevious()->setNext(newElem);
				newElem->setPrevious(temp->getPrevious());
				temp->setPrevious(newElem);
				newElem->setNext(temp);
				return;
			}
			if (temp->getFirstValue() == data1 && temp->getSecondValue() == data2) 
			{
				delete newElem;
				return;
			}
			i++;
			temp = temp->getNext();
		}
		delete newElem;
		push_back(data1, data2);
	}

	void insert(size_t index, T1 data1, T2 data2)
	{
		Node* temp;
		temp = getPointer(index);
		if (temp == head)
			push_front(data1, data2);
		else
		{
			Node* newElem = new Node;
			newElem->setFirstValue(data1);
			newElem->setSecondValue(data2);
			temp->getPrevious()->setNext(newElem);
			newElem->setPrevious(temp->getPrevious());
			newElem->setNext(temp);
			temp->setPrevious(newElem);
		}
	}

	T2 atSecondValue(size_t index)
	{
		Node* temp;
		temp = getPointer(index);
		return temp->getSecondValue();
	}

	void set(size_t index, T1 data1, T2 data2)
	{
		Node* temp;
		temp = getPointer(index);
		temp->setFirstValue(data1);
		temp->setSecondValue(data2);
	}

	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}

	size_t get_size()
	{
		Node* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->getNext();
		}
		return length;
	}
};