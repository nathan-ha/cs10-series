#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double , const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);
int contains(double, const vector<double> &); //checks if vector contains an element and returns the first index where it's found, return -1 if not found

int main(int argc, char* argv[]) {

    // cout << "TEST PROGRAM STARTS\n";

    string fileName;
    vector<double> flightPathAngles; //flight-path angle
    vector<double>  coefficientsOfLift; //coefficient of lift
    double userAngle;
    //int index;
    string userInput;

    fileName = argv[1];

    // cout << "TEST 1\n";

    readData(fileName, flightPathAngles, coefficientsOfLift);

    // if (flightPathAngles.size() == 0 || coefficientsOfLift.size() == 0) {
    //     cout << "File cannot be blank" << endl;
    //     return 1;
    // }

    if (!isOrdered(flightPathAngles)) {
        reorder(flightPathAngles, coefficientsOfLift);
    }

    //cout << "TEST " << flightPathAngles.size() << endl;

    // cout << "TEST 2\n";

    // for (int i = 0; i < flightPathAngles.size(); i++) {
    //     cout << "TEST A " << flightPathAngles.at(i) << endl; 
    // }

    // for (int i = 0; i < coefficientsOfLift.size(); i++) {
    //     cout << "TEST K " << coefficientsOfLift.at(i) << endl; 
    // }

    do {

        cout << "Input a flight-path angle:" << endl;
        cin >> userAngle;

        //index = contains(userAngle, flightPathAngles);

        //checks if the file already contains the angle and returns that coefficient, otherwise program will calculate it
        // if (index == -1) {
        //     cout << interpolation(userAngle, flightPathAngles, coefficientsOfLift) << endl;
        // }
        // else {
        //     cout << coefficientsOfLift.at(index) << endl; 
        // }

        if (flightPathAngles.at(0) <= userAngle && userAngle <= flightPathAngles.back()) {

            cout << interpolation(userAngle, flightPathAngles, coefficientsOfLift) << endl;
        }
        else {
            cout << "Error: Out of bounds" << endl;
        }

        cout << "Do you want to enter another flight-path angle? (type \"Yes\" to enter another value)" << endl; 
        cin >> userInput;

    } while (userInput == "Yes"); //FIXME: change "0" to "Yes" and "!=" to "=="


    return 0;
}

void readData(const string &fileName, vector<double> &flightPathAngles, vector<double> &coefficientsOfLift) {
    
    double temp;
    ifstream fin;

    fin.open(fileName);

    if (fin.fail()) {
        cout << "Error opening " << fileName << endl;
        exit(1);
    }

    // cout << "TEST 3\n";

    while (fin >> temp) {

        //fin >> temp;

        //if (fin.fail()) exit(1);
        //cout << "test " << temp << endl;
        flightPathAngles.push_back(temp);
        //cout << temp << endl;
        fin >> temp;
        coefficientsOfLift.push_back(temp);
        //cout << "test " << temp << endl;
    }

    fin.close();
}

bool isOrdered(const vector<double> &v) {
    //check if in ascending order
    for (unsigned int i = 0; i < v.size() - 1 && v.size() > 0; i++) {

        if (v.at(i) > v.at(i + 1)) {
            //cout << "test\n";
            return false;
        }

    }
    return true;
}

void reorder(vector<double> &flightPathAngles, vector<double> &coefficientsOfLift) {

    //im using bubble sort because it easy (and we never learned how to sort vectors?)
    double temp;
    double temp2;

    for (unsigned int i = 0; i < flightPathAngles.size(); i++) {

        for (unsigned int j = 0; j < flightPathAngles.size() - i - 1; j++) {

            if (flightPathAngles.at(j) > flightPathAngles.at(j + 1)) {

                temp = flightPathAngles.at(j);
                flightPathAngles.at(j) = flightPathAngles.at(j + 1);
                flightPathAngles.at(j + 1) = temp;

                //have to also change the order of the parallel(coefficient) vector
                temp2 = coefficientsOfLift.at(j);
                coefficientsOfLift.at(j) = coefficientsOfLift.at(j + 1);
                coefficientsOfLift.at(j + 1) = temp2;
            }

        }
    }
}

int contains(double userNum, const vector<double> &v) {
    for (unsigned int i = 0; i < v.size(); i++) {

        if (v.at(i) == userNum) {
            return i;
        }

    }
    return -1;
}


double interpolation(double b, const vector<double> &flightPathAngles, const vector<double> &coefficientsOfLift) {
    /* From Zybooks:
    a < b < c 
    such that |c-a| is minimal 
    (i.e. a is the largest angle in the dataset strictly less than b,
    and c is the smallest angle in the dataset strictly greater than b).
    */

    double a = flightPathAngles.at(0);
    double c = flightPathAngles.back();
    double aIndex;
    double cIndex;
    int index = contains(b, flightPathAngles); //used for determining if and where the element already exists


        // if (!(flightPathAngles.at(0) < b && b < flightPathAngles.back())) {
        //     exit(1);
        // }

    
        
        if (index == -1) {
            for (unsigned int i = 0; i < flightPathAngles.size(); i++) {
                // a is the largest angle in the dataset strictly less than b
                if (flightPathAngles.at(i) > a && flightPathAngles.at(i) < b) {
                    a = flightPathAngles.at(i);
                    aIndex = i;
                }
                //c is the smallest angle in the dataset strictly greater than b
                if (flightPathAngles.at(i) < c && flightPathAngles.at(i) > b) {
                    c = flightPathAngles.at(i);
                    cIndex = i;
                }
            }
            //From zybooks:
            //f(b) = f(a) + ((b - a)/(c - a))(f(c) - f(a))
            //in this case, f(x) = coefficientsOfLift.at(x)
            // return c;
            return coefficientsOfLift.at(aIndex) + ((b - a) / (c - a)) * (coefficientsOfLift.at(cIndex) - coefficientsOfLift.at(aIndex));
        }
        else {
            return coefficientsOfLift.at(index);
        }

    }
