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

// recursively traverses the tree and deletes everything starting from smallest values
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

void BSTree::insert(Node* prevNode, Node* currNode, const std::string& newString) {
    //edge case with empty tree is handled in other insert()
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

void BSTree::smallest(Node* currNode, Node*& minNode) const {
    //go as far left through the tree as possible to find min value
    if (currNode->getLeft() == nullptr) {
        minNode = currNode;
        return;
    }
    smallest(currNode->getLeft(), minNode);
}

const std::string& BSTree::smallest() const {
    if (root_ == nullptr) {
        throw std::runtime_error("called smallest() on empty list");
    }
    //look for smallest val and save it to smallestNode
    Node* smallestNode;
    smallest(root_, smallestNode);
    return smallestNode->getData();
}

//same logic as smallest()
void BSTree::largest(Node* currNode, Node*& maxNode) const {
    //go as far right through the tree as possible to find max value
    if (currNode->getRight() == nullptr) {
        maxNode = currNode;
        return;
    }
    largest(currNode->getRight(), maxNode);
}

const std::string& BSTree::largest() const {
    if (root_ == nullptr) {
        throw std::runtime_error("called largest() on empty list");
    }
    Node* largestNode;
    largest(root_, largestNode);
    return largestNode->getData();
}

int BSTree::height(const std::string& target, Node* currNode, int currHeight) const {
    if (currNode == nullptr) { //base case: end of path is reached with no target found
        return -1;
    }
    if (currNode->getData() == target) { //base case: target found
        return currHeight;
    }
    //search through left and right subtrees until node is found or end is reached, increasing currHeight with each call
    int leftSubTreeHeight = height(target, currNode->getLeft(), currHeight + 1);
    if (leftSubTreeHeight != -1) { //don't return height if nothing was found
        return leftSubTreeHeight;
    }
    int rightSubTreeHeight = height(target, currNode->getRight(), currHeight + 1);
    if (rightSubTreeHeight != -1) {
        return rightSubTreeHeight;
    }
    return -1;
}


int BSTree::height(const std::string& target) const {
    if (root_ == nullptr) {
        throw std::runtime_error("height() called on empty tree");
    }
    int tempHeight = 0; //i know temp is a bad name but this variable doesn't do anything but help the overload
    int heightOfTree = height(target, root_, tempHeight);
    if (heightOfTree == -1) {
        throw std::runtime_error("height(): target not found");
    }
    return heightOfTree;
}

Node* BSTree::getFarRightNode(Node* currNode) const {
    if (currNode == nullptr) {
        throw std::runtime_error("called getFarRightNode() with nullptr");
    }
    if (currNode->getRight() == nullptr) {
        return currNode;
    }
    return getFarRightNode(currNode->getRight());
}

Node* BSTree::getFarLeftNode(Node* currNode) const {
    if (currNode == nullptr) {
        throw std::runtime_error("called getFarLeftNode() with nullptr");
    }
    if (currNode->getLeft() == nullptr) {
        return currNode;
    }
    return getFarLeftNode(currNode->getLeft());
}

Node* BSTree::findReplacement(Node* currNode) const {
    //replacement node will be the farthest left (right) node of right (left) subtree
    if (currNode == nullptr) {
        throw std::runtime_error("called findReplacement() on nullptr");
    }
    if (currNode->getLeft() != nullptr) { //edge case: node only has one child
        return getFarRightNode(currNode->getLeft());
    } 
    //TODO: figure out seg faults
    return getFarLeftNode(currNode->getRight());
}

void BSTree::remove(const std::string& target, Node* currNode, Node* prevNode) {
    if (currNode == nullptr) { //base case: end of path reached
        return;
    }
    if (currNode->getData() == target) { //base case: node found
        if (currNode->getCount() > 1) { //don't remove node if count is more than one
            currNode->decrementCount();
            return;
        }
        bool isLeaf = currNode->getLeft() == nullptr && currNode->getRight() == nullptr;
        if (isLeaf) { //edge case: (only) remove leaf
            delete currNode;
            return;
        }
        //replace target and delete it
        Node* replacement = findReplacement(currNode);
        //connect replacement node to the currNode's children
        replacement->setLeft(currNode->getLeft());
        replacement->setRight(currNode->getRight());
        delete currNode;
        //connect parent to replacement
        if (prevNode == nullptr) { //no parents if removing root
            return;
        }
        if (target < prevNode->getData()) {
            prevNode->setLeft(replacement);
        } else {
            prevNode->setRight(replacement);
        }
        return;
    }
    //search rest of tree
    remove(target, currNode->getLeft(), currNode);
    remove(target, currNode->getRight(), currNode);
}



void BSTree::remove(const std::string& target) {
    if (root_ == nullptr) { //edge case: empty tree
        throw std::runtime_error("called remove() on empty tree");
    }
    if (target == root_->getData()) {

    }
    remove(target, root_, nullptr);
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
