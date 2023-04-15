#include <iostream>
#include "IntList.h"
using namespace std;

int main() {
	//test constructor
	IntList list1;
	cout << "TESTING CONSTRUCTOR\n";
	cout << "empty list: " << list1 << '\n'
		 << "expected:\n\n";

	//test push front
	cout << "TESTING PUSH_FRONT()\n";
	list1.push_front(11);
	list1.push_front(22);
	list1.push_front(33);
	cout << "test push_front()\n" 
		 << "pushing 11,22,33 to list: " << list1 << '\n'
		 << "expected: 33,22,11\n\n";

	//test pop_front()
	cout << "TESTING POP_FRONT()\n";
	IntList emptyList;
	cout << "list before pop_front(): " << list1 << endl;
	cout << "popping first value: ";
	list1.pop_front();
	cout << list1 << '\n';
	cout << "expected: " << "22,11\n";
	cout << "popping until empty: " << endl;
	while (!list1.empty()) {
		list1.pop_front();
		cout << "pop: " << list1 << endl;
	}
	emptyList.pop_front();
	cout << "pop_front() on empty list: " << emptyList
		 << "\nexpected: \n\n" ;

	//test push_back()
	IntList list2;
	cout << "TESTING PUSH_BACK()\n";
	cout << "list before push_back(): " << list2 << endl;
	list2.push_back(11);
	list2.push_back(22);
	cout << "list after push_back(11) and push_back(22): " << list2 << endl
		 << "expected: 11,22\n\n";

	//test pop_back()
	cout << "TESTING POP_BACK()\n";
	emptyList.pop_back();
	cout << "pop_back() on empty list: " << emptyList
		 << "\nexpected: ";

	cout << "list before pop " << list2 << endl;
	cout << "popping last value\n";
	list2.pop_back();
	cout << "now: " << list2 << '\n';
	cout << "expected: " << "11\n";
	emptyList.pop_back();
	cout << "pop_back() on empty list: " << emptyList
		 << "\nexpected: \n\n" ;
	
	//test empty()
	cout << "TESTING EMPTY()\n"
		 << "non-empty list: " << list2
		 << "\nexpected: false\n" 
		 << "actual: " << boolalpha << list2.empty() << endl
		 << "empty list: " << emptyList << endl
		 << "expected: true\nActual: " << emptyList.empty() << endl << endl;

	//test printReverse()
	cout << "TESTING PRINTREVERSE()\n";
	IntList list3;
	for (int i = 1; i < 9; i++) {
		list3.push_back(i * 11);
	}
	cout << "Current List: " << list3 << endl;
	cout << "Reversed list: ";
	list3.printReverse();
	cout << "\nReversing empty list:\n" << endl;
	emptyList.printReverse();
	cout << "Expected nothing\n";
	

	return 0;
}
