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
    Node* currNode = root_;
    while (currNode != nullptr) {
        if (newString == currNode->getData()) { //case 1: duplicate is inserted (don't actually insert the node)
            currNode->incrementCount();
            return;
        }
        if (newString < currNode->getData()) {
            //insert node as left child
            if (currNode->getLeft() == nullptr) {
                Node* newLeaf = new Node(newString);
                currNode->setLeft(newLeaf);
                newLeaf->incrementCount();
                return;
            }
            currNode = currNode->getLeft();
        } else {
            //insert as right child
            if (currNode->getRight() == nullptr) {
                Node* newLeaf = new Node(newString);
                currNode->setRight(newLeaf);
                newLeaf->incrementCount();
                return;
            }
            currNode = currNode->getRight();
        }
    }
}

bool BSTree::search(const std::string& target) const {
    if (root_ == nullptr) {
        // throw std::runtime_error("called search() on empty list");
        return false;
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

std::string BSTree::smallest() const {
    if (root_ == nullptr) {
        // throw std::runtime_error("called smallest() on empty list");
        return "";
    }
    //go as far left through the tree as possible to find min value
    Node* currNode = root_;
    while (currNode->getLeft() != nullptr) {
        currNode = currNode->getLeft();
    }
    return currNode->getData();
}

std::string BSTree::largest() const {
    if (root_ == nullptr) {
        // throw std::runtime_error("called largest() on empty list");
        return "";
    }
    //go as far right through the tree as possible to find max value
    Node* currNode = root_;
    while (currNode->getRight() != nullptr) {
        currNode = currNode->getRight();
    }
    return currNode->getData();
}

int BSTree::treeHeight(Node* currNode) const {
    if (currNode == nullptr) {
        return -1;
    }
    //search for largest path
    int leftHeight = treeHeight(currNode->getLeft());
    int rightHeight = treeHeight(currNode->getRight());
    //return max of the paths
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

int BSTree::height(const std::string& target) const {
    if (root_ == nullptr) {
        // throw std::runtime_error("height() called on empty tree");
        return -1;
    }
    //get height of node measuring from bottom up
    int totalHeightOfTree = treeHeight(root_);
    //search for depth of target starting from root
    Node* currNode = root_;
    int currDepth = 0;
    while (currNode != nullptr) {
        if (currNode->getData() == target) {
            return totalHeightOfTree - currDepth;
        }
        //traverse tree
        if (target < currNode->getData()) {
            currNode = currNode->getLeft();
        } else {
            currNode = currNode->getRight();
        }
        currDepth++;
    }
    return -1;
}


void BSTree::remove(const std::string& target) {
    Node* parentNode = nullptr;
    Node* currNode = root_;
    //search for node
    while (currNode != nullptr) {
        //node found
        if (currNode->getData() == target) {
            //case 0: target count >1
            if (currNode->getCount() > 1) {
                currNode->decrementCount();
                return;
            }
            //case 1: target is leaf
            bool isLeaf = currNode->getLeft() == nullptr && currNode->getRight() == nullptr;
            if (isLeaf) {

                if (currNode == root_) { //case 1.1: only one node in tree
                    root_ = nullptr;
                } else if (parentNode->getLeft() == currNode) { //case 1.2: removing as left child
                    parentNode->setLeft(nullptr);
                } else { //case 1.3: removing as right child
                    parentNode->setRight(nullptr);
                }

                delete currNode;
                return;
            }


            //case 2: target has one child
            if (currNode->getRight() == nullptr) { //case 2.1: only has left child

                if (currNode == root_) { //case 2.1.1: target is root
                    root_ = root_->getLeft();
                } else if (parentNode->getLeft() == currNode) { //case 2.1.2: removing as left child
                    parentNode->setLeft(currNode->getLeft()); //connect parent to new child
                } else { //case 2.1.3: removing as right child
                    parentNode->setRight(currNode->getRight());
                }

                delete currNode;
                return;
            }
            if (currNode->getLeft() == nullptr) { //case 2.2: only has right child

                //same logic as 2.1
                if (currNode == root_) { //case 2.2.1: target is root
                    root_ = root_->getRight();
                } else if (parentNode->getLeft() == currNode) { //case 2.2.2: removing as left child
                    parentNode->setLeft(currNode->getRight()); //connect parent to new child
                } else { //case 2.2.3: removing as right child
                    parentNode->setRight(currNode->getRight());
                }

                delete currNode;
                return;
            }

            // if the node to remove has a left child, 
            // replace the node to remove with the largest string value that is smaller than the current string to remove 
            // (i.e. find the largest value in the left subtree of the node to remove)

            // If the node has no left child, 
            // replace the node to remove with the smallest value larger than the current string to remove 
            // (i.e. find the smallest value in the right subtree of the node to remove).
            


            //TODO: this function swaps data into wrong place..I think
            //case 3: has two children
            Node* replacement = currNode->getLeft();
            while (replacement->getRight() != nullptr) {
                replacement = replacement->getRight();
            }
            //copy replacement data and delete it
            int replacementCount = replacement->getCount();
            std::string replacementData = replacement->getData();
            remove(replacementData); //replacement will either be a leaf or have one child
            //copy data over to currNode
            currNode->setData(replacementData);
            currNode->setCount(replacementCount);
            return;
        }
        //continue to search for node
        parentNode = currNode;
        if (target < currNode->getData()) {
            currNode = currNode->getLeft();
        } else {
            currNode = currNode->getRight();
        }
    }
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
        // throw std::runtime_error("preOrder() called on empty tree");
        std::cout << std::endl;
        return;
    }
    preOrder(root_);
    std::cout << std::endl;
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
        // throw std::runtime_error("inOrder() called on empty tree");
        std::cout << std::endl;
        return;
    }
    inOrder(root_);
    std::cout << std::endl;
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
        // throw std::runtime_error("postOrder() called on empty tree");
        std::cout << std::endl;
        return;
    }
    postOrder(root_);
    std::cout << std::endl;
}