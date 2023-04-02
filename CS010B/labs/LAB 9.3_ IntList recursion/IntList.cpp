#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(nullptr) {}


void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

bool IntList::exists(IntNode *currentNode, int inputValue) const {
   //base case: end of list is reached. Returning false at this point doesn't change the outcome, but returning true would.
   if (currentNode == nullptr) {
      return false;
   } 
   else {
      //this will chain together a bunch of bools (e.g. false || false || false || true || false)
      //but only one of them needs to be true since only one element needs to equal the input value
      return (currentNode->value == inputValue) || exists(currentNode->next, inputValue);
   }
}

//basically just the other exists(), except we only search the entire list
bool IntList::exists(int inputValue) const {
   return exists(head, inputValue);
}

ostream &operator<<(ostream &out, IntNode* currentNode) {
   if (currentNode == nullptr) return out; //in case the list is empty

   //base case: last element of list is reached
   if (currentNode->next == nullptr) {
      return out << currentNode->value; //outputting the last value here (instead of in recursive line) since we don't want a space at the end
   }
   else {
      return out << currentNode->value << ' ' << currentNode->next;
   }
}

//same as the helper function, but it starts with the head by default
ostream & operator<<(ostream &out, const IntList &list) {
   return out << list.head;
}