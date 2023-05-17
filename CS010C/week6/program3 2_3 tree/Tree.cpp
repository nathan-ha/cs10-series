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

//splits a full node and then returns the middle key, will return "" if no more keys are promoted
string Tree::split(Node *child)
{
    if (child->large == "")
    {
        throw runtime_error("Tree::split(): tried to split a non-full node");
    }
    // Node *parent = child->parent;
    throw runtime_error("create split()");

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
    bool notLeaf = targetNode->left != nullptr; //leaf nodes will not have a left child, which implies that it doesn't have any children
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
        notLeaf = targetNode->left != nullptr;
    }

    // case 1: leaf has room for new key
    if (targetNode->large == "") //if a node has one key, the key will sit in the small part
    {
        targetNode->addKey(newKey);
        return;
    }
    
    // case 2: no room in leaf
    string midKey = prepMidKey(targetNode, newKey); //middle key will be "tossed" up into the parent
    //edge case: target node is the root (aka parent is null)
    if (targetNode->parent == nullptr)
    {
        root_ = new Node(midKey, "");
        //split the target node into a left and right child for the new root
        root_->left = targetNode;
        root_->right = new Node(targetNode->large, "");
        targetNode->large = "";
        root_->right->parent = root_;
        targetNode->parent = root_;

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
            parent->middle->parent = parent;
            targetNode->large = "";
        }
        //case 2.1.2: need to split the right child of parent
        else if (parent->right == targetNode)
        {
            parent->middle = new Node(targetNode->small, "");
            parent->middle->parent = parent;
            targetNode->small = targetNode->large; //shift large key to small spot
            targetNode->large = "";
        }
        return;
    }
        
    //case 2.2: parent does not have space

    while (midKey != "") //keep looping until no more middle keys are being tossed up
    {
        //make new root and connect to left and right children
        Node* grandParent = new Node(prepMidKey(parent, midKey), "");
        grandParent->parent = parent->parent;
        parent->parent = grandParent;
        grandParent->left = parent; //original parent will be left child
        Node* uncle = new Node(parent->large, "");
        grandParent->right = uncle;
        uncle->parent = grandParent;
        parent->large = "";
        if (grandParent->parent == nullptr) root_ = grandParent;

        //TODO: entire subtree is leaked somewhere

        //connect parents to children
        //case 2.2.1: target node is a right child
        if (parent->right == targetNode)
        {
            //split node (original node will be left child)
            Node* newRightSibling = new Node(targetNode->large, "");
            newRightSibling->parent = uncle;
            targetNode->large = "";
            uncle->left = targetNode;
            uncle->right = newRightSibling;
            targetNode->parent = uncle;
            parent->right = parent->middle; //uncle took parent's middle and left children
            parent->middle = nullptr;
        }
        //case 2.2.2: target node is a left child
        else if (parent->left == targetNode)
        {
            //split node (original node will be left child)
            Node* newRightSibling = new Node(targetNode->large, "");
            newRightSibling->parent = parent;
            targetNode->large = "";
            uncle->left = parent->middle;
            uncle->middle->parent = uncle;
            uncle->right = parent->right; //uncle took parent's middle and right children
            uncle->right->parent = uncle;
            parent->right = newRightSibling;
            parent->middle = nullptr;
        }
        midKey = prepMidKey(parent, midKey);
        parent = grandParent;
    }
}


//finds the middle key between the two in the node, and another key
//will also edit the node to replace the middle key with the inputted key (if needed)
string Tree::prepMidKey(Node *root, const string &key)
{
    if (root->large == "")
    {
        return ""; //there is no middle key if there are only two keys
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
    preOrder(root->left);
    cout << root->large << ", ";
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
    inOrder(root->middle);
    cout << root->large << ", ";
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
    cout << root->small << ", ";
    postOrder(root->right);
    cout << root->large << ", ";
}

//remove a key while maintaining 2-3 tree properties
void Tree::remove(const string &targetKey)
{
    //edge case: empty tree
    if (root_ == nullptr)
    {
        throw runtime_error("Tree::remove(): tried to remove from empty tree");
    }
    //find node with target key
    Node *target = root_;
    while (target->large != targetKey && target->small != targetKey)
    {
        if (target == nullptr) //target key was not found
        {
            throw runtime_error("remove(): key not found");
        }
        if (targetKey < target->small)
        {
            target = target->left;
        }
        else if (target->large < targetKey)
        {
            target = target->right;
        }
        else
        {
            target = target->middle;
        }
    }
    
    bool isLeaf = target->left == nullptr; //if left is null, then the rest will be null too
    //edge case: only one node
    if (target == root_ && isLeaf)
    {
        //has one key
        if (root_->large == "")
        {
            delete root_;
            root_ = nullptr;
        }
        else
        {
            root_->removeKey(targetKey); //just remove the key, and not the whole node
        }
        return;
    }
    //if the target is a leaf with two keys
    if (isLeaf && target->large != "")
    {
        target->removeKey(targetKey);
        return;
    }

    //case 1: removing node with one key
    //looking for sibling to borrow from
    Node *sibling = nullptr;
    char siblingPosition = findValidSibling(target, sibling);

    //case 1.1: sibling has a key avaiable
    if (siblingPosition != 0)
    {
        //rotate
    }


    //TODO: finish remove

}

//finds sibling with more than one key to take from
//returns the location of the sibling relative to the parent along with a pointer to the sibling
char Tree::findValidSibling(Node *curr, Node *&sibling)
{
    Node *parent = curr->parent;
    //case 1: curr is a left child
    if (parent->left == curr)
    {
        //immediate right sibling of left child
        if (parent->middle == nullptr && parent->right->large != "")
        {
            sibling = parent->right;
            return 'r';
        }
        else if (parent->middle != nullptr && parent->middle->large != "")
        {
            sibling = parent->middle;
            return 'm';
        }
        sibling = nullptr;
        return 0; //return null if immediate sibling does not have enough keys
    }
    //case 2: curr is a right child
    if (parent->right == curr)
    {
        //immediate left sibling of right child
        if (parent->middle == nullptr && parent->left->large != "")
        {
            sibling = parent->left;
            return 'l';
        }
        else if (parent->middle != nullptr && parent->middle->large != "")
        {
            sibling = parent->middle;
            return 'm';
        }
        sibling = nullptr;
        return 0; //return null if immediate sibling does not have enough keys
    }
    //case 3: curr is a middle child
    if (parent->left->large != "")
    {
        sibling = parent->left;
        return 'l';
    }
    else if (parent->right->large != "")
    {
        sibling = parent->right;
        return 'r';
    }
    sibling = nullptr;
    return 0;
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
