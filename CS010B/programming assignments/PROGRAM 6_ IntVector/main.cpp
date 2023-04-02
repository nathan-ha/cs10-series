#include "IntVector.h"
#include <iostream>

using namespace std;

int main() {
    
    // //test constructors
    IntVector* v  = new IntVector(0, 0);
    IntVector* v2  = new IntVector(1, 0);
    IntVector* v3  = new IntVector(0, 1);
    IntVector* v4  = new IntVector(1, 1);
    IntVector* v5  = new IntVector(10, 2);

    // //test destructor
    delete v;
    delete v2;
    delete v3;
    delete v4;
    delete v5;

    cout << "Test what is in vector after deletion: " << v2->at(0) << endl;

    v  = new IntVector(0, 0);
    v2  = new IntVector(1, 0);
    v3  = new IntVector(0, 1);
    v4  = new IntVector(1, 1);
    v5  = new IntVector(10, 5);

    //test .at()
    for (unsigned int i = 0; i < 10; i++) {
        cout << "v5 at " << i << ": " << v5->at(i) << ", ";
    }
    cout << endl;

    // cout << "v at 0" << ": " << v->at(0) << endl; //expected error
    cout << "v2 at 0" << ": " << v2->at(0) << endl;
    // cout << "v3 at 0" << ": " << v3->at(0) << endl; //expected error
    cout << "v4 at 0" << ": " << v4->at(0) << endl;
    cout << "v5 at 0" << ": " << v5->at(0) << endl;
    cout << "v5 at 5" << ": " << v5->at(5) << endl;
    // cout << "v5 at 10" << ": " << v5->at(10) << endl; //expected error



    //test front()
    // cout << "v front: " << v->front() << endl; //expected error
    cout << "v2 front: " << v2->front() << endl;
    // cout << "v3 front: " << v3->front() << endl; //expected error
    cout << "v4 front: " << v4->front() << endl;
    cout << "v5 front: " << v5->front() << endl;

    //test back()
    // cout << "v back: " << v->back() << endl; //expected error
    cout << "v2 back: " << v2->back() << endl;
    // cout << "v3 back: " << v3->back() << endl; //expected error
    cout << "v4 back: " << v4->back() << endl;
    cout << "v5 back: " << v5->back() << endl;

    //test expand()
    // cout << "v capacity: " << v->capacity() << endl;
    // cout << "v2 capacity: " << v2->capacity() << endl;
    // cout << "v4 capacity: " << v4->capacity() << endl;
    // cout << "v5 capacity: " << v5->capacity() << endl;

    // cout << "\n\nDOUBLED CAPACITY" << endl;
    // v->expand();
    // v2->expand();
    // v4->expand();
    // v5->expand();

    // cout << "v capacity: " << v->capacity() << endl;
    // cout << "v2 capacity: " << v2->capacity() << endl;
    // cout << "v4 capacity: " << v4->capacity() << endl;
    // cout << "v5 capacity: " << v5->capacity() << endl;

    // cout << "\n\nINCREASED CAPACITY" << endl;
    // v2->expand(20);
    // v4->expand(0);
    // v5->expand(-1);

    // cout << "v capacity: " << v->capacity() << endl;
    // cout << "v2 capacity: " << v2->capacity() << endl;
    // cout << "v4 capacity: " << v4->capacity() << endl;
    // cout << "v5 capacity: " << v5->capacity() << endl;

    //test insert()
    cout << "v2 Before insert: " << v2->at(0) << endl;
    v2->insert(0, 1);
    cout << "v2 After insert: " << v2->at(0) << endl;

    cout << "v5 capacity Before insert: " << v5->capacity() << endl;
    cout << "v5 Before insert: " << v5->at(2) << endl;
    v5->insert(2, 10);
    cout << "v5 capacity after insert: " << v5->capacity() << endl;
    cout << "v5 After insert: " << v5->at(2) << endl;

    // cout << "Insert to end of vector" << endl;
    // int tempCapacity = v5->capacity();
    // v5->insert(tempCapacity, 10);
    // cout << "v5 After insert: " << v5->at(tempCapacity) << endl;

    //test erase()
    cout << "v5[1] before erase: " << v5->at(1) << endl;
    cout << "v5[2]: " << v5->at(2) << endl;
    v5->erase(1);
    cout << "v5[1] after erase: " << v5->at(1) << endl;
    cout << "v5[2]: " << v5->at(2) << endl;

    //test push_back()
    cout << "v2 last element before push_back(): " << v2->at(v2->size() - 1) << endl;
    v2->push_back(-1);
    cout << "v2 last element after push_back(): " << v2->at(v2->size() - 1) << endl;

    //test pop_back()
    cout << "v2 last element before pop_back(): " << v2->at(v2->size() - 1) << endl;
    v2->pop_back();
    cout << "v2 last element after pop_back(): " << v2->at(v2->size() - 1) << endl;

    //test clear()
    IntVector* v6 = new IntVector(10);
    cout << "v6 size before clear() " << v6->size() << endl;
    v6->clear();
    cout << "v6 size after clear() " << v6->size() << endl;

    //test resize()
    cout << "v6 size before resize() " << v6->size() << endl;
    v6->resize(15);
    cout << "v6 size after resize() " << v6->size() << endl;

    cout << "v6 size before resize() " << v6->size() << endl;
    v6->resize(150, 1);
    cout << "v6 size after resize() " << v6->size() << endl;
    cout << "v6 at 100: " << v6->at(100) << endl;

    //test reserve()
    cout << "v6 capacity before reserve(10) " << v6->capacity() << endl;
    v6->reserve(10);
    cout << "v6 capacity after reserve(10) " << v6->capacity() << endl;

    cout << "v6 capacity before reserve(200) " << v6->capacity() << endl;
    v6->reserve(200);
    cout << "v6 capacity after reserve(200) " << v6->capacity() << endl;

    v6->resize(20);

    //test assign()
    cout << "v6 values before assign(10, 2):" << endl;
    for (unsigned int i = 0; i < v6->size(); i++) {
        cout << v6->at(i) << ", ";
    }
    cout << endl;
    v6->assign(10, 2);

    cout << "v6 values after assign(10, 2):" << endl;
    for (unsigned int i = 0; i < v6->size(); i++) {
        cout << v6->at(i) << ", ";
    }
    cout << endl;

    IntVector v7(3);
    v7.at(0) = 1;
    cout << "v7.at(0): " << v7.at(0) << endl;
    v7.erase(1);
    cout << "v7.at(0) after erase(1): " << v7.at(0) << endl;

    v7.resize(1);
    // cout << "TESTING INSERT" << endl;
    // v7.insert(2, 2);
    // for (unsigned int i = 0; i < v7.size(); i++) {
    //     cout << v7.at(i) << ", ";
    // }

    cout << endl;
}