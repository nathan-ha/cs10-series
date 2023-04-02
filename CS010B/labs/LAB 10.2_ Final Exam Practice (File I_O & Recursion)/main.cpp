#include <fstream>
#include <iostream>
using namespace std;

bool rCopy(const string &inputFile, const string &outputFile);
bool rCopy(const string &inputFile, const string &outputFile, ifstream &fin, ofstream &fout); //helper


int main(int argc, char* argv[]) {
    rCopy(argv[1], argv[2]);
}

bool rCopy(const string &inputFile, const string &outputFile) {

    ifstream fin(inputFile);

    if (not fin.is_open()) {
        cout << "Error opening " << inputFile << endl
             << "Copy not completed" << endl;
        return false;
    }

    ofstream fout(outputFile); //only open output if input was opened successfully

    return rCopy(inputFile, outputFile, fin, fout);
}

// bool rCopy(const string &inputFile, const string &outputFile, ifstream &fin, ofstream &fout) {
//     //base case: end of file is reached or file just didn't open
//     if (fin.fail() or fout.fail()) return false;

//     char c;
//     fin.get(c);

//     //goes to the back of the file (sort of)
//     rCopy(inputFile, outputFile, fin, fout); //new characters are copied since fin (and everything else) is passed by reference

//     //prevents bug where a null/random character was added to the beginning -- I'm guessing it's the eof bit
//     if (c == 0 or fin.bad()) return false;

//     //add character to output file starting from the end of the input file
//     fout << c;

//     return true;
// }


//added 2023/03/22
bool rCopy(const string &inputFile, const string &outputFile, ifstream &fin, ofstream &fout) {
    
    char c;
    
    if (fin.get(c)) {
        rCopy(inputFile, outputFile, fin, fout);
    }
    else {
        return false; //don't add to file if something failed
    }
    fout << c;
    return true; //return true if copy was completed
}