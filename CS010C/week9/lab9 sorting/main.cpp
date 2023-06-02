#include <iostream>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[], int arr3[]);

void Quicksort_midpoint(int numbers[], int low, int high);
void Quicksort_medianOfThree(int numbers[], int low, int high);
void InsertionSort(int numbers[], int numbersSize);
int Partition(int numbers[], int low, int high, bool usesMedianOfThree);

int main()
{
    const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds
    int nums1[NUMBERS_SIZE];
    int nums2[NUMBERS_SIZE];
    int nums3[NUMBERS_SIZE];
    fillArrays(nums1, nums2, nums3);
    cout << "testing arrays of size " << NUMBERS_SIZE << '\n';

    // testing insertion sort time
    clock_t Start = clock();
    InsertionSort(nums3, NUMBERS_SIZE);
    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "insertion sort time: " << elapsedTime << "ms\n";

    // testing Quicksort (midpoint) time
    Start = clock();
    Quicksort_midpoint(nums1, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort (midpoint) time: " << elapsedTime << "ms\n";

    // testing Quicksort (median of three) time
    Start = clock();
    Quicksort_medianOfThree(nums1, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort (median of three) time: " << elapsedTime << "ms\n";

    cout << "\ncalling sort on the sorted arrays:\n";

    // testing insertion sort time
    Start = clock();
    InsertionSort(nums3, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "insertion sort time: " << elapsedTime << "ms\n";

    // testing Quicksort (midpoint) time
    Start = clock();
    Quicksort_midpoint(nums1, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort (midpoint) time: " << elapsedTime << "ms\n";

    // testing Quicksort (median of three) time
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

/*
    sorts the array using insertion sort
    algorithm:
        outer loop: point to start of unsorted portion of arraay
        inner loop: shift elements to the left into its proper place in the sorted portion of the array
*/
void InsertionSort(int numbers[], int numbersSize)
{
    for (int i = 0; i < numbersSize - 1; i++)
    {
        int j = i;
        // swap elements until key is put in right place
        while (numbers[j] > numbers[j + 1] && j >= 0)
        {
            int swapHolder = numbers[j];
            numbers[j] = numbers[j + 1];
            numbers[j + 1] = swapHolder;
            j--;
        }
    }
}

/*
    Sorts the given array in the range from i to k using quicksort method.
    In this function, pivot is the midpoint element (numbers[(i+k)/2]).
*/
void Quicksort_midpoint(int numbers[], int low = 0, int high = NUMBERS_SIZE - 1)
{
    if (low >= high) return;
    int lowPartitionHigh = Partition(numbers, low, high, false);
    Quicksort_midpoint(numbers, low, lowPartitionHigh);
    Quicksort_midpoint(numbers, lowPartitionHigh + 1, high);
}

/*
    This quicksort is the same as the other one but uses a different pivot
    The pivot is the median of the following three values:
        leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]).
*/
void Quicksort_medianOfThree(int numbers[], int low = 0, int high = NUMBERS_SIZE - 1)
{
    if (low >= high) return;
    int lowPartitionHigh = Partition(numbers, low, high, true);
    Quicksort_midpoint(numbers, low, lowPartitionHigh);
    Quicksort_midpoint(numbers, lowPartitionHigh + 1, high);
}

/*
    Partitions array into low and high partitions. Used in quicksort.
    Returns the highest index of the low partition.
*/
int Partition(int numbers[], int low, int high, bool usesMedianOfThree)
{
    int pivotIndex = low + (high - low) / 2;
    int pivot = numbers[pivotIndex];
    if (usesMedianOfThree)
    {
        // gets the median of the first, middle, and last elements
        // uses actual black magic
        pivot = max(min(numbers[low], numbers[pivotIndex]), min(max(numbers[low], numbers[pivotIndex]), numbers[high]));
    }
    for (;;)
    {
        while (numbers[low] < pivot)
        {
            low++;
        }
        while (pivot < numbers[high])
        {
            high--;
        }
        // this is true when all elements are partitioned (0 or 1 elements remain)
        if (low >= high)
        {
            return high;
        }
        //elements smaller than pivot will be on the left, larger on the right
        int swapHolder = numbers[low];
        numbers[low] = numbers[high];
        numbers[high] = swapHolder;
        //move low and high so we don't look at the same elements again
        low++;
        high--;
    }
    throw runtime_error("partition: something went horribly wrong");
}