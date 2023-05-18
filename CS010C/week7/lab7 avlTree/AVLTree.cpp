#include <iostream>
#include <fstream>
#include <stdexcept>

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
        else if (newKey == curr->data)
        {
            curr->count++;
            return;
        }
    }
}

//Returns the balance factor of a given node.
int AVLTree::balanceFactor(Node *curr) const
{
    return height(curr->left) - height(curr->right); //balance factor is (left subtree height) - (right subtree height)
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

//rotates subtree when subtree becomes left-heavy after insertion (left-left rotation)
//actually does a right rotation
//returns new root of subtree
Node *AVLTree::rotateLL(Node *curr)
{
    //edge case: rotating root
    if (curr == root_)
    {
        root_ = root_->left; //set new root
        root_->parent = nullptr;
    }
    //otherwise rotate right normally
    else
    {
        Node *parent = curr->parent;
        parent->left = curr->left;
        parent->left->parent = parent; //fixes parent pointer
    }
    //connect the rest of the nodes
    Node *parent = curr->parent;
    Node *leftChild = curr->left;
    Node *leftLeftChild = leftChild->left;
    leftChild->right = curr;
    leftChild->left = leftLeftChild;
    //fix parent pointers
    leftChild->parent = parent;
    curr->parent = leftChild;
    //fix child pointers (they will always be leaves)
    leftLeftChild->left = nullptr;
    leftLeftChild->right = nullptr;
    curr->left = nullptr;
    curr->right = nullptr;
    return leftChild; //left child is the new subroot
}

//rotates subtree when subtree becomes right-heavy after insertion (right-right rotation)
//actually does a left rotation
//returns new root of subtree
Node *AVLTree::rotateRR(Node *curr)
{
    //edge case: rotating root
    if (curr == root_)
    {
        root_ = root_->right; //set new root
        root_->parent = nullptr;
    }
    //otherwise rotate left normally
    else
    {
        Node *parent = curr->parent;
        parent->right = curr->right;
        parent->right->parent = parent; //fixes parent pointer
    }
    //connect the rest of the nodes
    Node *parent = curr->parent;
    Node *rightChild = curr->right;
    Node *rightRightChild = rightChild->right;
    rightChild->left = curr;
    rightChild->right = rightRightChild;
    //fix parent pointers
    rightChild->parent = parent;
    curr->parent = rightChild;
    //fix child pointers (they will always be leaves)
    rightRightChild->left = nullptr;
    rightRightChild->right = nullptr;
    curr->left = nullptr;
    curr->right = nullptr;
    return rightChild; //left child is the new subroot
}

//Rotate the subtree to right at the given node and returns the new subroot.
Node *AVLTree::rotateRight(Node *curr)
{
    throw runtime_error("make rotateRight()");
}

//returns the height of a node from the bottom of the tree
int AVLTree::height(Node *curr) const
{
    if (curr == nullptr)
    {
        return -1;
    }
    // go left and right
    int leftHeight = height(curr->left);
    int rightHeight = height(curr->right);
    // return the max between the two heights
    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    return rightHeight + 1;
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