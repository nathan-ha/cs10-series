#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

using namespace std;

#include "AVLTree.h"

AVLTree::AVLTree()
    : root_(nullptr)
{
}

AVLTree::~AVLTree()
{
    burnTree(root_);
    root_ = nullptr;
}

//deletes every node in the tree
void AVLTree::burnTree(Node *curr)
{
    if (curr == nullptr) return;
    //go left, go right, then delete node
    burnTree(curr->left);
    burnTree(curr->right);
    delete curr;
}

//Insert an item to the binary search tree and perform rotation if necessary.
void AVLTree::insert(const string &newKey)
{
    //case 1: empty tree
    if (root_ == nullptr)
    {
        root_ = new Node(newKey);
        return;
    }
    //insert node as leaf like a normal bst
    Node *curr = root_;
    while (curr != nullptr)
    {
        if (newKey == curr->data) return; //edge case: duplicate insertion, don't insert it
        if (newKey < curr->data)
        {
            if (curr->left == nullptr)
            {
                //inserting new node as a leaf
                curr->left = new Node(newKey);
                curr->left->parent = curr;
                break;
            }
            curr = curr->left;
        }
        else if (curr->data < newKey)
        {
            if (curr->right == nullptr)
            {
                //inserting new node as a leaf
                curr->right = new Node(newKey);
                curr->right->parent = curr;
                break;
            }
            curr = curr->right;
        }
    }
    //fix imbalance that the insertion caused
    Node *unbalancedNode = findUnbalancedNode(curr);
    if (unbalancedNode == nullptr) return;
    rotate(unbalancedNode, newKey);
}

//rotates the subtree based on the type of imbalance
//returns new root of the subtree
Node *AVLTree::rotate(Node *input, const string &key)
{
    imbalanceType rotationCase = rotateCase(input, key);
    if (rotationCase == LL)
    {
        return rotateRight(input);
    }
    if (rotationCase == RR)
    {
        return rotateLeft(input);
    }
    if (rotationCase == LR)
    {
        rotateLeft(input->left); //yields a subtree with two right children (LL)
        return rotateRight(input);
    }
    if (rotationCase == RL)
    {
        rotateRight(input->right); //yields a subtree with two right children (RR)
        return rotateLeft(input);
    }
    throw runtime_error("AVLTree::rotate(): failed to rotate subtree");
}

//returns a enum indicating the rotation that should be performed on the subtree
imbalanceType AVLTree::rotateCase(Node *input, const string &key) const
{
    int inputBalanceFactor = balanceFactor(input);
    bool leftHeavy = inputBalanceFactor > 1;
    bool rightHeavy = inputBalanceFactor < -1;
    //case 1: imbalance is on the left side
    if (leftHeavy)
    {
        //case 1a: left child with left child
        if (key < input->left->data)
        {
            return LL;
        }
        //case 1b: left child with right child
        return LR;
    }
    //case 2: imbalance is on the right side
    else if (rightHeavy)
    {
        //case 2a: right child with left child
        if (key < input->right->data)
        {
            return RL;
        }
        //case 2b: right child with right child
        return RR;
    }
    throw runtime_error("AVLTree::rotateCase(): tried to rotate balanced subtree");
}

//Returns the balance factor of a given node.
//balance factor is defined as (left subtree height) - (right subtree height)
int AVLTree::balanceFactor(Node *input) const
{
    return height(input->left) - height(input->right);
}

//Traverse and print the tree in inorder notation. 
//Print the string followed by its balance factor in parentheses followed by a , and one space.
void AVLTree::printBalanceFactors() const
{
    printBalanceFactors(root_);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *curr) const
{
    if (curr == nullptr) return; //base case: end of path is reached
    //go left, print node, and go right
    printBalanceFactors(curr->left);
    cout << curr->data << "(" << balanceFactor(curr) << "), ";
    printBalanceFactors(curr->right);
}

//Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
Node *AVLTree::findUnbalancedNode(Node *curr) const
{
    while (curr != nullptr)
    {
        if (abs(balanceFactor(curr)) > 1) return curr; //found imbalance
        curr = curr->parent;
    }
    return nullptr; //if all the nodes are balanced
}

//Rotate the subtree to left at the given node and returns the new subroot.
Node *AVLTree::rotateLeft(Node *input)
{
    Node *parent = input->parent;
    Node *newRoot = input->right; //will be the new root (of subtree)
    //edge case: rotating root
    if (parent == nullptr)
    {
        root_ = newRoot;
    }
    //case 1: input is a left child
    else if (parent->left == input)
    {
        parent->left = newRoot;
    }
    //case 2: input is a right child
    else
    {
        parent->right = newRoot;
    }
    //connect rest of nodes
    newRoot->parent = parent;
    input->parent = newRoot;
    input->right = newRoot->left;
    if (input->right != nullptr) input->right->parent = input; //newRoot may or may not have had a left child
    newRoot->left = input;
    return newRoot;
}

//Rotate the subtree to right at the given node and returns the new subroot.
Node *AVLTree::rotateRight(Node *input)
{
    Node *parent = input->parent;
    Node *newRoot = input->left;
    //edge case: rotating root
    if (parent == nullptr)
    {
        root_ = newRoot;
    }
    //case 1: input is a left child
    else if (parent->left == input)
    {
        parent->left = newRoot;
    }
    //case 2: input is a right child
    else
    {
        parent->right = newRoot;
    }
    //connect the rest of the nodes
    newRoot->parent = parent;
    input->parent = newRoot;
    input->left = newRoot->right;
    if (input->left != nullptr) input->left->parent = input; //newRoot may or may not have had a right child
    newRoot->right = input;
    return newRoot;
}

//returns the height of a node from the bottom of the tree
int AVLTree::height(Node *curr) const
{
    if (curr == nullptr) return -1; //base case: end of path reached
    int leftHeight = height(curr->left);
    int rightHeight = height(curr->right);
    return max(leftHeight, rightHeight) + 1; //return largest height between children
}

// Generates dotty file and visualize the tree using dotty program
void AVLTree::visualizeTree(const string &outputFilename) const
{
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open())
    {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root_);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream &outFS, Node *n) const
{
    if (n)
    {
        if (n->left)
        {
            visualizeTree(outFS, n->left);
            outFS << n->data << " -> " << n->left->data << ";" << endl;
        }

        if (n->right)
        {
            visualizeTree(outFS, n->right);
            outFS << n->data << " -> " << n->right->data << ";" << endl;
        }
    }
}