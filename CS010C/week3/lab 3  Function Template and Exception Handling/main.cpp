#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

template<typename T> unsigned min_index(const vector<T> &vals, unsigned index);
template<typename T> void selection_sort(vector<T> &vals);
template<typename T> T getElement(vector<T> vals, int index);
vector<char> createVector();

int main() {
    //TODO: write tests and do part B
    
    return 0;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minIndex = 0;
    //go from "index" to end
    for (unsigned i = index; i < vals.size(); i++) {
        if (vals.at(i) < vals.at(minIndex)) {
            minIndex = i;
        }
    }
    return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals) {
    for (unsigned i = 0; i < vals.size() - 1; i++) {
        unsigned minIndex = i;
        for (unsigned j = i + 1; j < vals.size(); j++) {
            //look for smallest value
            if (vals.at(j) < vals.at(minIndex)) {
                minIndex = j;
            }
        }
        //swap element i with smallest element if a new one was found
        if (minIndex != i) {
            T temp = vals.at(i);
            vals.at(i) = minIndex;
            vals.at(minIndex) = temp;
        }
    }
}

template<typename T> 
T getElement(vector<T> vals, int index) {
    return vals.at(index);
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++) {
        vals.push_back(c);
        c++;
    }
    return vals;
}