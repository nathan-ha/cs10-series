#include "BSTree.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <stdexcept>

BSTree::BSTree(): root_(nullptr) {}

//TODO: do destructor
BSTree::~BSTree() {
    burnTree(root_);
    root_ = nullptr;
}

// recursively traverses the tree and deletes everything
void BSTree::burnTree(Node* currNode) {
    if (currNode == nullptr) return; //stop when end of path is reached
    burnTree(currNode->getLeft());
    burnTree(currNode->getRight());
    delete currNode;
}

void BSTree::print(const Node* currNode) const {
    if (currNode == nullptr) {
        return;
    }
    std::cout << '\"' << currNode->getData() << '\"' << " count: " << currNode->getCount() << "; ";
    //recursively traverses the tree starting from the left (smallest) to right (biggest)
    print(currNode->getLeft());
    print(currNode->getRight());
}

void BSTree::print() const {
    if (root_ == nullptr) {
        throw std::runtime_error("called print() on empty tree");
    }
    print(root_);
    std::cout << '\n';
}

void BSTree::insert(Node* prevNode, Node* currNode, const std::string& newString) {
    if (currNode == nullptr) { //base case: found where the new node should be
        //add the node
        currNode = new Node(newString);
        currNode->incrementCount();
        //connect the node to the parent
        if (newString < prevNode->getData()) {
            prevNode->setLeft(currNode);
            return;
        }
        prevNode->setRight(currNode);
        return;
    }
    //TODO: should i compare strings like this?
    if (newString < currNode->getData()) {
        insert(currNode, currNode->getLeft(), newString);
        return;
    }
    if (newString > currNode->getData()) {
        insert(currNode, currNode->getRight(), newString);
        return;
    }
    //if this line is reached, then the node is duplicate (we don't want those)
    currNode->incrementCount(); //increment count without adding a new node
}

void BSTree::insert(const std::string& newString) {
    if (root_ == nullptr) { //edge case: empty tree
        root_ = new Node(newString);
        root_->incrementCount();
        return;
    }
    insert(nullptr, root_, newString);
}

bool BSTree::search(Node* currNode, const std::string& target) const {
    if (currNode == nullptr) { //if null is reached, then the target was never found on that path
        return false;
    } 
    if (currNode->getData() == target) {
        return true;
    }
    //traverse tree
    if (target < currNode->getData()) {
        return search(currNode->getLeft(), target) || false; //we only need one true in this recursive chain to return true overall
    }
    return search(currNode->getRight(), target) || false;
}


bool BSTree::search(const std::string& target) const {
    if (root_ == nullptr) {
        throw std::runtime_error("called search() on empty list");
    }
    return search(root_, target);
}
