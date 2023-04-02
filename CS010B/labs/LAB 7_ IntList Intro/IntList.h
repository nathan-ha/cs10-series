#ifndef INTLIST_H
#define INTLIST_H

#include <ostream>
#include <iostream>

struct IntNode {
    int value;
    IntNode* next;
    IntNode(int value) : value(value), next(nullptr) {}
};

class IntList {
    private:
        IntNode* head;
        IntNode* tail;
    public:
        IntList();
        ~IntList();
        void push_front(int);
        void pop_front();
        bool empty() const;
        const int &front() const;
        const int &back() const;
        friend std::ostream & operator<<(std::ostream &, const IntList &);

        // void print() {
        //     for (IntNode* p = head; p != nullptr; p = p->next) {
        //         std::cout << p->value << ", ";
        //     }
        //     std::cout << std::endl;
        // }
};

#endif