#include "IntList.h"

IntList::IntList() : 
    head(nullptr),
    tail(nullptr)
{
}   

IntList::~IntList() {
    // while (not empty()) {
    //     pop_front();
    // }
    IntNode* p = head;

    //deletes the contents of p and points it to the next node/link
    while (p != nullptr) {
        IntNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }

    // this might work
    // for (IntNode* p = head; p != nullptr; p = p->next) {
    //     delete p;
    // }

    head = nullptr;
    tail = nullptr;
}

bool IntList::empty() const {
    return head == nullptr;
}

//make new node, point the 'next' to (old) head, and set the new head to n, pushing it to front
void IntList::push_front(int value) {
    IntNode* newHead = new IntNode(value);

    newHead->next = head;
    head = newHead;
    
    //makes the tail equal to the head if there is only one node (i.e. head)
    if (tail == nullptr) {
        tail = newHead;
    }
    //no need to delete newHead since it was added to the list
}

void IntList::push_back(int value) {
    IntNode* newTail = new IntNode(value);

    //if the list is empty, then initialize head and tail to the first node
    if (empty()) {
        head = newTail;
        tail = newTail;
    }
    else {
        //connects the last two elements and points tail to the new last element
        tail->next = newTail;
        tail = newTail;
        //new tail should already be pointing to nullptr by default
    }
}

void IntList::pop_front() {
    if (empty()) return;

    IntNode* victim = head;
    head = head->next; //set head to the next node
    delete victim; //delete the old head

    if (empty()) {
        tail = nullptr; //if there's nothing in the list, make tail and head nullptr
        head = nullptr;
    }

}

void IntList::selection_sort() {
    if (empty()) return;

    //start at beginning, find smallest thing in the list, and swap them, then move on
    for (IntNode* p = head; p->next != nullptr; p = p->next) {
        IntNode* min = p;

        for (IntNode* q = p->next; q != nullptr; q = q->next) {
            if (q->value < min->value) {
                min = q;
            }
        }

        //swap smallest value and p
        auto temp = p->value; //I used auto instead of int here in case I want to ever use other datatypes and I forget to change it
        p->value = min->value;
        min->value = temp;
    }
}

const int &IntList::front() const {
    return head->value;
}

const int &IntList::back() const {
    return tail->value;
}

std::ostream &operator<<(std::ostream & out, const IntList &list) {

    if (list.empty()) return out;

    for (IntNode* p = list.head; p->next != nullptr; p = p->next) { //iterates through list until it gets to the element before the tail
        out << p->value << ' ';
    }
    out << list.tail->value;

    return out;
}

IntList::IntList(const IntList &origList) { //copy constructor
    //no need to delete any values because this list did not exist before this constructor (list already existing is handled by the assignment(=) opertator overload)
    head = nullptr;
    tail = nullptr;
    
    for (IntNode* p = origList.head; p != nullptr; p = p->next) {
        push_back(p->value);
    }

}

IntList &IntList::operator=(const IntList &rhs) {
    
    if (this != &rhs) { //check if the list is being assigned to itself
        clear(); //don't want to push back on top of existing values

        for (IntNode* p = rhs.head; p != nullptr; p = p->next) {
            push_back(p->value);
        }
    }

    return *this;
}

void IntList::clear() {

    for (IntNode* p = head; p != nullptr;) {
        IntNode* victim = p;
        p = p->next;
        delete victim;
    }

    head = nullptr;
    tail = nullptr;
}

void IntList::insert_ordered(int value) {

    if (empty() || value <= head->value) { //if the list is empty, add the value; or if the new value is going to be the smallest value, push it to the front anyways
        push_front(value);
    }
    else if (value >= tail->value) {
        push_back(value);
    }
    else {

        for (IntNode* p = head; p != nullptr; p = p->next) { //insert to middle of list

            if (p->next->value >= value) { //if the next value is greater than value, then insert value before it
                IntNode* newNode = new IntNode(value);

                newNode->next = p->next;
                p->next = newNode;
                break; //we only need to insert one value
            }

        }

    }
}

void IntList::remove_duplicates() {

    for (IntNode* p = head; p != nullptr; p = p->next) { //check each node p against all nodes after it, q
        IntNode* pre_q = p; //tracks the node directly before q

        for (IntNode* q = p->next; q != nullptr;) {

            if (p->value == q->value) { //if duplicate is found, delete the duplicate node and connect the two nodes around it
                IntNode* victim = q;

                q = q->next;
                delete victim;
                pre_q->next = q;

                if (q == nullptr) {
                    tail = pre_q; //set the tail to the new last element if the last element is removed
                    tail->next = nullptr; //just to be safe
                }

            }
            else { //without this else statement, q will get incremented twice every time a duplicate is found (since q = q->next is called above), causing every other duplicate to be skipped
                q = q->next;
                pre_q = pre_q->next; 
                //pre_q is only allowed to move when no dupes are found because then it does some weird stuff
                //I'm guessing because pre_q will then traverse the deleted nodes and keep them linked it to the list
                //so holding pre_q back prevents this
            }
       }
    }

}

//added later for practice: March 15, 2023
void IntList::remove_max() {
    if (empty()) return;
    //find max
    int max = head->value;
    for (IntNode* p = head; p != nullptr; p = p->next) {
        if (p->value > max) max = p->value;
    }

    /*assuming we want to remove all occurrences of max*/

    //remove from beginning
    while (head->value == max) {
        IntNode* victim = head;
        head = head->next;
        delete victim;
        if (empty()) return;
    }
    
    IntNode* prev = head;
    //remove from middle
    for (IntNode* p = head->next; p->next != nullptr; p = p->next) {
        if (p->value == max) {
            IntNode* victim = p;
            p = p->next;
            prev->next = p;
            delete victim;
        }
        prev = prev->next;
    }
    //remove from end
    if (tail->value == max) {
        IntNode* victim = tail;
        tail = prev;
        prev->next = nullptr;
        delete victim;
        if (empty()) return;
    }
}