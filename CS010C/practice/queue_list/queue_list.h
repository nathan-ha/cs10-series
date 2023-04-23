#pragma once
#include <stdexcept>

template <typename T>
class queue_list {
    struct node {
        T data;
        node* next;
        node(T data): data(data), next(nullptr) {}
    };

    node* head;

    queue_list operator=(const queue_list& rhs);
    queue_list(const queue_list& originalStack);
public:
    queue_list(): head(nullptr) {}
    ~queue_list();
    void push(T val);
    void pop();
    void pop_two();
    T& top() const;
    bool empty() const;
};