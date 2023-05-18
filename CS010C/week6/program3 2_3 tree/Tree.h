#ifndef __TREE_H
#define __TREE_H

using namespace std;

#include "Node.h"

class Tree
{
private:
  Node *root_;
public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search(const string &) const;

private:
  Tree operator=(const Tree &);
  Tree(const Tree &);
  void burnTree(Node *);
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  string prepMidKey(Node *, const string &key);
  string split(Node *);
  char findValidSibling(Node *, Node *&);
  void rotateLeft(Node *, Node *);
  void rotateRight(Node *, Node *);

};

#endif
