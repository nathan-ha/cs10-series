#pragma once
#include "Node.h"
#include <string>

class BSTree {
    private:
        Node* root_;
        //bans copies
        BSTree(const BSTree&);
        BSTree operator=(const BSTree&);
        //helpers
        void burn(Node* currNode);
        void preOrder(Node* currNode) const;
        void inOrder(Node* currNode) const;
        void postOrder(Node* currNode) const;
        int treeHeight(Node* currNode) const;
    public:
        BSTree();
        ~BSTree();

        void insert(const std::string& newString);
        void remove(const std::string& target);

        bool search(const std::string& target) const;
        std::string largest() const;
        std::string smallest() const;
        int height(const std::string& target) const;

        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        
};