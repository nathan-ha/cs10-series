#pragma once
#include <stdexcept>
#include <iostream>

template <typename T>
class stack_list {
    struct node {
        T data;
        node* next;
        node(T data): data(data), next(nullptr) {}
    };

    node* head;

    stack_list operator=(const stack_list& rhs);
    stack_list(const stack_list& originalStack);
public:
    stack_list(): head(nullptr) {}
    ~stack_list();
    void push(T val);
    void pop();
    void pop_two();
    T& top() const;
    bool empty() const;
    void print() const;
};


template<typename T>
stack_list<T>::~stack_list() {
    while (head != nullptr) {
        node* victim = head;
        head = head->next;
        delete victim;
    }
    head = nullptr;
}

template<typename T>
bool stack_list<T>::empty() const {
    return head == nullptr;
}

template <typename T>
void stack_list<T>::push(T val) {
    if (empty()) {
        head = new node(val);
        return;
    }
    node* newNode = new node(val);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void stack_list<T>::pop() {
    if (empty()) {
        throw std::out_of_range("called pop on empty stack");
    }
    node* victim = head;
    head = head->next;
    delete victim;
}

template <typename T>
void stack_list<T>::pop_two() {
    if (empty()) {
        throw std::out_of_range("called pop on empty stack");
    }
    if (head->next == nullptr) {
        throw std::out_of_range("called pop_two on stack with one element");
    }
    node* victim1 = head;
    node* victim2 = head->next;
    head = head->next->next;
    delete victim1;
    delete victim2;
}

template <typename T>
T& stack_list<T>::top() const {
    if (empty()) {
        throw std::out_of_range("called top on empty stack");
    }
    return head->data;
}

template <typename T>
void stack_list<T>::print() const {
    for (node* i = head; i != nullptr; i = i->next) {
        std::cout << i->data << ' ';
    }
    std::cout << std::endl;
}



