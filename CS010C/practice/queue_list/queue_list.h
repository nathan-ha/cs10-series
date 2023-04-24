#pragma once
#include <stdexcept>
#include <iostream>

template <typename T>
class queue_list {
    struct node {
        T data;
        node* next;
        node(T data): data(data), next(nullptr) {}
    };

    node* head;
    node* tail;

    queue_list operator=(const queue_list& rhs);
    queue_list(const queue_list& originalStack);
public:
    queue_list(): head(nullptr), tail(nullptr) {}
    ~queue_list();
    void push_back(T val); //push back
    void pop(); //pop front
    void pop_two();
    T& front() const;
    bool empty() const;
    void print() const;
};

template <typename T>
bool queue_list<T>::empty() const {
    return head == nullptr;
}

template <typename T>
queue_list<T>::~queue_list() {
    while (head != nullptr) {
        auto victim = head;
        head = head->next;
        delete victim;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename T>
void queue_list<T>::push_back(T val) {
    node* newNode = new node(val);
    if (empty()) {
        head = newNode;
        tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

template <typename T>
void queue_list<T>::pop() {
    if (empty()) {
        throw std::out_of_range("called pop on empty queue");
    }
    node* victim = head;
    head = head->next;
    delete victim;
}

template <typename T>
void queue_list<T>::pop_two() {
    if (empty()) {
        throw std::out_of_range("called pop_two() on empty queue");
    }
    if (head->next == nullptr) { //only one node
        throw std::out_of_range("called pop_two() on queue with one element");
    }
    node* victim1 = head;
    node* victim2 = head->next;
    head = head->next->next;
    delete victim1;
    delete victim2;
}

template <typename T>
T& queue_list<T>::front() const {
    if (empty()) {
        throw std::out_of_range("called front() on empty queue");
    }
    return head->data;
}

template <typename T>
void queue_list<T>::print() const {
    if (empty()) {
        throw std::out_of_range("called print() on empty queue");
    }
    for (auto p = head; p != nullptr; p = p->next) {
        std::cout << p->data << ' ';
    }
    std::cout << std::endl;
}

