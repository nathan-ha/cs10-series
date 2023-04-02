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

    v  = new IntVector(0, 0);
    v2  = new IntVector(1, 0);
    v3  = new IntVector(0, 1);
    v4  = new IntVector(1, 1);
    v5  = new IntVector(10, 2);

    //test .at()
    for (int i = 0; i < 10; i++) {
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


    
}