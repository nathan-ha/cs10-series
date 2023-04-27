//provided files: https://drive.google.com/open?id=13r8_4vDUS2NRyQILKAoe_tBmIdqV0UQX
#include "Node.h"
#include "BSTree.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    BSTree b;
    BSTree emptyBST;
    b.insert("a");
    b.insert("b");
    b.insert("c");
    b.insert("d");
    b.insert("e");
    b.insert("a");
    b.insert("a");
    b.insert("a");
    b.insert("d");
    b.print();
    cout << boolalpha << b.search("a") << endl
         << b.search("-1") << endl
         << b.search("c") << endl
         << b.search("e") << endl;

    return 0;
}