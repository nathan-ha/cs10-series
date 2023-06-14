#include <cstdlib>
#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std;


void merge(int arr[], int left, int middle, int right);
void merge_sort(int arr[], int left, int right);


int main() {

    const int size = 50000;

    // create array of random ints
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }

    auto start = chrono::high_resolution_clock::now();
    merge_sort(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "time to sort (microseconds): " << elapsed_time.count() << endl;

    // for (int i = size; i > 0; i--) cout << arr[i - 1] << endl;

    return 0;
}

void merge(int input_arr[], int left, int middle, int right)
{
    int left_index = left;
    int right_index = middle + 1;
    int merge_position = 0;
    int merge_size = right - left + 1;

    int *merge_array = new int[merge_size];

    while (left_index <= middle && right_index <= right) {

        if (input_arr[left_index] < input_arr[right_index]) {
            merge_array[merge_position++] = input_arr[left_index++];
            // left_index++;
            // merge_position++;
        }
        else {
            merge_array[merge_position++] = input_arr[right_index++];
            // right_index++;
            // merge_position++;
        }

    }
    // if any items remain, add them in 
    // (they are guaranteed to be larger than everything inside the array at that point)
    while (left_index <= middle) {
        merge_array[merge_position] = input_arr[left_index];
        left_index++;
        merge_position++;
    }
    while (right_index <= right) {
        merge_array[merge_position] = input_arr[right_index];
        right_index++;
        merge_position++;
    }

    // copy temp array into real array
    for (int i = 0; i < merge_size; i++) {
        input_arr[left + i] = merge_array[i]; 
    }

    delete[] merge_array;
}

void merge_sort(int arr[], int left, int right) {
    if (left >= right) return;

    int middle = (left + right) / 2;

    merge_sort(arr, left, middle);
    merge_sort(arr, middle + 1, right);

    merge(arr, left, middle, right);
}