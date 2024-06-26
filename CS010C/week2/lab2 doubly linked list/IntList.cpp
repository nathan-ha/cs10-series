#include "IntList.h"
#include <iostream>

//create a doubly linked list with a dummy head and tail
IntList::IntList() : head(new IntNode(0)), tail (new IntNode(0)) {
	head->next = tail;
	head->prev = nullptr;
	tail->next = nullptr;
	tail->prev = head;
}

IntList::~IntList() {
	//delete all nodes, including dummy nodes
	for (IntNode* currNode = head; currNode != nullptr;) {
		IntNode* victim = currNode;
		currNode = currNode->next;
		delete victim;
	}
	head = nullptr;
	tail = nullptr;
}

void IntList::push_front(int value) {
	IntNode* newNode = new IntNode(value);
	//make new node and connect it to head and it's neighboring node
	newNode->next = head->next;
	newNode->prev = head;
	head->next->prev = newNode;
	head->next = newNode;
}

void IntList::pop_front() {
	if (empty()) return; //don't do anything if empty
	IntNode* victim = head->next;
	//connect nodes around victim
	head->next->next->prev = head;
	head->next = head->next->next;
	delete victim;
}

void IntList::push_back(int value) {
	IntNode* newNode = new IntNode(value);
	//connect new node to tail and the node next to it
	newNode->next = tail;
	newNode->prev = tail->prev;
	tail->prev->next = newNode;
	tail->prev = newNode;
}

void IntList::pop_back() {
	if (empty()) return;
	IntNode* victim = tail->prev;
	//connect nodes around the node before tail
	tail->prev->prev->next = tail;
	tail->prev = tail->prev->prev;
	delete victim;
}

bool IntList::empty() const {
	return head->next == tail; //if there are only a head and a tail, then the list is empty
}

//output everything except head and tail
std::ostream& operator<<(std::ostream &out, const IntList &rhs) {
	if (rhs.empty()) return out; //return empty stream if list is empty
	//outputs every value, and adds a space after it (except the last value which is output in the line after)
	for (IntNode* currNode = rhs.head->next; currNode != rhs.tail->prev; currNode = currNode->next) {
		out << currNode->data << ' '; 
	}
	out << rhs.tail->prev->data;
	return out;
}

void IntList::printReverse() const {
	if (empty()) return;
	//prints out all node data. same logic as the operator << overload but starting from end
	for (IntNode* currNode = tail->prev; currNode != head->next; currNode = currNode->prev) {
		std::cout << currNode->data << ' ';
	}
	std::cout << head->next->data;
}