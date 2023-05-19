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
            uncle->left->parent = uncle;
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
    //replaces the small key
    if (key < root->small)
    {
        string midKey = root->small;
        root->small = key;
        return midKey;
    }
    //replaces the large key
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

//print small, look left, print large, then look middle, then look right
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

//print small, look left, then look middle, print large, then look right
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

//look left, look middle, print small, look right, then print large
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

    //case 0: three keys in tree
    bool rootHasTwoChildren = root_->middle == nullptr;
    bool bothChildrenAreLeaves = root_->left->isLeaf() && root_->right->isLeaf();
    if (rootHasTwoChildren && bothChildrenAreLeaves)
    {
        if (target == root_)
        {
            //merge two children into new root
            root_->clear();
            root_->addKey(root_->left->small);
            root_->addKey(root_->right->small);
            delete root_->left;
            delete root_->right;
            root_->left = nullptr;
            root_->right = nullptr;
            return;
        }
        else if (root_->right == target)
        {
            //delete right child and merge remaining two keys
            delete target;
            root_->addKey(root_->left->small);
            delete root_->left;
            root_->left = nullptr;
            root_->right = nullptr;
            return;
        }
        else if (root_->left == target)
        {
            //delete right child and merge remaining two keys
            delete target;
            root_->addKey(root_->right->small);
            delete root_->right;
            root_->left = nullptr;
            root_->right = nullptr;
            return;
        }
    }

    //case 1: removing leaf with one key
    if (isLeaf && target->large == "")
    {
        //looking for sibling to borrow from
        Node *sibling = nullptr;
        Node *parent = target->parent;
        char siblingPosition = findValidSibling(target, sibling);

        //case 1.1: sibling has a key avaiable -- take a key from them
        if (sibling != nullptr)
        {
            //rotate sibling's key into target
            //if target is a right child
            if (parent->right == target)
            {
                rotateRight(target, sibling);
            }
            //if target is a left child
            else if (parent->left == target)
            {
                rotateLeft(target, sibling);
            }
            //if target is a middle child
            else if (parent->middle == target)
            {
                //rotate right or left depending on which siblings have spare keys
                if (siblingPosition == 'l') //taking from left sibling
                {
                    rotateRight(target, sibling);
                }
                else if (siblingPosition == 'r') //taking from right sibling
                {
                    rotateLeft(target, sibling);
                }
            }
            return;
        }
        //case 1.2: immediate sibling has no avaiable keys -- merge them
        
        //if parent only has two children, merge the remaining child with it
        if (parent->middle == nullptr)
        {
            parent->addKey(sibling->small);
            delete target;
            delete sibling;
            parent->left = nullptr; //parent is now a leaf
            parent->right = nullptr;
            return;
        }
        
        //parent has three children
        //removing as right child
        if (parent->right == target)
        {
            sibling = parent->middle;
            target->clear();
            target->addKey(parent->large); //replace target key with relevant sibling and parent keys
            cout << siblingPosition << endl;
            target->addKey(sibling->small);
            
            parent->large = "";
            delete sibling;
            parent->middle = nullptr; //parent is now a 2-node
            return;
        }
        
        //removing as left child
        if (parent->left == target)
        {
            sibling = parent->middle;
            target->clear();
            target->addKey(parent->small); //replace target key with relevant sibling and parent keys
            target->addKey(sibling->small);
            parent->removeKey(parent->small);
            delete sibling;
            parent->middle = nullptr; //parent is now a 2-node
            return;
        }
        
        if (parent->middle == target)
        {
            //move parent key into sibling's key before deleting child
            if (siblingPosition == 'l') //sibling is a left child
            {
                sibling->addKey(parent->small); //move parent's small key into left sibling
                parent->removeKey(parent->small);
            }
            else if (siblingPosition == 'r')
            {
                sibling->addKey(parent->large); //move parent's large key into right sibling
                parent->removeKey(parent->large);
            }
            delete target;
            parent->middle = nullptr;
            return;
        }
        //if this line is reached, one of the above cases did not run when it was supposed to
        throw runtime_error("something went wrong when removing a leaf");
    }

    throw runtime_error("remove(): did not handle this case yet");

}

//rotate nodes left, used in insert
void Tree::rotateLeft(Node *target, Node *sibling)
{
    Node *parent = target->parent;
    target->small = parent->small;  //overwrite target's key with a parent's key
    parent->small = parent->large;
    parent->large = "";
    parent->addKey(sibling->small); //move sibling's key into parent
    sibling->removeKey(sibling->small);
}

//rotates nodes right, used in insert
void Tree::rotateRight(Node *target, Node *sibling)
{
    Node *parent = target->parent;
    target->small = parent->large; //overwrite target's key with a parent's key
    parent->large = "";
    parent->addKey(sibling->large); //move sibling's key into parent
    sibling->large = "";
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
    if (parent->middle == curr)
    {
        
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
