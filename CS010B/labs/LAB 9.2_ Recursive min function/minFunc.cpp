#include "minFunc.h"

const int* min(const int arr[], int arrSize) {
    //base/edge cases: array size is 1 or 0
    if (arrSize == 1) {
        return &arr[0];
    }
    else if (arrSize <= 0) {
        return nullptr;
    }

    //the recursion goes through entire array backwards
    const int* minValuePtr = min(arr, arrSize - 1);

    //each recursive call will return the smallest value between the last element (according to arrSize) 
    //and the previous smallest one, which is tracked by min()
    if (arr[arrSize - 1] < *minValuePtr) {
        return &arr[arrSize - 1];
    }
    return minValuePtr;

}
