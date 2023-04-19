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
    vector<int> v1 = {1,2,3,4,5};
    vector<int> v2;
    vector<int> v3 = {0,0,0,0};
    vector<int> v4 = {0};
    vector<int> v5 = {3,2,1};
    vector<int> v6 = {7,7,7,7};
    vector<int> v7 = {4,2,7,2,1,7,4,2,2,0,89,5};

    //making this 2d vector so i can perform actions on all of the test vectors in one shot
    vector<vector<int>> intVectors;
    intVectors.push_back(v1);
    intVectors.push_back(v2);
    intVectors.push_back(v3);
    intVectors.push_back(v4);
    intVectors.push_back(v5);
    intVectors.push_back(v6);
    intVectors.push_back(v7);

    cout << "Performing tests on various vectors of ints:\n";

    for(auto& currVector: intVectors){
        try {
            cout << "list values before sort:\n";
            for (auto& currElement: currVector){
                cout << currElement << ' ';
            }
            cout << "\nmin index: " << min_index(currVector, 0) << '\n';
            cout << "list values after sort:\n";
            selection_sort(currVector);
            for (auto& currElement: currVector){
                cout << currElement << ' ';
            }
            cout << "\n\n";
        }
        catch (logic_error& error) {
            cout << "error: " << error.what() << endl;
        }
    }

    //TODO: start part 2 of assignment

    return 0;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minIndex = index;
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
    if (vals.size() <= 0) {
        throw logic_error("selection_sort: empty vector");
    }
    for (unsigned i = 0; i < vals.size() - 1; i++) {
        unsigned minIndex = min_index(vals, i);
        //swap element i with smallest element if a smaller element was found
        if (i != minIndex) {
            T temp = vals.at(i);
            vals.at(i) = vals.at(minIndex);
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