#include "Heap.h"
#include <iostream>

Heap::Heap(): numItems(0) {}

void Heap::enqueue(PrintJob* newJob) {
    if (numItems == MAX_HEAP_SIZE) return; //edge case: array capacity reached
    //append to array
    arr[numItems] = newJob;
    numItems++;
    //"percolate up" until max heap properties is satisfied
    int newJobIndex = numItems - 1;
    int parentIndex = (newJobIndex - 1) / 2;
    while (arr[newJobIndex]->getPriority() > arr[parentIndex]->getPriority()) { //max heap is violated when child is larger than parent
        //move the new element through the array until it gets to the right spot
        while (newJobIndex > parentIndex) {
            //keep swapping newJob, effectively inserting it at its new position
            auto temp = arr[newJobIndex];
            arr[newJobIndex] = arr[newJobIndex - 1];
            arr[newJobIndex - 1] = temp;
            newJobIndex--;
        }
        parentIndex = (newJobIndex - 1) / 2;
    }
}

void Heap::trickleDown(int root) {

    int leftChild = root * 2 + 1;
    int leftChildPriority = arr[leftChild]->getPriority();
    int rightChild = root * 2 + 2;
    int rightChildPriority = arr[rightChild]->getPriority();
    bool violatesHeap = arr[root]->getPriority() < leftChildPriority ||
                        arr[root]->getPriority() < rightChildPriority;

    //while the children are greater than the current index, swap with the greater of the two children
    while (violatesHeap) {
        if (leftChildPriority > rightChildPriority) {
            auto temp = arr[leftChild];
            arr[leftChild] = arr[root];
            arr[root] = temp;
            root = root * 2 + 1;
        } else {
            auto temp = arr[rightChild];
            arr[rightChild] = arr[root];
            arr[root] = temp;
            root = root * 2 + 2;
        }
        if (root * 2 + 2 >= numItems) return; //don't continue if you are gonna go out of bounds
        leftChild = root * 2 + 1;
        leftChildPriority = arr[leftChild]->getPriority();
        rightChild = root * 2 + 2;
        rightChildPriority = arr[rightChild]->getPriority();
        violatesHeap = arr[root]->getPriority() < leftChildPriority ||
                       arr[root]->getPriority() < rightChildPriority;
    }

}

void Heap::dequeue() {
    if (numItems == 0) return;
    //edge case: less than two children because trickledown() doesn't work if either of the children are not initialized
    if (numItems == 1) {
        numItems = 0;
        return;
    } else if (numItems == 2) {
        arr[0] = arr[1];
        numItems = 1;
        return;
    }
    //swap first and last element then trickle the new root down to the right spot
    arr[0] = arr[numItems - 1];
    numItems--;
    trickleDown(0);
}

//highest priority job will always be the first element
PrintJob* Heap::highest() {
    if (numItems == 0) return nullptr;
    return arr[0];
}

//print details about highest priority item
void Heap::print() {
    if (numItems == 0) return;
    std::cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << '\n';
}