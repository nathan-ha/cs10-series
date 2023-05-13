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

//helps destructor
void Tree::burnTree(Node *root)
{
    if (root == nullptr) return;
    //explore every subtree and delete them starting from the ends
    burnTree(root->left);
    burnTree(root->middle);
    burnTree(root->right);
    delete root;
    root = nullptr;
}

//inserts node and maintains 2-3 tree properties
void Tree::insert(const string &newKey)
{
    //edge case: empty tree
    if (root_ == nullptr)
    {
        root_ = new Node(newKey, "");
        return;
    }

    //look for leaf node where key belongs
    Node *targetNode = root_;
    bool isLeaf = targetNode->left == nullptr && targetNode->middle == nullptr && targetNode->right == nullptr;
    while (!isLeaf)
    {
        if (newKey < targetNode->small)
        {
            targetNode = targetNode->left;
        }
        else if (targetNode->large < newKey)
        {
            targetNode = targetNode->right;
        }
        else
        {
            targetNode = targetNode->middle;
        }
        isLeaf = targetNode->left == nullptr && targetNode->middle == nullptr && targetNode->right == nullptr;
    }

    /* case 1: leaf has room for new key */
    if (targetNode->large == "") //if a node has one key, the key will sit in the small part
    {
        targetNode->addKey(newKey);
        return;
    }
    
    /* case 2: no room in leaf */
    string midKey = prepMidKey(targetNode, newKey); //middle key will be "tossed" up into the parent
    while (true)
    {
        //edge case: target node is the root (aka parent is null)
        if (targetNode == root_)
        {
            root_ = new Node(midKey, "");
            //split the target node into a left and right child for the new root
            root_->left = targetNode;
            root_->right = new Node(targetNode->large, "");
            targetNode->large = "";
            return;
        }
        //case 2.1: parent has space for another key
        Node *parent = targetNode->parent;
        if (parent->large == "")
        {
            parent->addKey(midKey);
            //split the node
            //case 2.1.1: need to split the left child of parent
            if (parent->left = targetNode)
            {
                parent->middle = new Node(targetNode->large, "");
                targetNode->large = "";

            }
            //case 2.1.2: need to split the right child of parent
            else
            {
                parent->middle = new Node(targetNode->small, "");
                targetNode->small = targetNode->large; //shift large key to small spot
                targetNode->large = "";
            }
            return;
        }
        midKey = prepMidKey(targetNode, midKey);
        targetNode = parent;
    }


}

//finds the middle key between the two in the node, and another key
//will also edit the node to replace the middle key with the inputted key (if needed)
const string &Tree::prepMidKey(Node *root, const string &key)
{
    if (root->small == "" || root->large == "")
    {
        throw runtime_error("Tree::findMidKey(): tried to find middle key with a non-full node");
    }
    if (key < root->small)
    {
        string midKey = root->small;
        root->small = key;
        return midKey;
    }
    if (root->large < key)
    {
        string midKey = root->large;
        root->large = key;
        return midKey;
    }
    return key;
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
    if (root == nullptr) return;

    bool isLeaf = (root->left == nullptr) && (root->middle == nullptr) && (root->right == nullptr);
    bool is2Node = (root->left == nullptr) && (root->middle != nullptr) && (root->right == nullptr);
    if (isLeaf)
    {
        cout << root->small << ", ";
        return;
    }
    if (is2Node)
    {
        inOrder(root->left);
        cout << root->small << ", ";
        inOrder(root->right);
        return;
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
    Node *currNode = root_;
    while (currNode != nullptr)
    {
        //if target is found
        if (currNode->small == target || currNode->large == target)
        {
            return true;
        }
        //otherwise, keep going through tree
        if (target < currNode->small)
        {
            currNode = currNode->left;
        }
        else if (currNode->large < target)
        {
            currNode = currNode->right;
        }
        else
        {
            currNode = currNode->middle;
        }
    }
    return false;
}
