#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

//basically a constructor for nodes
Node* newNode(string payload) {
    Node* newNode = new Node;
    newNode->payload = payload;
    newNode->next = nullptr;
    return newNode;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        if (head == nullptr) {
            head = newNode(name); // initialize head specially
            prev = head;
        } else {
            //append new node to last node
            prev->next = newNode(name);
            prev = prev->next;
        }
    }
    if (prev != nullptr) {
        prev->next = head; // makes circular -- last node points to head
    }
    return head;
}

void print(Node* start) {
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        //exit after iterating through whole list once
        if (curr == start) {
            break;
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing (last node circles back to itself)
        //look for kth node
        for (int i = 0; i < k; ++i) {
          prev = curr;
          curr = curr->next;
        }   
        // delete kth node
        prev->next = curr->next;
        delete curr;
        curr = prev->next; //point curr back into the list
    }
    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    if (!(cin >> n >> k)) return 1;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
        delete lastPerson;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}