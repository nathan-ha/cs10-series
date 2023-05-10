using namespace std;

#include "Node.h"

Node::Node(string small, string large)
    : small(small), large(large), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr)
{
}
