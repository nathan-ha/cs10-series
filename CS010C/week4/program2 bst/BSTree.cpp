#include "BSTree.h"
#include "Node.h"
#include <string>

BSTree::BSTree(): root(nullptr) {}

//TODO: do destructor
BSTree::~BSTree() {

}

void BSTree::insert(Node* currNode, const std::string& newString) {
    if (currNode == nullptr) { //base case: found where the new node should be
        //add the node
        currNode = new Node(newString);
        currNode->incrementCount();
        return;
    }
    //TODO: should i compare strings like this?
    if (currNode->getData() < newString) {
        insert(currNode->getLeft(), newString);
        return; //returning here so the other conditions aren't evaulated
    }
    if (currNode->getData() > newString) {
        insert(currNode->getRight(), newString);
        return;
    }
    //if the code reaches here, then the node is duplicate (we don't want those)
    currNode->incrementCount(); //increment count without adding a new node
}

void BSTree::insert(const std::string& newString) {
    if (root == nullptr) { //edge case: empty tree
        root = new Node(newString);
    }
    insert(root, newString);
}
