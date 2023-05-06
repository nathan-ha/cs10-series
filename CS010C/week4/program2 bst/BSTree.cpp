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
        return "";
    }
    //go as far right through the tree as possible to find max value
    Node* currNode = root_;
    while (currNode->getRight() != nullptr) {
        currNode = currNode->getRight();
    }
    return currNode->getData();
}

int BSTree::height(Node* root) const {
    if (root == nullptr) {
        return -1;
    }
    //search for largest path starting from root
    int leftHeight = height(root->getLeft());
    int rightHeight = height(root->getRight());
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

int BSTree::height(const std::string& target) const {
    //search for target node
    Node* currNode = root_;
    while (currNode != nullptr) {
        if (currNode->getData() == target) {
            break;
        }
        if (target < currNode->getData()) {
            currNode = currNode->getLeft();
        } else {
            currNode = currNode->getRight();
        }
    }
    //find height starting from curr
    return height(currNode);
}

void BSTree::remove(const std::string& target) {
    Node* parentNode = nullptr;
    Node* targetNode = root_;
    //search for node
    while (targetNode != nullptr) {
        //node found
        if (targetNode->getData() == target) {
            //case 1: target count >1
            if (targetNode->getCount() > 1) {
                targetNode->decrementCount();
                return;
            }
            //case 2: target is leaf (no children)
            bool isLeaf = targetNode->getLeft() == nullptr && targetNode->getRight() == nullptr;
            if (isLeaf) {
                if (targetNode == root_) { //only one node in tree
                    root_ = nullptr;
                } else if (parentNode->getLeft() == targetNode) { //removing as left child
                    parentNode->setLeft(nullptr);
                } else { //removing as right child
                    parentNode->setRight(nullptr);
                }
                delete targetNode;
                return;
            }            
            //if the target has a left child
            if (targetNode->getLeft() != nullptr) {
                //find largest val of left subtree to find replacement
                Node* replacement = targetNode->getLeft();
                while (replacement->getRight() != nullptr) {
                    replacement = replacement->getRight();
                }
                //replace target's data
                Node replacementCopy = *replacement;
                replacement->setCount(1);
                remove(replacement->getData()); //nothing is leaked since this will be called recursively until leaf is reached
                targetNode->setData(replacementCopy.getData());
                targetNode->setCount(replacementCopy.getCount());
                return;
            }
            //if target has right child
            if (targetNode->getRight() != nullptr) {
                //find smallest val of right subtree
                Node* replacement = targetNode->getRight();
                while (replacement->getLeft() != nullptr) {
                    replacement = replacement->getLeft();
                }
                //replace data
                Node replacementCopy = *replacement;
                replacement->setCount(1);
                remove(replacement->getData());
                targetNode->setData(replacementCopy.getData());
                targetNode->setCount(replacementCopy.getCount());
                return;
            }
        }
        //continue to search for node
        parentNode = targetNode;
        if (target < targetNode->getData()) {
            targetNode = targetNode->getLeft();
        } else {
            targetNode = targetNode->getRight();
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
        std::cout << std::endl;
        return;
    }
    postOrder(root_);
    std::cout << std::endl;
}