#pragma once

#include "Node.h"

class AVLTree
{
    private:
        Node *root_;

    public:
        AVLTree();
        void insert(const string &);
        int balanceFactor(Node *) const;
        void printBalanceFactors() const;
        
    private:
        AVLTree operator=(const AVLTree &);
        AVLTree(const AVLTree &);
        Node *findUnbalancedNode(Node *);
        void rotate(Node *);
        Node *rotateLeft(Node *);
        Node *rotateRight(Node *);
        void printBalanceFactors(Node *);
};

