#include <iostream>
#include <limits>
#include "BSTree.h"

using namespace std;

void printOrders(BSTree* tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << "Inorder = ";
  tree->inOrder( );
  cout << "Postorder = ";
  tree->postOrder( );
}

int menu() {
    int choice = 0;
    cout << endl << "Enter menu choice: ";
    cout << endl;
    cout 
        << "1. Insert" << endl
        << "2. Remove" << endl
        << "3. Print" << endl
        << "4. Search" << endl
        << "5. Smallest" << endl
        << "6. Largest" << endl
        << "7. Height" << endl
        << "8. Quit" << endl;
    // fix buffer just in case non-numeric choice entered
    // also gets rid of newline character
    cin >> choice;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main( ) {
    BSTree tree;

    int choice = menu();

    string entry;
  
    while (choice != 8) {
    try {
        if (choice == 1) {
            cout << "Enter string to insert: \n";
            string input;
            if (getline(cin, input)) {
                tree.insert(input);
            } else {
                throw runtime_error("bad input");
            }
        } else if (choice == 2) {
            cout << "Enter string to remove: \n";
            string input;
            if (getline(cin, input)) {
                tree.remove(input);
            } else {
                throw runtime_error("bad input");
            }
        } else if (choice == 3) {
            printOrders(&tree);
        } else if (choice == 4) {
            cout << "Enter string to search for: \n";
            string input;
            if (getline(cin, input)) {
                if (tree.search(input)) {
                    cout << "Found\n";
                } else {
                    cout << "Not Found\n";
                }
            } else {
                throw runtime_error("bad input");
            }
        } else if (choice == 5) {
            cout << "Smallest: " << tree.smallest() << endl;
        } else if (choice == 6) {
            cout << "Largest: " << tree.largest() << endl;
        } else if (choice == 7) {
            cout << "Enter string: \n";
            string input;
            if (getline(cin, input)) {
                cout << "Height of subtree rooted at " << input << ": " << tree.height(input) << endl;
            } else {
                throw runtime_error("bad input");
            }
        }   
        //fix buffer just in case non-numeric choice entered
        choice = menu();
    }
    catch (...) {
        //can't actually do anything with the exceptions since it breaks zybooks
        choice = menu();
    }
    }
    return 0;
}

