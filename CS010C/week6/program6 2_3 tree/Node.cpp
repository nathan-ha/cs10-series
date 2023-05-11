#include <iostream>
using namespace std;

#include "Node.h"

Node::Node(string small, string large)
    : small(small), large(large), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr)
{
}

int Node::numChildren() const 
{
    int count = 0;
    if (left != nullptr) count++;
    if (middle != nullptr) count++;
    if (right != nullptr) count++;
    return count;
}

void Node::print() const
{
    if (numChildren() == 0) return;
    if (numChildren() == 1)
    {
        cout << small;
        return;
    }
    if (numChildren() == 2)
    {
        cout << small << ", " << large;
        return;
    }
}