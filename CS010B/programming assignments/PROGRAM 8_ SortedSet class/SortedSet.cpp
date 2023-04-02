#include "SortedSet.h"

//contructors & destructor
SortedSet::SortedSet() :
    IntList()
{}

SortedSet::SortedSet(const SortedSet &originalSet) :
    IntList(originalSet)
{}

SortedSet::SortedSet(const IntList &originalList) :
    IntList(originalList)
{
    remove_duplicates();
    selection_sort();
}

SortedSet::~SortedSet() {
    //TODO idk what to do here
    //for now, I just copied the destructor from IntList
    IntNode* p = head;
    //deletes the contents of p and points it to the next node/link
    while (p != nullptr) {
        IntNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

//accessors
bool SortedSet::in(int value) const {
    for (IntNode* p = head; p != nullptr; p = p->next) {
        if (p->value == value) {
            return true;
        }
    }
    return false;
}

SortedSet SortedSet::operator|(const SortedSet &rhs) const { //union
    IntList unionSet; //TODO: change this to a SortedSet later on-- maybe?
    //dumps the values from both lists into the new one and then the constructor removes duplicates and sorts it
    for (IntNode* p = head; p != nullptr; p = p->next) {
        unionSet.push_back(p->value);
    }
    for (IntNode* p = rhs.head; p != nullptr; p = p->next) {
        unionSet.push_back(p->value);
    }

    return SortedSet(unionSet); //the constructor sorts and removes duplicates
}

SortedSet SortedSet::operator&(const SortedSet &rhs) const { //intersection
    IntList intersectionSet;
    for (IntNode* p = head; p != nullptr; p = p->next) {
        //only inserts the value if both lists contain it
        if (rhs.in(p->value)) { 
            intersectionSet.push_back(p->value);
        }
    }
    return SortedSet(intersectionSet);
}

//mutators

//basically the same as the IntList::insert_ordered(), except some added conditions that check for duplicates
void SortedSet::add(int value) {

    //first four conditions are edge cases
    if (empty()) {
        IntList::push_front(value);
    }
    else if (head->value == value || tail->value == value ) {
        return;
    }
    else if (value < head->value) {
        IntList::push_front(value);
    }
    else if (value > tail->value) {
        IntList::push_back(value);
    }
    else {
        for (IntNode* p = head; p != nullptr; p = p->next) {

            if (p->next->value == value) {
                return;
            }
            else if (p->next->value > value) {
                IntNode* newNode = new IntNode(value);
                newNode->next = p->next;
                p->next = newNode;
                return; //we only need to insert one value
            }
            
        }
    }
}

//I guess these next three functions are just alternatives for add()
void SortedSet::push_front(int value) {
    add(value);
}
void SortedSet::push_back(int value) {
    add(value);
}
void SortedSet::insert_ordered(int value) {
    add(value);
}

SortedSet SortedSet::operator|=(const SortedSet &rhs) {
    *this = *this | rhs; //supposed to assign the lhs to the union of itself and the rhs and also return that set
    return *this;
}

SortedSet SortedSet::operator&=(const SortedSet &rhs) {
    *this = *this & rhs;
    return *this;
}