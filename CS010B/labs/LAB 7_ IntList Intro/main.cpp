#include "IntList.h"
#include <iostream>

using namespace std;

int main() {
    IntList list;
    cout << list.empty() << endl;

    list.push_front(100);
    list.push_front(1);
    list.push_front(2);

    // list.pop_front(); 
    // list.pop_front(); 
    // list.pop_front(); 

    // list.pop_front();
    cout << list.empty() << endl;

    cout << list << endl;
    // list.print();

}