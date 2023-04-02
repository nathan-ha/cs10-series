#include "SortedSet.h"
#include <iostream>

using namespace std;

int main() {

    cout << "Testing default constructor and destructor.\n\n";
    SortedSet DefaultConstructorTest;
    SortedSet* deleteTest = new SortedSet;
    delete deleteTest;

    IntList list;
    for (int i = 0; i < 30; i++) {
        list.push_back(i % 15 - i % 6 + i - 2 * i % 7 + i % 5); //randomize the values a little
    }
    cout << "IntList list: " << endl << list << endl << endl;

    cout << "Testing passing in control IntList: " << endl;
    SortedSet IntListSet(list);
    cout << "IntListSet: " << IntListSet << endl << endl;

    SortedSet copySet(IntListSet);
    cout << "Testing copy constructor.\nNew (copied) Set: " << copySet << endl << endl;

    cout << "Testing in():\nIs 15 in IntListSet?  " << boolalpha << IntListSet.in(15) << endl;
    cout << "Is -99 in IntListSet? " << boolalpha << IntListSet.in(-99) << endl << endl;

    IntList list2;
    for (int i = 0; i < 20; i++) {
        list2.push_back(i);
    }
    cout << "list2: " << list2 << endl;
    SortedSet SortedSet2(list2);
    cout << "IntListSet: " << IntListSet << endl;
    cout << "SortedSet2: " << SortedSet2 << endl;
    cout << "Testing union of IntListSet and SortedSet2: " << (IntListSet | SortedSet2) << endl;
    cout << "Testing Intersection of IntListSet and SortedSet2: " << (IntListSet & SortedSet2) << endl << endl;

    SortedSet2.push_front(-1);
    cout << "Testing push_front() on SortedSet2:\n"
         << "Pushing -1: " << SortedSet2 << endl;
    SortedSet2.push_front(-1);
    cout << "Test if duplicates are pushed:\n"
         << "Pushing -1: " << SortedSet2 << endl;

    SortedSet2.push_back(20);
    cout << "Testing push_back() on SortedSet2:\n"
         << "Pushing 20: " << SortedSet2 << endl;
    SortedSet2.push_back(20);
    cout << "Test if duplicates are pushed:\n"
         << "Pushing 20: " << SortedSet2 << endl;
    
    SortedSet set3;
    set3.push_back(1);
    set3.push_back(3);
    cout << "Testing insert_ordered()\n"
         << "set3: " << set3 << endl;
    set3.insert_ordered(2);
    cout << "inserting 2:\n"
         <<  set3 << endl;
    set3.insert_ordered(2);
    cout << "inserting 2:\n"
         <<  set3 << endl;
    set3.insert_ordered(5);
    cout << "inserting 5:\n"
         <<  set3 << endl << endl;

    SortedSet set4;
    set4.push_back(1);
    cout << "Testing add()\n"
         << "set3: " << set4 << endl;
    set4.insert_ordered(5);
    cout << "adding 5:\n"
         <<  set4 << endl;
    set4.insert_ordered(2);
    cout << "adding 2:\n"
         <<  set4 << endl;
    set4.insert_ordered(5);
    cout << "adding 5:\n"
         <<  set4 << endl << endl;

    SortedSet set5;
    SortedSet set6;
    for (int i = 5; i < 10; i++) {
        set5.push_back(i);
    }
    cout << "Testing |= operator:\n"
         << "set5: " << set5 << endl
         << "set6: " << set6 << endl
         << "Assigning set5 to the union of itself and set6" << endl;
    set5 |= set6;
    cout << "set5: " << set5 << endl;

    set5 |= set4;
    cout << "set4: " << set4 << endl;
    cout << "Now assigning set6 to the union of itself and set4:\n"
         << "set5: " << set5 << endl << endl;

    SortedSet set7;
    SortedSet set8;
    for (int i = 1; i < 10; i++) {
        set7.push_back(i);
    }
    cout << "Testing &= operator:\n"
         << "set7: " << set7 << endl
         << "set8: " << set8 << endl
         << "Assigning set7 to the intersection of itself and set8" << endl;
    set7 &= set8;
    cout << "set7: " << set7 << endl;

    for (int i = 1; i < 10; i++) {
        set7.push_back(i);
    }
    cout << "repopulated set7: " << set7 << endl;
    cout << "IntListSet: " << IntListSet << endl;
    set7 &= IntListSet;
    cout << "Now assigning set7 to the intersection of itself and IntListSet:\n"
         << "set7: " << set7 << endl;
}