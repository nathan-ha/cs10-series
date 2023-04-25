#include "Node.h"
#include <stdexcept>

Node::Node(const std::string& data): data(data), left(nullptr), right(nullptr), count(0) {}

void Node::setLeft(Node* newLeft) {
    left = newLeft;
}

void Node::setRight(Node* newRight) {
    right = newRight;
}

void Node::setData(const std::string& newData) {
    data = newData;
}

Node* Node::getLeft() const {
    return left;
}

Node* Node::getRight() const {
    return right;
}

const std::string& Node::getData() const {
    return data;
}

void Node::incrementCount() {
    count++;
}

void Node::decrementCount() {
    if (count == 0) {
        throw std::logic_error("called DecrementCount() on Node with count=0");
    }
    count--;
}

int Node::getCount() const {
    return count;
}