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
    //root already contains the key
    else if ((newKey == root_->small) || (newKey == root_->large))
    {
        throw runtime_error("Tree::insert(): tree already contains this key");
    }

    //look for leaf node where key belongs
    Node *targetNode = root_;
    bool notLeaf = targetNode->left != nullptr || targetNode->middle != nullptr || targetNode->right != nullptr;
    while (notLeaf)
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
        if ((newKey == targetNode->small) || (newKey == targetNode->large))
        {
            throw runtime_error("Tree::insert(): tree already contains this key");
        }
        notLeaf = targetNode->left != nullptr || targetNode->middle != nullptr || targetNode->right != nullptr;
    }

    /* case 1: leaf has room for new key */
    if (targetNode->large == "") //if a node has one key, the key will sit in the small part
    {
        targetNode->addKey(newKey);
        return;
    }
    
    /* case 2: no room in leaf */
    string midKey = prepMidKey(targetNode, newKey); //middle key will be "tossed" up into the parent
    //edge case: target node is the root (aka parent is null)
    if (targetNode->parent == nullptr)
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
        if (parent->left == targetNode)
        {
            parent->middle = new Node(targetNode->large, "");
            targetNode->large = "";
        }
        //case 2.1.2: need to split the right child of parent
        else if (parent->right == targetNode)
        {
            parent->middle = new Node(targetNode->small, "");
            targetNode->small = targetNode->large; //shift large key to small spot
            targetNode->large = "";
        }
        return;
    }
        
    //case 2.2: parent does not have space
    // bool promotingNodes = true;
    // while (promotingNodes)
    // {
    //     //split target
    //     Node *newRightSibling = new Node(targetNode->large, "");
    //     newRightSibling->large = "";
    //     newRightSibling->parent = parent;
    //     parent->right = newRightSibling;
    //     parent->left = targetNode;
    //     //split parent
    //     Node *grandParent = new Node(prepMidKey(parent, midKey), "");
    //     grandParent->left = parent;
    //     grandParent->right = new Node(parent->large, "");
    //     parent->parent = grandParent;
    //     parent->large = "";
    //     parent->right = parent->middle;
    //     if (grandParent != root_ && grandParent->parent->large == "")
    //     {
    //         promotingNodes = false;
    //     }
    //     if (root_->parent != nullptr)
    //     {
    //         root_ = grandParent;
    //     }
    //     targetNode = targetNode->parent;
    // }
}

//finds the middle key between the two in the node, and another key
//will also edit the node to replace the middle key with the inputted key (if needed)
string Tree::prepMidKey(Node *root, const string &key)
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
    preOrder(root_);
    cout << endl;
}

void Tree::preOrder(Node *root) const
{
    if (root == nullptr) return;

    bool is2Node = root->small != "" && root->large == "";
    if (is2Node)
    {
        cout << root->small << ", ";
        preOrder(root->left);
        preOrder(root->right);
        return;
    }
    //else: node is a 3-node
    cout << root->small << ", ";
    cout << root->large << ", ";
    preOrder(root->left);
    preOrder(root->middle);
    preOrder(root->right);
}

void Tree::inOrder() const
{
    inOrder(root_);
    cout << endl;
}

void Tree::inOrder(Node *root) const
{
    if (root == nullptr) return;

    bool is2Node = root->small != "" && root->large == "";
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
    cout << root->large << ", ";
    inOrder(root->middle);
    inOrder(root->right);
}

void Tree::postOrder() const
{
    postOrder(root_);
    cout << endl;
}

void Tree::postOrder(Node *root) const
{
    if (root == nullptr) return;

    bool is2Node = root->small != "" && root->large == "";
    if (is2Node)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->small << ", ";
        return;
    }
    //else: node is a 3-node
    postOrder(root->left);
    postOrder(root->middle);
    postOrder(root->right);
    cout << root->small << ", ";
    cout << root->large << ", ";
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
