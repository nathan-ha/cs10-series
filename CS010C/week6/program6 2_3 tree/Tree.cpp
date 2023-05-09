#include <stdexcept>
using namespace std;

#include "Tree.h"

Tree::Tree()
{
    throw runtime_error("create constructor");
}
Tree::~Tree()
{
    throw runtime_error("create destructor");
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
