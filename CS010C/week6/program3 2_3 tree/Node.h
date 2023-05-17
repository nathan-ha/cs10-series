#ifndef __NODE_H
#define __NODE_H

#include <string>
using namespace std;


class Node
{

  friend class Tree;
  Node(string small, string large);

private:
  string small;
  string large;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  void addKey(const string &);
  void removeKey(const string &);
  void clear();
};

#endif
