#pragma once
#include <string>
#include <fstream>

#include "Node.h"

enum imbalanceType {RR, LL, RL, LR};

class AVLTree
{
    private:
        Node *root_;

    public:
        AVLTree();
        ~AVLTree();
        void insert(const std::string &);
        int balanceFactor(Node *) const;
        void printBalanceFactors() const;
        void visualizeTree(const std::string &) const;
        
    private:
        //bans copies
        AVLTree operator=(const AVLTree &);
        AVLTree(const AVLTree &);
        //helpers
        imbalanceType rotateCase(Node *, const std::string &) const;
        void burnTree(Node *);
        Node *findUnbalancedNode(Node *) const;
        Node *rotate(Node *, const std::string &);
        Node *rotateLeft(Node *);
        Node *rotateRight(Node *);
        int height(Node *) const;
        void printBalanceFactors(Node *) const;
        void visualizeTree(std::ofstream &, Node *) const;
};

