#include "Node.h"

Node::Node(const std::string &data)
    : left(nullptr),
      right(nullptr),
      parent(nullptr),
      data(data)
{
}
