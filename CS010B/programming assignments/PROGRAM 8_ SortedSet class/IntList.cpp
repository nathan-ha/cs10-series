#include "IntList.h"

/*  note: I copied this file from the last PROGRAM, and removed some of the comments. 
            If you're curious why I did something a certain way,
            my last program might explain it
*/
IntList::IntList() : 
    head(nullptr),
    tail(nullptr)
{}   

IntList::~IntList() {
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
}

void IntList::push_back(int value) {
    IntNode* newTail = new IntNode(value);

    if (empty()) {
        head = newTail;
        tail = newTail;
    }
    else {
        //connects the last two elements and points tail to the new last element
        tail->next = newTail;
        tail = newTail;
    }
}

void IntList::pop_front() {
    if (empty()) return;

    IntNode* victim = head;
    head = head->next;
    delete victim;

    if (empty()) {
        tail = nullptr;
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
        auto temp = p->value;
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

    for (IntNode* p = list.head; p->next != nullptr; p = p->next) {
        out << p->value << ' ';
    }
    out << list.tail->value;

    return out;
}

//copy constructor
IntList::IntList(const IntList &origList) { 
    //no need to delete any values because this list did not exist before this constructor (list already existing is handled by the assignment(=) opertator overload)
    head = nullptr;
    tail = nullptr;
    
    for (IntNode* p = origList.head; p != nullptr; p = p->next) {
        push_back(p->value);
    }

}

IntList &IntList::operator=(const IntList &rhs) {
     //check if the list is being assigned to itself and remove any existing values before copying
    if (this != &rhs) {
        clear();

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
     //if the list is empty, add the value; or if the new value is going to be the smallest value, push it to the front anyways
    if (empty() || value <= head->value) {
        push_front(value);
    }
    else if (value >= tail->value) {
        push_back(value);
    }
    else {

        for (IntNode* p = head; p != nullptr; p = p->next) { //insert to middle of list
            //if the next value is greater than value, then insert value before it
            if (p->next->value >= value) { 
                IntNode* newNode = new IntNode(value);

                newNode->next = p->next;
                p->next = newNode;
                break; //we only need to insert one value
            }

        }

    }
}

void IntList::remove_duplicates() {
    //check each node p against all nodes after it, q
    for (IntNode* p = head; p != nullptr; p = p->next) {
        IntNode* pre_q = p; //tracks the node directly before q

        for (IntNode* q = p->next; q != nullptr;) {
            //if duplicate is found, delete the duplicate node and connect the two nodes around it
            if (p->value == q->value) {
                IntNode* victim = q;

                q = q->next;
                delete victim;
                pre_q->next = q;

                //set the tail to the new last element if the last element is removed
                if (q == nullptr) {
                    tail = pre_q;
                    tail->next = nullptr;
                }

            }
            //without this else statement, q will get incremented twice every time a duplicate is found (since q = q->next is called above), causing every other duplicate to be skipped
            else {
                q = q->next;
                pre_q = pre_q->next; 
            }
       }
    }
}