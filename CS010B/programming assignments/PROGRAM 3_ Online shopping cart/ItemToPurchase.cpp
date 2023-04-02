#include <iostream>
#include "ItemToPurchase.h"

using namespace std;

ItemToPurchase::ItemToPurchase() {
    _name = "none";
    _description = "none";
    _price = 0;
    _quantity = 0;
}

ItemToPurchase::ItemToPurchase(string name, string description, int price = 0, int quantity = 0) {
    _name = name;
    _description = description;
    _price = price;
    _quantity = quantity;
}

void ItemToPurchase::setName(string s) {
    _name = s;
}

string ItemToPurchase::name() const {
    return _name;
}

void ItemToPurchase::setPrice(int p) {
    _price = p;
}

int ItemToPurchase::price() const {
    return _price;
}

void ItemToPurchase::setQuantity(int q) {
    _quantity = q;
}

int ItemToPurchase::quantity() const {
    return _quantity;
}

void ItemToPurchase::setDescription(string d) {
    _description = d;
}

void ItemToPurchase::printItemCost() const {
    cout << _name << ' ' << _quantity << " @ $" << _price << " = $" << (_quantity * _price) << endl;
}

string ItemToPurchase::description() const {
    return _description;
}

void ItemToPurchase::printItemDescription() const {
    cout << _name << ": " << _description << endl;
}