#include "IntVector.h"
#include <stdexcept>
#include <iostream>

IntVector::IntVector(unsigned capacity, int value) {

    _capacity = capacity;
    _size = capacity;

    //only make the array and stuff if the vector is not empty
    if (capacity > 0) {

        _data = new int[_capacity];

        //fill the array with the second parameter's value
        for (unsigned i = 0; i < _size; i++) {
            _data[i] = value;
        }

    }
    else {
        _data = nullptr;
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
    // std::cout << "test size " << _size << std::endl;
    // std::cout << "test index " << index << std::endl;
    if (index > _size - 1 || _size == 0) {
        throw std::out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

const int & IntVector::front() const {
    return _data[0];
}

const int & IntVector::back() const {
    return _data[_size - 1];
}



