#include "Node.h"

Node::Node(const string &data)
    : left(nullptr),
      right(nullptr),
      parent(nullptr),
      data(data),
      count(1)
{
}
