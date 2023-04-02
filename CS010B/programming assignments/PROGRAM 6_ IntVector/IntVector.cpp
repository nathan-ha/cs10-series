#include "IntVector.h"
#include <stdexcept>
#include <iostream>

IntVector::IntVector(unsigned capacity, int value) {

    _capacity = capacity;
    _size = capacity;
    _data = nullptr;

    //only make the array and stuff if the vector is not empty
    if (capacity > 0) {

        _data = new int[_capacity];

        //fill the array with the second parameter's value
        for (unsigned i = 0; i < _size; i++) {
            _data[i] = value;
        }
    }
};

IntVector::~IntVector() {
    delete[] _data;
    _data = nullptr; //removes dangling pointer
}

unsigned IntVector::size() const {
    return _size;
}

unsigned IntVector::capacity() const {
    return _capacity;
}

bool IntVector::empty() const {
    return _size == 0;
}

const int & IntVector::at(unsigned index) const {
    if (index > _size - 1 || _size == 0) {
        throw std::out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

int & IntVector::at(unsigned index) {
    if (index > _size - 1 || _size == 0) {
        throw std::out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

const int & IntVector::front() const {
    return _data[0];
}

int & IntVector::front() {
    return _data[0];
}

const int & IntVector::back() const {
    return _data[_size - 1];
}

int & IntVector::back() {
    return _data[_size - 1];
}

void IntVector::expand() { //TODO: find out if this is doesn't cause memory leaks
     int* newData = nullptr;

    if (_capacity == 0) {
        newData = new int[1];
        _capacity = 1;
    }
    else {
        newData = new int[_capacity * 2];
        _capacity *= 2;
    }

    //copies old array to new one
    for (unsigned int i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }

    //delete contents of array and point pointer to new array
    delete[] _data;
    _data = newData;
    newData = nullptr; //prevent dangling pointer
}

void IntVector::expand(unsigned amount) {
    int* newData = new int[_capacity + amount];
    
    for (unsigned int i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }

    _capacity += amount;
    delete[] _data;
    _data = newData;
    newData = nullptr;
}

void IntVector::insert(unsigned index, int value) {
    if (index > _size) {
        throw std::out_of_range("IntVector::insert_range_check"); //TODO: figure this out
    }

    if (_size + 1 > _capacity) {
        expand();
    }

    //shift array right
    for (unsigned int i = index; i < _size; i++) {
        _data[i + 1] = _data[i]; 
    }

    _data[index] = value;
    _size++;
}

void IntVector::erase(unsigned index) {
    if (index > _size - 1 || _size == 0) {
        throw std::out_of_range("IntVector::erase_range_check");
    }

    //shift array left and overwrite unwanted value
    for (unsigned int i = index; i < _size; i++) {
        _data[i] = _data[i + 1];
    }

    _size--;
}

void IntVector::push_back(int value) {
    if (_size + 1 > _capacity) {
        expand();
    }
    _data[_size] = value;
    _size++;
}

void IntVector::pop_back() {
    _size--;
}

void IntVector::clear() {  
    _size = 0;
}

void IntVector::resize(unsigned size, int value) {
    if (size <= _size) {
        _size = size;
    }
    else {
        if (size > _capacity * 2) { //resize to double the old capacity unless the new capacity should be bigger than that
            expand(size - _capacity);
        }
        else if (size > _capacity) {
            expand();
        }

        for (unsigned int i = _size; i < _capacity; i++) {
            _data[i] = value;
        }

        _size = size;
    }
}

void IntVector::reserve(unsigned n) {
    if (n > _capacity) {
        expand(n - _capacity); //sets the capacity to at least n
    }
}

void IntVector::assign(unsigned n, int value) {
    
    if (n > _capacity * 2) {
        expand(n - _capacity);
    }
    else if (n > _capacity) {
        expand();
    }
    _size = n;

    //overwrite old elements
    for (unsigned int i = 0; i < _size; i++) {
        _data[i] = value;
    }
}












