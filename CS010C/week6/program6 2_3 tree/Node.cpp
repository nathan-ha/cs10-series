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

//removes a key while maintaining internal order
void Node::removeKey(const string &key)
{
    if (key == large)
    {
        large = "";
    }
    else if (key == small)
    {
        //shift large to small
        small = large;
        large = "";
    }
    else
    {
        throw runtime_error("Node::removeKey(): this node does not contain the key");
    }
}