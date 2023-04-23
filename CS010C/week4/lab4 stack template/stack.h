#pragma once
#include <stdexcept>

const int MAX_SIZE = 20;

template <typename T>
class stack {
    T* data_;
    int size_;
    //disallows copies
    stack operator=(const stack& rhs);
    stack(const stack& originalStack);
public:
    stack(): data_(new T[MAX_SIZE]), size_(0) {}
    ~stack();
    void push(T val);
    void pop();
    void pop_two();
    T& top() const;
    bool empty() const;
};

template <typename T>
stack<T>::~stack() {
    delete[] data_;
    data_ = nullptr;
}

template <typename T>
bool stack<T>::empty() const {
    return size_ <= 0;
}

template <typename T>
void stack<T>::push(T val) {
    if (size_ >= MAX_SIZE) { //edge case: stack is full
        throw std::overflow_error("Called push on full stack.");
    }
    //add element to end of array
    data_[size_] = val;
    size_++;
}

template<typename T>
void stack<T>::pop() {
    if (empty()) { //edge case: stack is empty
        throw std::out_of_range("Called pop on empty stack.");
    }
    size_--;
}

template<typename T>
void stack<T>::pop_two() {
    if (empty()) { //edge case: stack is empty
        throw std::out_of_range("Called pop_two on empty stack.");
    }
    if (size_ == 1) { //edge case: only one item in stack
        throw std::out_of_range("Called pop_two on a stack of size 1."); 
    }
    size_ -= 2;
}

template<typename T>
T& stack<T>::top() const {
    if (empty()) { //edge case: stack is empty
        throw std::underflow_error("Called top on empty stack.");
    }
    return data_[size_ - 1]; //returns last element of array
}
