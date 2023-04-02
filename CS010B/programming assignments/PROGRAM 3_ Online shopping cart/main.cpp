#include "ItemToPurchase.h"
#include "ShoppingCart.h"
#include <iostream>

using namespace std;

void printMenu(ShoppingCart &cart);

int main() {

    string name, date;

    cout << "Enter customer's name: ";
    getline(cin, name);
    cout << endl;
    cout << "Enter today's date: ";
    getline(cin, date);
    cout 
        << endl
        << endl;
    cout 
        << "Customer name: " + name << endl
        << "Today's date: "  + date << endl
        << endl;
    //rip
    ShoppingCart cart(name, date);

    printMenu(cart);

    return 0;
}

void printMenu(ShoppingCart &cart) {
    char option = 0;
    string name;
    string description;
    int price;
    int quantity;

    while (option != 'q') {
        ItemToPurchase tempItem;
            cout
                << "MENU\n"
                << "a - Add item to cart\n"
                << "d - Remove item from cart\n"
                << "c - Change item quantity\n"
                << "i - Output items' descriptions\n"
                << "o - Output shopping cart\n"
                << "q - Quit\n\n"
                << "Choose an option: ";
            cout << endl;

        cin >> option;

        while (option != 'a' && option != 'd' && option != 'c' &&  option != 'i' &&  option != 'o' && option != 'q') {
            cout << "Choose an option: \n";
            cin >> option;     
        }

        if (option == 'o') {
            cout << "\nOUTPUT SHOPPING CART\n";
            cart.printTotal();

        }
        else if (option == 'i') {
            cout << "\nOUTPUT ITEMS' DESCRIPTIONS\n";
            cart.printDescriptions();
            // cout << cart.customerName() << "test" << endl;

        }
        else if (option == 'a') {
            cout
                << "\nADD ITEM TO CART\n"
                << "Enter the item name: \n";
                
            cin.ignore(); //flushes the cin buffer because getline kept being skipped (i guess it got full?)
            getline(cin, name);
            tempItem.setName(name);

            // cout << "TEST " << name << endl;

            cout << "Enter the item description: \n";
            // cin.ignore();  //this kept making the first letter get cut off for some reason
            getline(cin, description);
            tempItem.setDescription(description);
            // cout << "TEST " << description << endl;

            cout << "Enter the item price: \n";
            cin >> price;
            tempItem.setPrice(price);

            cout << "Enter the item quantity: \n";
            cin >> quantity;
            tempItem.setQuantity(quantity);
            
            cart.addItem(tempItem);

            cout << endl;

        } 
        else if (option == 'd') {
            cout
                << "\nREMOVE ITEM FROM CART\n"
                << "Enter name of item to remove: \n";
            cin.ignore();   
            getline(cin, name);

            cart.removeItem(name);

        }
        else if (option == 'c') {
            cout
                << "\nCHANGE ITEM QUANTITY\n"
                << "Enter the item name: \n";
            
            cin.ignore();
            getline(cin, name);
            cout << "Enter the new quantity: \n";
            cin >> quantity;

            tempItem.setName(name);
            tempItem.setQuantity(quantity);

            cart.modifyItem(tempItem);
        }    
    }
}