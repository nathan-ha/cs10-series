#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile;
   vector<int> nums;
   string temp;
   int average = 0;
   
   // Assign to inputFile value of 2nd command line argument
   inputFile = argv[1];
   // Assign to outputFile value of 3rd command line argument
   outputFile = argv[2];
   // Create input stream and open input csv file.
   ifstream fin;
   fin.open(inputFile);
   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if (fin.fail()) {
      cout << "Error when opening " << inputFile << endl;
      return 1;
   }
   // Read in integers from input file to vector.
   while (getline(fin, temp, ',')) {
      //i have no idea how else to convert string to ints so i used stoi() from the string library
      nums.push_back(stoi(temp));
   }

   

   // for (unsigned int i = 0; i < nums.size(); i++) {
   //    cout << "TEST " << nums.at(i) << endl;
   // }

   // Close input stream.
   fin.close();
   
   // Get integer average of all values read in.
   for (unsigned int i = 0; i < nums.size(); i++) {
      average += nums.at(i);
      // cout << "test " << nums.at(i) << endl;
   }
   average /= nums.size();

   // for (unsigned int i = 0; i < nums.size() - 1; i++) {
   //    cout << "TEST " << nums.at(i) << endl;
   // }
   
   // Convert each value within vector to be the difference between the original value and the average.
   for (unsigned int i = 0; i < nums.size(); i++) {
      nums.at(i) -= average;
   }
   

   // for (unsigned int i = 0; i < nums.size() - 1; i++) {
   //    cout << "TEST " << nums.at(i) << endl;
   // }

   
   // Create output stream and open/create output csv file.

   ofstream fout;

   fout.open(outputFile);

   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if (fout.fail()) {
      cout << "Error when opening " << outputFile << endl;
      return 1;
   }
   
   // Write converted values into ouptut csv file, each integer separated by a comma.
   for (unsigned int i = 0; i < nums.size() - 1; i++) {
      fout << nums.at(i) << ',';
   }
   fout << nums.at(nums.size() - 1) << endl;
   
   // Close output stream.

   fout.close();
   
   return 0;
}