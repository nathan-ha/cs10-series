#pragma once
#include "Node.h"
#include <string>
#include <iostream>

class BSTree {
    private:
        Node* root_;
        //bans copies
        BSTree(const BSTree&);
        BSTree operator=(const BSTree&);
        //helpers
        void burnTree(Node* currNode);
        void insert(Node* prevNode, Node* currNode, const std::string& newString);
        void print(const Node* currNode) const;
        bool search(Node* currNode, const std::string& target) const;
    public:
        BSTree();
        ~BSTree();

        void print() const;

        void insert(const std::string& newString);
        void remove(const std::string& target) const;

        bool search(const std::string& target) const;
        const std::string& largest() const;
        const std::string& smallest() const;
        int height(const std::string& target) const;

        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        
};