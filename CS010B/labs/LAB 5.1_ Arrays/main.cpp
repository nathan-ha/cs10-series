//include any standard libraries needed
#include <fstream>
#include <iostream>

using namespace std;

//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize);

//  - Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index);


// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize);


const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
   ifstream fin;
   int usrIndex;
   int arraySize = 0;
   int i;

   // verify file name provided on command line
   // cout << "Opening File: " << argv[1] << endl;

   // open file and verify it opened
   fin.open(argv[1]);

   if (not fin.is_open()) {
      cout << "Failed to open " << argv[1] << endl;
      return 1;
   }
   // Declare an array of doubles of size ARR_CAP.
   double doubles[ARR_CAP];
    
   // Fill the array with up to ARR_CAP doubles from the file entered at the command line.

   // fin >> doubles[i];
   // arraySize++;
   for (i = 0; fin >> doubles[i] && i < ARR_CAP; i++) {
      arraySize++;
   }
   // display(doubles, arraySize);

   // Call the mean function passing it this array and output the 
   // value returned.
   cout << "Mean: " << mean(doubles, arraySize) << endl << endl;
    
   // Ask the user for the index (0 to size - 1) of the value they want to remove.
   cout << "Enter index of value to be removed (0 to " << arraySize - 1  << "):\n";
   cin >> usrIndex;
   cout << endl;
	
   // Call the display function to output the array.
   cout << "Before removing value: ";
   display(doubles, arraySize);
   cout << endl << endl;
   
   // Call the remove function to remove the value at the index
   // provided by the user.
   remove(doubles, arraySize, usrIndex);
  
    
   // Call the display function again to output the array
   // with the value removed.
   cout << "After removing value: ";
   display(doubles, arraySize);
   cout << endl << endl;

   
   // Call the mean function again to get the new mean
   cout << "Mean: " << mean(doubles, arraySize) << endl;

   
	return 0;
}

double mean(const double array[], int arraySize) {
   double total = 0;

   for (int i = 0; i < arraySize; i++) {
      total += array[i];
   }

   return total / arraySize;
}

void remove(double array[], int &arraySize, int index) {

      if (0 <= index && index <= arraySize - 1) {

         for (; index < arraySize - 1; index++) {
            array[index] = array[index + 1];
         }

         arraySize--;
   }
}

void display(const double array[], int arraySize) {
   for (int i = 0; i < arraySize - 1; i++) {
      cout << array[i] << ", ";
   }
   cout << array[arraySize - 1];
}