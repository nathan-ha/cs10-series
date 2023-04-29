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
        void insert(Node* prevNode, Node* currNode, const std::string& newString);
        void print(const Node* currNode) const;
        bool search(Node* currNode, const std::string& target) const;
        void smallest(Node* currNode, Node*& minNode) const;
        void largest(Node* currNode, Node*& maxNode) const;
        int height(const std::string& target, Node* currNode, int currHeight) const;  
        void preOrder(Node* currNode) const;
        void inOrder(Node* currNode) const;
        void postOrder(Node* currNode) const;
        void remove(const std::string& target, Node* currNode, Node* prevNode);
        Node* getFarRightNode(Node* currNode) const;
        Node* getFarLeftNode(Node* currNode) const;
        Node* findReplacement(Node* currNode) const;
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