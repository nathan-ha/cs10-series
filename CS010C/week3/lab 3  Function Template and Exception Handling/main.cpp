#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

template<typename T> unsigned min_index(const vector<T> &vals, unsigned index);
template<typename T> void selection_sort(vector<T> &vals);
template<typename T> T getElement(vector<T> vals, int index);
vector<char> createVector();

int main() {
    //part 1: test selection sort and min index
    vector<int> v1 = {1,2,3,4,5};
    vector<int> v2;
    vector<int> v3 = {0,0,0,0};
    vector<int> v4 = {0};
    vector<int> v5 = {3,2,1};
    vector<int> v6 = {7,7,7,7};
    vector<int> v7 = {4,2,7,2,1,7,4,2,2,0,89,5};

    //making this 2d vector so i can perform actions on all of the test vectors in one shot
    vector<vector<int>*> intVectors;
    intVectors.push_back(&v1);
    intVectors.push_back(&v2);
    intVectors.push_back(&v3);
    intVectors.push_back(&v4);
    intVectors.push_back(&v5);
    intVectors.push_back(&v6);
    intVectors.push_back(&v7);

    cout << "Performing tests on various vectors of ints:\n";

    //prints out vectors and performs tests 
    for(auto& currVector: intVectors){
        cout << "list values before sort: ";
        for (auto& currElement: *currVector){
            cout << currElement << ' ';
        }
        cout << "\nmin index: " << min_index(*currVector, 0) << '\n';
        cout << "list values after sort: ";
        selection_sort(*currVector);
        for (auto& currElement: *currVector){
            cout << currElement << ' ';
        }
        cout << "\n----------------------------------------------------\n";
    }

    //same as above but with chars
    cout << "Performing tests on various vectors of chars:\n";

    vector<char> charV1 = {'a','b','c','d'};
    vector<char> charV2;
    vector<char> charV3 = {'\n', '\b', 0};
    vector<char> charV4 = {'0'};
    vector<char> charV5 = {'c', 'b', 'a'};
    vector<char> charV6 = {'a', 'a', 'a', 'a'};
    vector<char> charV7 = {'v', 'B', '1', 'V', 'c', 'z', 'z'};
    vector<char> charV8 = {'a','B','b','c'};

    vector<vector<char>*> charVectors;
    charVectors.push_back(&charV1);
    charVectors.push_back(&charV2);
    charVectors.push_back(&charV3);
    charVectors.push_back(&charV4);
    charVectors.push_back(&charV5);
    charVectors.push_back(&charV6);
    charVectors.push_back(&charV7);
    charVectors.push_back(&charV8);

    cout << "Performing tests on various vectors of strings:\n";

    for(auto& currVector: charVectors){
        cout << "list values before sort: ";
        for (auto& currElement: *currVector){
            cout << currElement << ' ';
        }
        cout << "\nmin index: " << min_index(*currVector, 0) << '\n';
        cout << "list values after sort: ";
        selection_sort(*currVector);
        for (auto& currElement: *currVector){
            cout << currElement << ' ';
        }
        cout << "\n----------------------------------------------------\n";
    }

    //same thing as above but with strings
    vector<string> strV1 = {"a", "b", "c", "d"};
    vector<string> strV2;
    vector<string> strV3 = {"\n", "\b"};
    vector<string> strV4 = {"0"};
    vector<string> strV5 = {"c", "b", "a"};
    vector<string> strV6 = {"a", "a", "a", "a"};
    vector<string> strV7 = {"dsfwe", "fifo", "doi2j0j", "a", "Zzz", "psdoi", "Aaa"};
    vector<string> strV8 = {"a", "z", "z", "A", "1", "n"};

    vector<vector<string>*> stringVectors;
    stringVectors.push_back(&strV1);
    stringVectors.push_back(&strV2);
    stringVectors.push_back(&strV3);
    stringVectors.push_back(&strV4);
    stringVectors.push_back(&strV5);
    stringVectors.push_back(&strV6);
    stringVectors.push_back(&strV7);
    stringVectors.push_back(&strV8);


    cout << "Performing tests on various vectors of strings:\n";

    for(auto& currVector: stringVectors){
        cout << "list values before sort: ";
        for (auto& currElement: *currVector){
            cout << currElement << ' ';
        }
        cout << "\nmin index: " << min_index(*currVector, 0) << '\n';
        cout << "list values after sort: ";
        selection_sort(*currVector);
        for (auto& currElement: *currVector){
            cout << currElement << ' ';
        }
        cout << "\n----------------------------------------------------\n";
    }

    //Part B
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
        try {
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch (out_of_range& exception) {
            cout << "exception: " << exception.what() << endl;
        }
    }

    return 0;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minIndex = index;
    //only search from from "index" to end
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
        return; //was debating if I should throw an exception here or not, but zybooks didn't appreciate me trying it so I decided to return instead
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
    if (index < 0 || static_cast<unsigned>(index) >= vals.size()) {
        throw out_of_range("attemped to get element out of range");
    }
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