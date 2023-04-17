//in class notes, April 17, 2023
#include <stdexcept>

//stack using linked list
class Stack {
private:
    struct Node {
        int value;
        Node* next;
        Node(int value): value(value), next(nullptr) {}
    };
    Node* head;
public:
    Stack(): head(nullptr) {}
    void push(int v) {
        auto n = new Node(v);
        n->next = head;
        head = n;
    }
    bool is_empty() const {
        return head == nullptr;
    }
    void pop() {
        if (is_empty()) throw std::runtime_error("stack is empty");
        auto victim = head;
        head  = head->next;
        delete victim;
    }
};

#define INITIAL_SIZE 2 //using macro to get rid of errors

//stack using array
class StackArray {
private:
    int* A;
    int size;
public:
    StackArray(): A(new int[INITIAL_SIZE]) {}
    void push(int x) {
        if (size >= INITIAL_SIZE) throw std::out_of_range("stack has no more space");
        A[size++] = x;
    }
    void pop() {
        size--;
    }
};