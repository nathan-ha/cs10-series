#pragma once
#include <iostream>

struct IntNode {
    int data;
    IntNode* prev;
    IntNode* next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
private:
	IntNode* head;
	IntNode* tail;
	//disallows copies
	IntList(const IntList& originalList);
	IntList operator=(const IntList& rhs);
public:
	IntList();
	~IntList();
	void push_front(int value);
	void pop_front();
	void push_back(int value);
	void pop_back();
	bool empty() const;
	friend std::ostream& operator<<(std::ostream &out, const IntList &rhs);	
	void printReverse() const;
};


