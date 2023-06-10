#include <cstdlib>
#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std;

void heapify(int arr[], int root, int size);
void heapsort(int arr[], int size);

int main()
{

    // create array of random ints
    const int size = 10000;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand();
    }

    auto start = chrono::high_resolution_clock::now();
    heapsort(arr, size);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "time to sort (microseconds): " << elapsed_time.count() << endl;

    return 0;
}

// helps create a max heap
void heapify(int arr[], int root, int size)
{
    int left = root * 2 + 1;
    int right = root * 2 + 2;

    // get max of children and root
    int max = root;
    if (left < size && arr[left] > arr[max]) max = left;
    if (right < size && arr[right] > arr[max]) max = right;

    if (max != root)
    {
        swap(arr[max], arr[root]); // move max to root
        heapify(arr, max, size); // recursively heapify subtrees
    }
}

void heapsort(int arr[], int size)
{
    // heapify array
    int start = size / 2 - 1; // gets the last non-leaf element
    for (int i = start; i > 0; i--)
    {
        heapify(arr, i, size);
    }

    // swap biggest and last element and re-heapify, exclusing the last element
    for (size = size - 1; size > 0; size--)
    {
        swap(arr[0], arr[size]);
        heapify(arr, 0, size);
    }

}