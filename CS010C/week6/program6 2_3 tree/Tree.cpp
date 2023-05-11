#include <stdexcept>
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
    throw runtime_error("create insert()");
}
void Tree::preOrder() const
{
    throw runtime_error("create preOrder()");
}
void Tree::inOrder() const
{
    throw runtime_error("create inOrder()");
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
