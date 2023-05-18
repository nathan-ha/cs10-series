#include <iostream>

using namespace std;

#include "AVLTree.h"

AVLTree::AVLTree()
    : root_(nullptr)
{
}

//Insert an item to the binary search tree and perform rotation if necessary.
void AVLTree::insert(const string &newKey)
{
    #include <stdexcept>
    throw std::runtime_error("create insert()");
}

//Returns the balance factor of a given node.
int AVLTree::balanceFactor(Node *) const
{
    #include <stdexcept>
    throw std::runtime_error("create balanceFactor()");
}

//Traverse and print the tree in inorder notation. 
//Print the string followed by its balance factor in parentheses followed by a , and one space.
void AVLTree::printBalanceFactors() const
{
    #include <stdexcept>
    throw std::runtime_error("create printBalanceFactors()");
}

//Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
Node *AVLTree::findUnbalancedNode(Node *curr)
{
    #include <stdexcept>
    throw std::runtime_error("create findUnbalancedNode()");
}

//Implement four possible imbalance cases and update the parent of the given node.
void AVLTree::rotate(Node *curr)
{
    #include <stdexcept>
    throw std::runtime_error("create rotate()");
}

//Rotate the subtree to left at the given node and returns the new subroot.
Node *AVLTree::rotateLeft(Node *curr)
{
    #include <stdexcept>
    throw std::runtime_error("create rotateLeft()");
}

//Rotate the subtree to right at the given node and returns the new subroot.
Node *AVLTree::rotateRight(Node *curr)
{
    #include <stdexcept>
    throw std::runtime_error("create rotateRight()");
}

void AVLTree::printBalanceFactors(Node *curr)
{
    #include <stdexcept>
    throw std::runtime_error("create printBalanceFactors()");
}