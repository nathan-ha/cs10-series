//Creates a bunch of random numbers in csv file (used for testing main.cpp)

#include <fstream>
#include <cstdlib>

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main() {

    int max = 100000;
    int min = -max;

    ofstream fout;
    fout.open("data3.csv");

    for (int j = 0; j < 300; j++) {

        for (int i = 0; i < 100; i++) {
            fout << fRand(min, max) << ',';
        }

        fout << endl;
    }
    fout << fRand(0, 100000);


    fout.close();
    return 0;
}