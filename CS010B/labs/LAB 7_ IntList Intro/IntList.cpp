#include "IntList.h"

IntList::IntList() : 
    head(nullptr),
    tail(nullptr)
{
}   

IntList::~IntList() {
    // while (not empty()) {
    //     pop_front();
    // }
    IntNode* p = head;

    //deletes the contents of p and points it to the next node/link
    while (p != nullptr) {
        IntNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }

    // //TODO: see if this works too
    // for (IntNode* p = head; p != nullptr; p = p->next) {
    //     delete p;
    // }

    head = nullptr;
    tail = nullptr;
}

bool IntList::empty() const {
    return head == nullptr;
}

//make new node, point the 'next' to (old) head, and set the new head to n, pushing it to front
void IntList::push_front(int value) {
    IntNode* n = new IntNode(value);

    n->next = head;
    head = n;
    
    //makes the tail equal to the head if there is only one node
    if (tail == nullptr) {
        tail = n;
    }
    //n was not leaked because it (the pointer) disappears with the function, but the memory address is still being used by head
}

void IntList::pop_front() {
    if (empty()) return;

    IntNode* victim = head;
    head = head->next; //set head to the next node
    delete victim; //delete the old head

    if (empty()) {
        tail = nullptr; //if there's nothing in the list, make tail and head nullptr
        head = nullptr;
    }

}

const int &IntList::front() const {
    return head->value;
}

const int &IntList::back() const {
    return tail->value;
}

std::ostream &operator<<(std::ostream & out, const IntList &list) {

    if (list.empty()) return out;

    for (IntNode* p = list.head; p->next != nullptr; p = p->next) { //iterates through list until it gets to the element before the tail
        out << p->value << ' ';
    }
    out << list.tail->value;

    return out;
}