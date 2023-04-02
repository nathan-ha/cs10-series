#ifndef INTLIST_H
#define INTLIST_H

#include <ostream>

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
        void push_front(int value);
        void pop_front();
        bool empty() const;
        const int &front() const;
        const int &back() const;

        IntList(const IntList &origList);
        void push_back(int value);

        friend std::ostream & operator<<(std::ostream &, const IntList &);
        void selection_sort();
        void clear();
        void insert_ordered(int value);
        IntList &operator=(const IntList &rhs);

        void remove_duplicates();

        void remove_max();

};

#endif