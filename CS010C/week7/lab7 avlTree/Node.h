#pragma once
#include <string>

using namespace std;

class Node
{
    friend class AVLTree;
    Node(const std::string &);

    private:
        Node *left;
        Node *right;
        string data;
};