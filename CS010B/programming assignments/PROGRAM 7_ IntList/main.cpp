#include "IntList.h"
#include <iostream>

using namespace std;

int main() {
    IntList list;
    cout << boolalpha << "is empty at start: " << list.empty() << endl;

    list.push_front(100);
    list.push_front(1);
    list.push_front(2);

    list.pop_front(); 
    list.pop_front(); 
    list.pop_front(); 

    cout << boolalpha << "is empty after popping all elements: " << list.empty() << endl;

    cout << list << endl;

    list.push_front(101);
    list.push_front(11);
    list.push_front(21);

    cout << list << endl;

    list.push_back(22);
    cout << "after push back: " << list << endl;

    IntList list2;
    list2.push_back(1);
    cout << "push back on empty list: " << list2 << endl;

    cout << "before sort: " << list << endl;
    list.selection_sort();
    cout << "after sort: " << list << endl;

    IntList original;
    IntList copy = original;
    original.push_back(10);
    copy.push_back(0);
    cout << "original: " << original << endl;
    cout << "copy (should different value): " << copy << endl;
    original.push_back(1);
    IntList copy2 = original;
    cout << "copy2 (should same values as original plus another): " << copy2 << endl << endl;

    IntList list3;
    list3.push_back(1); list3.push_back(2); list3.push_back(3); 
    cout << "list3 before clear: " << list3 << endl;
    list3.clear();
    cout << "list3 after clear: " << list3 << endl;

    IntList emptyList;
    cout << "emptyList before clear: " << emptyList << endl;
    emptyList.clear();
    cout << "emptyList after clear: " << emptyList << endl << endl;

    IntList list4;
    for (int i = 0; i < 10; i++) {
        list4.push_back(i);
    }
    cout << "list4 before insert: " << list4 << endl;
    list4.insert_ordered(3);
    cout << "list4 after insert: " << list4 << endl;

    IntList list5;
    cout << "list5 before insert: " << list5 << endl;
    list5.insert_ordered(1);
    cout << "list5 after insert: " << list5 << endl;

    list5.insert_ordered(2);
    cout << "test list5 insert to end: " << list5 << endl;

    list5.insert_ordered(0);
    cout << "test list5 insert to beginning: " << list5 << endl << endl;

    copy.clear();
    cout << "original: " << original << endl;
    cout << "copy before = opertator : " << copy << endl;
    copy = original;
    cout << "copy after = opertator : " << copy << endl << endl;

    emptyList.remove_duplicates();
    IntList list6;
    list6.push_back(2); list6.push_back(2); list6.push_back(2); list6.push_back(3); list6.push_back(5); list6.push_back(5); list6.push_back(6); list6.push_back(1); list6.push_back(1); list6.push_back(1);
    cout << "list6 before duplicate removal: " << list6 << endl;
    list6.remove_duplicates();
    cout << "list6 after duplicate removal: " << list6 << endl;

    list6 = list6;
    cout << "list6 after assigning it to itself: " << list6 << endl;

    IntList list7;
    list7 = list6;
    cout << "list7 after assigning (filled) list6 to (empty) list7: " << list7 << endl;

    IntList list8;
    list8 = emptyList;
    cout << "list8 after being assigned to empty list: " << list8 << endl;

    list6 = list5;
    cout << "list6 after being assigned to list5: " << list5 << endl;

    IntList list9;
    list9.push_back(6); list9.push_back(6); list9.push_back(2); list9.push_back(2); list9.push_back(6); list9.push_back(5); list9.push_back(5); list9.push_back(6); list9.push_back(1); list9.push_back(1); list9.push_back(1); list9.push_back(6);
    cout << "list9 before removeing max: " << list9 << endl;
    list9.remove_max();
    cout << "list9 after removeing max: " << list9 << endl;

    IntList list10;
    for (int i = 0; i < 10; i++) list10.push_back(11);
    cout << "list10 before removing max: " << list10 << endl;
    list10.remove_max();
    cout << "list10 after removing max: " << list10 << endl;



}