#include "queue_array.h"
#include <iostream>
using namespace std;

int main() {
    queue_array<int> s(10);
    
    cout << "pushing\n";
    for (int i = 0; i < 11; i++) {
        try {
            s.push(i);
            s.print();
        }
        catch (out_of_range& e) {
            cout << "exception: " << e.what() << endl; 
        }
    }
    cout << "popping\n";    
    for (int i = 0; i < 11; i++) {
        try {
            s.pop();
            s.print();
        }
        catch (out_of_range& e) {
            cout << "exception: " << e.what() << endl; 
        }
    }
}