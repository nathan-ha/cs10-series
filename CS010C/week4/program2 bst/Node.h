#pragma once
#include <string>

class Node {
    private:
        std::string data_;
        int count_;
        Node* left_;
        Node* right_;
    public:
        Node(const std::string& data);
        void setLeft(Node* newLeft);
        void setRight(Node* newRight);
        void setData(const std::string& newData);
        void incrementCount();
        void decrementCount();
        void setCount(int newCount);

        Node* getLeft() const;
        Node* getRight() const;
        const std::string& getData() const;
        int getCount() const;
};