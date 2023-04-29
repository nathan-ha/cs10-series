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

//recursively traverses the tree and prints everything out
void BSTree::print(const Node* currNode) const {
    if (currNode == nullptr) {
        return;
    }
    //traverse left subtrees and then right subtrees
    std::cout << '\"' << currNode->getData() << "\"(" << currNode->getCount() << ") ";
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

void BSTree::insert(const std::string& newString) {
    if (root_ == nullptr) { //edge case: empty tree
        root_ = new Node(newString);
        root_->incrementCount();
        return;
    }
    // insert(nullptr, root_, newString);
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

/*
Process:
    if the node has a left child, the replacement will be the largest value in the left subtree
    else, the replacement will be the smallest value of the right subtree
*/
Node* BSTree::findReplacement(Node* start, Node*& parent) const {
    if (start->getLeft() != nullptr) {
        Node* currNode = start->getLeft();
        while (currNode->getRight() != nullptr) {
            parent = currNode;
            currNode = currNode->getRight();
        }
        return currNode;
    }
    if (start->getRight() != nullptr) {
        Node* currNode = start->getRight();
        while (currNode->getRight() != nullptr) {
            parent = currNode;
            currNode = currNode->getRight();
        }
        return currNode;
    }
    return nullptr; //if this is reached, then the original node is a leaf
}

void BSTree::remove(const std::string& target, Node* currNode, Node* prevNode) {
    if (currNode->getCount() > 1) { //base case: removing a node with a non-one count
        currNode->decrementCount();
        return;
    }

    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }

    if (currNode->getData() != target) {
        if (target < currNode->getData()) {
            remove(target, currNode->getLeft(), currNode);
        } else {
            remove(target, currNode->getRight(), currNode);
        }
        return;
    }

    //base case: found target

    if (currNode == root_) { //edge case: removing root
        Node* replacementOldParent = nullptr;
        Node* replacement = findReplacement(root_, replacementOldParent);
        
    }
}

void BSTree::remove(const std::string& target) {
    if (root_ == nullptr) { //edge case: empty tree
        throw std::runtime_error("called remove() on empty tree");
    }
    bool rootIsLeaf = root_->getLeft() == nullptr && root_->getRight() == nullptr;
    if (rootIsLeaf && root_->getCount() == 1) { //edge case: only one node in tree
        delete root_;
        root_ = nullptr;
        return;
    }
    if (rootIsLeaf) {
        root_->decrementCount();
        return;
    }
    remove(target, root_, nullptr);
    //TODO: finish remove
}


//traverse the tree from root to left subtree to right subtree
void BSTree::preOrder(Node* currNode) const {
    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }
    bool isLeaf = currNode->getLeft() == nullptr && currNode->getRight() == nullptr;
    if (!isLeaf) {
        std::cout << currNode->getData() << "(" << currNode->getCount() << "), ";
    } else {
        std::cout << currNode->getData() << "(" << currNode->getCount() << ") ";
    }
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

//traverse the tree from left subtree to root to right subtree
void BSTree::inOrder(Node* currNode) const {
    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }
    inOrder(currNode->getLeft());
    bool isLeaf = currNode->getLeft() == nullptr && currNode->getRight() == nullptr;
    if (!isLeaf) {
        std::cout << currNode->getData() << "(" << currNode->getCount() << "), ";
    } else {
        std::cout << currNode->getData() << "(" << currNode->getCount() << ") ";
    }
    inOrder(currNode->getRight());

}

void BSTree::inOrder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("inOrder() called on empty tree");
    }
    inOrder(root_);
    std::cout << '\n';
}

//traverse the tree from left subtree to right subtree to root
void BSTree::postOrder(Node* currNode) const {
    if (currNode == nullptr) { //base case: end of path is reached
        return;
    }
    postOrder(currNode->getRight());
    postOrder(currNode->getLeft());
    bool isLeaf = currNode->getLeft() == nullptr && currNode->getRight() == nullptr;
    if (!isLeaf) {
        std::cout << currNode->getData() << "(" << currNode->getCount() << "), ";
    } else {
        std::cout << currNode->getData() << "(" << currNode->getCount() << ") ";
    }

}

void BSTree::postOrder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("postOrder() called on empty tree");
    }
    postOrder(root_);
    std::cout << '\n';
}
