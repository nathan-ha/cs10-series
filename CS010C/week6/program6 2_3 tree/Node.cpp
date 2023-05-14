#include <iostream>
#include <stdexcept>
using namespace std;

#include "Node.h"

Node::Node(string small, string large)
    : small(small), 
      large(large), 
      left(nullptr), 
      middle(nullptr), 
      right(nullptr), 
      parent(nullptr)
{
}

//adds a key to a node, maintaining internal order
void Node::addKey(const string& newKey)
{
    if (small != "" && large != "")
    {
        throw runtime_error("Node::addKey(): tried to add key to full node");
    }
    //edge case: empty node
    if (small == "" && large == "")
    {
        small = newKey;
    }
    //add key to correct position
    else if (small < newKey)
    {
        large = newKey;
    }
    else
    {
        large = small;
        small = newKey;
    }
}