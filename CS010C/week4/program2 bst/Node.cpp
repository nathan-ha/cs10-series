#include "Node.h"
#include <stdexcept>

Node::Node(const std::string& data): 
    data_(data), 
    count_(0),
    left_(nullptr), 
    right_(nullptr) 
{}

void Node::setLeft(Node* newLeft) {
    left_ = newLeft;
}

void Node::setRight(Node* newRight) {
    right_ = newRight;
}

void Node::setData(const std::string& newData) {
    data_ = newData;
}

Node* Node::getLeft() const {
    return left_;
}

Node* Node::getRight() const {
    return right_;
}

const std::string& Node::getData() const {
    return data_;
}

void Node::incrementCount() {
    ++count_;
}

void Node::decrementCount() {
    if (count_ == 0) {
        throw std::logic_error("called decrementCount() on Node with count_=0");
    }
    --count_;
}

int Node::getCount() const {
    return count_;
}

void Node::setCount(int newCount) {
    count_ = newCount;
}