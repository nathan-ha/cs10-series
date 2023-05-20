#pragma once
#include <fstream>
#include <string>

using namespace std;

#include "Node.h"

class AVLTree
{
    private:
        Node *root_;

    public:
        AVLTree();
        ~AVLTree();
        void insert(const string &);
        int balanceFactor(Node *) const;
        void printBalanceFactors() const;
        void visualizeTree(const string &) const;
        
    private:
        enum imbalanceType {RR, LL, RL, LR};
        void burnTree(Node *);
        AVLTree operator=(const AVLTree &);
        AVLTree(const AVLTree &);
        Node *findUnbalancedNode(Node *) const;
        void rotate(Node *);
        Node *rotateLeft(Node *);
        Node *rotateRight(Node *);
        void printBalanceFactors(Node *) const;
        int height(Node *) const;
        void visualizeTree(ofstream &, Node *) const;
        Node *rotateLR(Node *);
        Node *rotateRL(Node *);
        imbalanceType rotateCase(Node *, const string &) const;
};

