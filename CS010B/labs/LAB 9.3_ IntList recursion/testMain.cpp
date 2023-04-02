#include <iostream>
#include "IntList.h"
using namespace std;

int main() {
    IntList list;
    for (int i = 0; i < 10; i++) {
        list.push_front(i);
    }
    IntList list2;
    cout << '.' << list << '.'<< endl;
    cout << list2.exists(100) << endl;
    cout << list.exists(0) << endl;
}