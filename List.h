#pragma once

#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>
class List
{
private:
	class Node
	{
	private:
		T data;
		Node* next, * prev;

	public:
		Node() : next(nullptr), prev(nullptr) {};
		
		Node(T data) 
		{
			this->data = data;
			next = nullptr;
			prev = nullptr;
		}
		
		~Node() 
		{
			next = nullptr;
			prev = nullptr;
		}
		
		void set_data(T data) 
		{
			this->data = data;
		}
		
		T get_data() 
		{
			return data;
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
	List() : head(nullptr), tail(nullptr) {}
	
	List(int size, int value) 
	{
		while (size--) 
		{
			push_back(value);
		}
	}
	
	List(const List<T>& list) 
	{
		head = nullptr;
		tail = nullptr;
		Node* temp = list.head;
		while (temp) 
		{
			push_back(temp->get_data());
			temp = temp->getNext();
		}
	}
	
	~List()
	{
		while (head)
		{
			tail = head->getNext();
			delete head;
			head = tail;
		}
		head = NULL;
	}

	void push_back(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
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
	
	void push_front(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
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
	
	void push_back(List<bool> ls2)
	{
		Node* temp = ls2.head;
		size_t n = ls2.get_size();
		while ((temp) && (n--))
		{
			push_back(temp->get_data());
			temp = temp->getNext();
		}
	}
	
	void push_front(List& ls2)
	{
		Node* temp = ls2.tail;
		size_t n = ls2.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->getPrevious();
		}
	}
	
	void pop_back()
	{
		if (head != tail)
		{
			Node* temp = tail;
			tail = tail->getPrevious();
			tail->setNext(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = tail;
			tail = head = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	
	void pop_front()
	{
		if (head != tail)
		{
			Node* temp = head;
			head = head->getNext();
			head->setPrevious(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = head;
			head = tail = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	
	void insert(size_t index, T data)
	{
		Node* temp;
		temp = getPointer(index);
		if (temp == head)
			push_front(data);
		else
		{
			Node* newElem = new Node;
			newElem->set_data(data);
			temp->getPrevious()->setNext(newElem);
			newElem->setPrevious(temp->getPrevious());
			newElem->setNext(temp);
			temp->setPrevious(newElem);
		}
	}
	
	T at(size_t index)
	{
		Node* temp;
		temp = getPointer(index);
		return temp->get_data();
	}
	
	void remove(size_t index)
	{
		Node* temp;
		temp = getPointer(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->getPrevious()->setNext(temp->getNext());
			temp->getNext()->setPrevious(temp->getPrevious());
			delete temp;
		}
	}
	
	void remove(T data) 
	{
		Node* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->getNext();
		if (!temp)
			throw out_of_range("Invalid argument");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->getPrevious()->setNext(temp->getNext());
			temp->getNext()->setPrevious(temp->getPrevious());
			delete temp;
		}
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
	
	void print_to_console()
	{
		Node* temp = head;
		while (temp)
		{
			cout << temp->get_data();
			temp = temp->getNext();
		}
	}
	
	void clear()
	{
		while (head)
		{
			tail = head->getNext();
			delete head;
			head = tail;
		}
	}
	
	void set(size_t index, T data)
	{
		Node* temp;
		temp = getPointer(index);
		temp->set_data(data);
	}
	
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
	
	bool compare(List<T> ls) 
	{
		if (get_size() != ls.get_size())
			return false;
		for (int i = 0; i < get_size(); i++) 
		{
			if (at(i) != ls.at(i))
				return false;
		}
		return true;
	}
	
	bool contains(List<char>& ls) 
	{
		Node* temp = head;
		while (temp) 
		{
			if (temp->get_data().compare(ls))
				return true;
			temp = temp->getNext();
		}
		return false;
	}

	void nullify() 
	{
		head = nullptr;
		tail = nullptr;
	}

	void reverse() 
	{
		Node* temp1 = head, * temp2 = tail;
		T value;
		for (size_t i = 0; i < get_size() / 2; i++) 
		{
			value = temp1->get_data();
			temp1->set_data(temp2->get_data());
			temp2->set_data(value);
			temp1 = temp1->getNext();
			temp2 = temp2->getPrevious();
		}
	}

	int get_price(size_t vertex1, size_t vertex2) 
	{
		Node* temp = head;
		while (temp) 
		{
			if (temp->get_data().vertex1 == vertex1 && temp->get_data().vertex2 == vertex2)
				return temp->get_data().cost;
			temp = temp->getNext();
		}
		throw invalid_argument("Incorrect argument");
	}
};