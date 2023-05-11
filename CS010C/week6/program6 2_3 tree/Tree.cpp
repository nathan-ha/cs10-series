#include <stdexcept>
#include <iostream>
using namespace std;

#include "Tree.h"

Tree::Tree()
    : root_(nullptr)
{
}

Tree::~Tree()
{
    burnTree(root_);
    root_ = nullptr;
}

void Tree::burnTree(Node* root)
{
    if (root == nullptr) return;
    //explore every subtree and delete them starting from the ends
    burnTree(root->left);
    burnTree(root->middle);
    burnTree(root->right);
    delete root;
    root = nullptr;
}

void Tree::insert(const string &newString)
{
    //edge case: empty tree
    if (root_ == nullptr)
    {
        root_ = new Node(newString, "");
        return;
    }
    insert(newString, root_);
}

void Tree::insert(const string &newString, Node *root) 
{
    //find leaf node where new string belongs
    bool isLeaf = root->left == nullptr && root->middle == nullptr && root->right == nullptr;
    while (!isLeaf)
    {
        //go left
        if (newString < root->small)
        {
            root = root->left;
        }
        //go middle
        else if (root->small < newString && newString < root->large)
        {
            root = root->middle;
        }
        //go right
        else if (root->large < newString)
        {
            root = root->right;
        }
        //new string equals one of the keys
        else
        {
            throw runtime_error("insert(): tried inserting a duplicate");
        }
        isLeaf = root->left == nullptr && root->middle == nullptr && root->right == nullptr;
    }

    //case 1: insert to node with one element
    bool hasOneKey = (root->small != "" && root->large != ""); //nodes with one key only have a small key
    if (hasOneKey)
    {
        //new string is smaller than key
        if (newString <  root->small)
        {
            root->large = root->small;
            root->small = newString;
            return;
        }
        //new string is larger than key
        else if (newString > root->small)
        {
            root->large = newString;
            return;
        }
        throw runtime_error("insert(): failed to insert to leaf with one key");
    }
    //case 2: insert to node with two keys
    //find middle key between newString, small, and large
    string middleKey;
    //newString is middle
    if (root->small < newString && newString < root->large)
    {
        middleKey = newString;
    }
    else if (newString < root->small)
    {
        middleKey = root->small;
        root->small = newString; //small will be lifted
    }
    else if (root->large < newString)
    {
        middleKey = root->large;
        root->large = newString; //large will be lifted
    }
    else
    {
        throw runtime_error("insert(): failed to lift key");
    }
    split(middleKey, root);
}

void Tree::split(const string &key, Node *root)
{
    //lift middle key into parent
    //keep lifting nodes until all lifted keys are in the tree
    //if parent is full, repeat process for parent
    //if root is full, make new root node

    //base case: lifting out of big root
    if (root->parent == nullptr)
    {
        //what the fuck am i doing HELP
    }

    bool parentIsFull = (root->parent->small != "") && (root->parent->large != "");
    if (parentIsFull)
    {
        string middleKey;
        //key is middle
        if (root->small < key && key < root->large)
        {
            middleKey = key;
        }
        else if (key < root->small)
        {
            middleKey = root->small;
            root->small = key; //small will be lifted
        }
        else if (root->large < key)
        {
            middleKey = root->large;
            root->large = key; //large will be lifted
        }
        else
        {
            throw runtime_error("insert(): failed to lift key");
        }
        split(middleKey, root->parent);
    }
}

void Tree::preOrder() const
{
    throw runtime_error("create preOrder()");
}

void Tree::preOrder(Node *root) const
{
    
}

void Tree::inOrder() const
{
    inOrder(root_);
    cout << endl;
}

void Tree::inOrder(Node *root) const
{
    bool isLeaf = root->numChildren() == 0;
    bool is2Node = root->numChildren() == 2;
    if (isLeaf)
    {
        root->print();
        return;
    }
    if (is2Node)
    {
        inOrder(root->left);
        cout << root->small << ", ";
        inOrder(root->right);
    }
    //else: node is a 3-node
    inOrder(root->left);
    cout << root->small << ", ";
    inOrder(root->middle);
    cout << root->large << ", ";
    inOrder(root->right);
}

void Tree::postOrder() const
{
    throw runtime_error("create postOrder");
}
void Tree::remove(const string &target)
{
    throw runtime_error("create remove()");
}
bool Tree::search(const string &target) const
{
    throw runtime_error("create search()");
}
