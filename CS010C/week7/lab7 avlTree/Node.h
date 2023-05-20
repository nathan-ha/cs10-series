#pragma once
#include <string>

class Node
{
    friend class AVLTree;
    Node(const std::string &);

    private:
        Node *left;
        Node *right;
        Node *parent;
        std::string data;
        int count;
};