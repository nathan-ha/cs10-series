//Creates a bunch of random numbers (used for testing main.cpp)

#include <fstream>
#include <cstdlib>

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main() {

    ofstream fout;
    fout.open("tunnel3.dat");

    for (int i = 0; i < 1000; i++) {
        fout << fRand(0, 100000) << " ";
        fout << fRand(0, 100000) << " ";
        fout << std::endl;
    }


    fout.close();
    return 0;
}