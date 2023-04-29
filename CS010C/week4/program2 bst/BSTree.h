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
        void print(const Node* currNode) const;
        void preOrder(Node* currNode) const;
        void inOrder(Node* currNode) const;
        void postOrder(Node* currNode) const;
        void remove(const std::string& target, Node* currNode, Node* prevNode);
        Node* findReplacement(Node* currNode, Node*& parent) const;
    public:
        BSTree();
        ~BSTree();

        void print() const; //used to test functions

        void insert(const std::string& newString);
        void remove(const std::string& target);

        bool search(const std::string& target) const;
        const std::string& largest() const;
        const std::string& smallest() const;
        int height(const std::string& target) const;

        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        
};