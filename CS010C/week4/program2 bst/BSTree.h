#pragma once
#include "Node.h"
#include <string>

class BSTree {
    private:
        Node* root;
        //bans copies
        BSTree(const BSTree&);
        BSTree operator=(const BSTree&);
        //helpers
        void insert(Node* currNode, const std::string& newString);
    public:
        BSTree();
        ~BSTree();

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