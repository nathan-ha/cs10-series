#include <fstream>
#include <iostream>
#include <cstdlib> //needed for exit function

using namespace std;

// Place fileSum prototype (declaration) here
int fileSum(string f);

int main() {

   string filename;
   int sum = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   
   sum = fileSum(filename);

   cout << "Sum: " << sum << endl;
   
   return 0;
}

// Place fileSum implementation here
int fileSum(string f) {
   ifstream fin;
   int sum = 0;
   int temp;

   fin.open(f);

   if (fin.fail() ) {
      cout << "Error opening " << f << endl;
      exit(1);
   }

   while (fin >> temp) {
      sum += temp;
   }

   fin.close();

   return sum;
   
}