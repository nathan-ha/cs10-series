#include "queue_list.h"
#include <iostream>
using namespace std;

int main() {
    queue_list<int> s;
    for (int i = 0; i < 10; i++) {
        s.push_back(i);
    }
    s.print();
    for (int i = 0; i < 9; i++) {
        s.pop();
        s.print();
    }
}