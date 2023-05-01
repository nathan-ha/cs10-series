#include "BSTree.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <stdexcept>

BSTree::BSTree(): root_(nullptr) {}

BSTree::~BSTree() {
    burn(root_);
    root_ = nullptr;
}

// recursively traverses the tree and deletes everything
void BSTree::burn(Node* currNode) {
    if (currNode == nullptr) return; //stop when end of path is reached
    burn(currNode->getLeft());
    burn(currNode->getRight());
    delete currNode;
}

void BSTree::insert(const std::string& newString) {
    if (root_ == nullptr) { //edge case: empty tree
        root_ = new Node(newString);
        root_->incrementCount();
        return;
    }
    Node* parentNode = nullptr;
    Node* currNode = root_;
    //traverse tree until nullptr is reached since new nodes are inserted as leaves
    while (currNode != nullptr) {
        if (newString == currNode->getData()) { //case 1: duplicate is inserted (don't actually insert the node)
            currNode->incrementCount();
            return;
        }
        //traverse tree (like normal)
        parentNode = currNode;
        if (newString < currNode->getData()) {
            currNode = currNode->getLeft();
        } else {
            currNode = currNode->getRight();
        }
    }
    //once position is found, connect new node to tree
    Node* newLeaf = new Node(newString);
    newLeaf->incrementCount();
    if (newString < parentNode->getData()) { //insert as left child
        parentNode->setLeft(newLeaf);
        return;
    }
    parentNode->setRight(newLeaf); //insert as right child
}

bool BSTree::search(const std::string& target) const {
    if (root_ == nullptr) {
        throw std::runtime_error("called search() on empty list");
    }
    Node* currNode = root_;
    //search through list until target is found or end is reached
    while (currNode != nullptr) {
        if (currNode->getData() == target) {
            return true;
        }
        if (target < currNode->getData()) {
            currNode = currNode->getLeft();
        } else {
            currNode = currNode->getRight();
        }
    }
    return false;
}

const std::string& BSTree::smallest() const {
    if (root_ == nullptr) {
        throw std::runtime_error("called smallest() on empty list");
    }
    //go as far left through the tree as possible to find min value
    Node* currNode = root_;
    while (currNode->getLeft() != nullptr) {
        currNode = currNode->getLeft();
    }
    return currNode->getData();
}

const std::string& BSTree::largest() const {
    if (root_ == nullptr) {
        throw std::runtime_error("called largest() on empty list");
    }
    //go as far right through the tree as possible to find max value
    Node* currNode = root_;
    while (currNode->getRight() != nullptr) {
        currNode = currNode->getRight();
    }
    return currNode->getData();
}


int BSTree::height(const std::string& target) const {
    if (root_ == nullptr) {
        throw std::runtime_error("height() called on empty tree");
    }
    Node* currNode = root_;
    int height = 0;
    //traverse tree until nullptr is reached or target is found
    while (currNode != nullptr) {
        if (target == currNode->getData()) { //found target
            return height;
        }
        if (target < currNode->getData()) {
            currNode = currNode->getLeft();
        } else {
            currNode = currNode->getRight();
        }
        height++;
    }
    return -1;
}

Node* BSTree::findReplacement(Node* start) const {
    //finds the minimum node (most left) in the right subtree
    Node* currNode = start->getRight();
    if (currNode == nullptr) {
        throw std::runtime_error("findReplacement(): there is no right subtree");
    }
    while (currNode->getLeft() != nullptr) {
        currNode = currNode->getLeft();
    }
    return currNode;
}

Node* BSTree::remove(const std::string& target, Node* currNode) {
    //Note: every return in this function will represent the (new) child of (the previous) currNode
    // also the default return will be currNode since returning the current node does not change the state of the tree
    if (currNode == nullptr) return nullptr; //base case: target not found
    //traverse tree
    if (target < currNode->getData()) {
        Node* newLeftChild = remove(target, currNode->getLeft());
        currNode->setLeft(newLeftChild);
    } else if (target > currNode->getData()) {
        Node* newRightChild = remove(target, currNode->getRight());
        currNode->setRight(newRightChild);
    }
    if (target != currNode->getData()) return currNode; //have to check for this otherwise weird bug happens
    // base case: target found
    //case 0: >1 count
    if (currNode->getCount() > 1)  {
        currNode->decrementCount();
        return currNode;
    }
    //case 1: no children
    bool isLeaf = currNode->getLeft() == nullptr && currNode->getRight() == nullptr;
    if (isLeaf) {
        if (root_ == currNode) root_ = nullptr; //edge case: root is only node
        delete currNode;
        return nullptr; //curr having no children means that the curr's parent will also have a null child
    }
    //case 2: one child
    if (currNode->getLeft() == nullptr) { //case 2.1: only has right child
        Node* rightChild = currNode->getRight();
        if (root_ == currNode) root_ = rightChild; //edge case: replacing root
        delete currNode;
        //no need to connect any nodes here since that's handled by the recursive call
        return rightChild; //assign the parent with the new child
    }
    if (currNode->getRight() == nullptr) { //case 2.2: only has left child
        Node* leftChild = currNode->getLeft();
        if (root_ == currNode) root_ = leftChild; //edge case: replacing root
        delete currNode;
        return leftChild;
    }
    //general case: two children
    Node* replacement = findReplacement(currNode); //a suitable replacement for a node would be the leftmost node in the right subtree
    currNode->setData(replacement->getData()); //replace target data with the replacement's data
    currNode->setCount(replacement->getCount());
    Node* newRightChild = remove(replacement->getData(), currNode->getRight()); //remove replacement (effectively swapping it with the target)
    currNode->setRight(newRightChild);
    return currNode;
}

void BSTree::remove(const std::string& target) {
    if (root_ == nullptr) { //edge case: empty tree
        throw std::runtime_error("called remove() on empty tree");
    }
    remove(target, root_);
}


//print node, then visit left child, then visit right
void BSTree::preOrder(Node* currNode) const {
    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }
    std::cout << currNode->getData() << "(" << currNode->getCount() << "), ";
    preOrder(currNode->getLeft());
    preOrder(currNode->getRight());

}

void BSTree::preOrder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("preOrder() called on empty tree");
    }
    preOrder(root_);
    std::cout << '\n';
}

//visit left child, print node, then visit right
void BSTree::inOrder(Node* currNode) const {
    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }
    inOrder(currNode->getLeft());
    std::cout << currNode->getData() << "(" << currNode->getCount() << "), ";
    inOrder(currNode->getRight());
}

void BSTree::inOrder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("inOrder() called on empty tree");
    }
    inOrder(root_);
    std::cout << '\n';
}

//visit left child, then visit right, then print node
void BSTree::postOrder(Node* currNode) const {
    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }
    postOrder(currNode->getLeft());
    postOrder(currNode->getRight());
    std::cout << currNode->getData() << "(" << currNode->getCount() << "), ";

}

void BSTree::postOrder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("postOrder() called on empty tree");
    }
    postOrder(root_);
    std::cout << '\n';
}