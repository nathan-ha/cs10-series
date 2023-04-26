#pragma once
#include <stdexcept>
#include <iostream>

template <typename T>
class queue_array {
    private:
        T* data_;
        int front_;
        int back_;
        int capacity_;
    public:
        queue_array(int capacity = 1);
        ~queue_array();
        void push(T& input);
        void pop();
        bool empty() const;
        void print() const;
};


template <typename T>
queue_array<T>::queue_array(int capacity): 
    data_(new T[capacity]), 
    front_(-1), 
    back_(-1), 
    capacity_(capacity) 
{}

template <typename T>
queue_array<T>::~queue_array() {
    delete[] data_;
    data_ = nullptr;
}

template <typename T>
bool queue_array<T>::empty() const {
    return front_ == -1 and back_ == -1;
}

template <typename T>
void queue_array<T>::push(T& input) {
    if (empty()) {
        data_[0] = input;
        front_ = 0;
        back_ = 0;
        return;
    }

    bool isFull = ((back_ + 1) % capacity_) == front_; //array is full when the element after back_ is front_
    if (isFull) {
        throw std::out_of_range("shits full (push)");
    }

    back_ = (back_ + 1) % capacity_; //move back_ up one
    data_[back_] = input;
}

template <typename T>
void queue_array<T>::pop() {
    if (empty()) {
        throw std::out_of_range("shits empty (pop)");
    }
    if (front_ == back_) { //make queue "empty" if last element is popped
        front_ = -1;
        back_ = -1;
        return;
    }
    front_ = (front_ + 1) % capacity_;
}

template <typename T>
void queue_array<T>::print() const {
    if (empty()) {
        throw std::out_of_range("can't print empty list, idiot");
    }
    for (int i = front_; i <= back_; i++) {
        std::cout << data_[i] << ' ';
    }
    std::cout << '\n';
}