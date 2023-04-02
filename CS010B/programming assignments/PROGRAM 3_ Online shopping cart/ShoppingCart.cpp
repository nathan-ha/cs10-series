#include <iostream>
#include "ShoppingCart.h"

using namespace std;

ShoppingCart::ShoppingCart() {
    _customerName = "none";
    _currentDate = "January 1, 2016";
    vector <ItemToPurchase> _cartItems;
}

ShoppingCart::ShoppingCart(string customerName, string date) {
    _customerName = customerName;
    _currentDate = date;
    vector <ItemToPurchase> _cartItems;
}

void ShoppingCart::addItem(ItemToPurchase &item) {
    _cartItems.push_back(item);
}

void ShoppingCart::removeItem(string name) {
    //makes a temp vector and copies every item except for the item with the specific name
    vector<ItemToPurchase> temp;
    bool found = false;

    for (auto &cartItem : _cartItems) {
        if (cartItem.name() != name) {
            temp.push_back(cartItem);
        }
        else {
            found = true;
        }
    }

    if (not found) {
        cout << "Item not found in cart. Nothing removed." << endl;
    }
    else {
        _cartItems = temp;
    }
    cout << endl;
}

void ShoppingCart::modifyItem(ItemToPurchase &item) {
    bool found = false;

    for (auto &cartItem : _cartItems) {

        if (cartItem.name() == item.name()) {
            found = true;

            //check for default description, price, and quantity.
            if (item.description() != "none") {
                cartItem.setDescription(item.description());
            }

            if (item.price() != 0) {
                cartItem.setPrice(item.price());
            }

            if (item.quantity() != 0) {
                cartItem.setQuantity(item.quantity());
            }
        }

    }

    if (not found) {
        cout << "Item not found in cart. Nothing modified." << endl;
    }

    cout << endl;
}

string ShoppingCart::customerName() const {
    return _customerName;
}

string ShoppingCart::date() const {
    return _currentDate;
}

int ShoppingCart::numItemsInCart() const {
    int total = 0;

    for (auto &cartItem : _cartItems) {
        total += cartItem.quantity();
    }

    return total;
}

int ShoppingCart::costOfCart() const {
    int total = 0;

    for (auto &cartItem : _cartItems) {
        total += cartItem.quantity() * cartItem.price();
    }

    return total;
}

void ShoppingCart::printTotal() {
    if (numItemsInCart() > 0) {
        cout
            << _customerName + "'s Shopping Cart - " + _currentDate << endl
            << "Number of Items: " << numItemsInCart() << endl
            << endl;

        for (auto &cartItem : _cartItems) {
            cartItem.printItemCost();
        }

        cout << endl
             << "Total: $" << costOfCart() << endl;
    }
    else {
        cout 
            << _customerName + "'s Shopping Cart - " + _currentDate << endl
            << "Number of Items: 0\n\n"
            << "SHOPPING CART IS EMPTY\n\n"
            << "Total: $0\n";
    }
    cout << endl;
}

void ShoppingCart::printDescriptions() {
    cout 
        << _customerName + "'s Shopping Cart - " + _currentDate << endl
        << endl
        << "Item Descriptions\n";

    for (auto &cartItem : _cartItems) {
        cartItem.printItemDescription();
    }

    cout << endl;
}
