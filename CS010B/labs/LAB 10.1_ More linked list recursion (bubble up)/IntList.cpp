#include "IntList.h"

bool IntList::bubbleUp() {
   return bubbleUp(head);
}

/* Plan: 
   base case: reached last element
   go to back of list
   only return true when the next element is smaller
   chain bools and swap every element that returns true (every element preceding the smallest one is swapped)
*/

bool IntList::bubbleUp(IntNode *curr) {
   //base case: reached last element or list is empty
   if (curr == nullptr || curr->next == nullptr) {
      return false;
   }
   //memory contraints aside, we need to have to store the recursive step in a variable because:
   //swapping values will actually mess with the minimum value checking
   //we need to "start" at the back of the list, so do recursion first
   bool hasSmaller = bubbleUp(curr->next);

   if (curr->next->value < curr->value) {
      //swap values
      int temp = curr->next->value;
      curr->next->value = curr->value;
      curr->value = temp;

      return true || hasSmaller;
   }

   return false || hasSmaller;
}

