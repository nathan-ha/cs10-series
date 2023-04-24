#include "stack_list.h"
#include <iostream>
using namespace std;

int main() {
    stack_list<int> s;

    for (int i = 0; i < 10; i++) {
        s.push(i);
    }

    s.print();
    for (int i = 0; i < 10; i++) {
        s.pop();
        s.print();
    }
}