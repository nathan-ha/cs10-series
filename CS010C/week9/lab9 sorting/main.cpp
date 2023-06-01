#include <iostream>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[], int arr3[]);

void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);

int main()
{
    int nums1[NUMBERS_SIZE];
    int nums2[NUMBERS_SIZE];
    int nums3[NUMBERS_SIZE];
    fillArrays(nums1, nums2, nums3);
    cout << "testing arrays of size " << NUMBERS_SIZE << '\n';

    const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds
    //testing insertion sort time
    clock_t Start = clock();
    InsertionSort(nums3, NUMBERS_SIZE);
    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "insertion sort time: " << elapsedTime << "ms\n";

    //testing Quicksort (midpoint) time
    Start = clock();
    Quicksort_midpoint(nums1, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort (midpoint) time: " << elapsedTime << "ms\n";

    //testing Quicksort (median of three) time
    Start = clock();
    Quicksort_medianOfThree(nums1, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort (median of three) time: " << elapsedTime << "ms\n";


}

// returns a random inclusive int
int genRandInt(int low, int high)
{
    return low + rand() % (high - low + 1);
}

// fills three arrays
void fillArrays(int arr1[], int arr2[], int arr3[])
{
    for (int i = 0; i < NUMBERS_SIZE; ++i)
    {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

/*sorts the array using insertion sort
 algorithm: 
    outer loop: point to start of unsorted portion of arraay
    inner loop: shift elements to the left into its proper place in the sorted portion of the array
*/
void InsertionSort(int numbers[], int numbersSize)
{
    for (int i = 0; i < numbersSize - 1; i++)
    {
        int j = i;
        //swap elements until key is put in right place 
        while (numbers[j] > numbers[j + 1] && j >= 0)
        {
            auto swapHolder = numbers[j];
            numbers[j] = numbers[j + 1];
            numbers[j + 1] = swapHolder; 
            j--;
        }
    }
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    cout << "do Quicksort_midpoint\n";
}
void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    cout << "do Quicksort_medianOfThree\n";
}