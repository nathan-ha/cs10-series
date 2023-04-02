#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <string>
#include <vector>
#include "ItemToPurchase.h"

class ShoppingCart {
    private:

        std::string _customerName;
        std::string _currentDate;
        std::vector <ItemToPurchase> _cartItems;

    public:

        ShoppingCart();
        ShoppingCart(std::string customerName, std::string date);

        void addItem(ItemToPurchase &item);
        void removeItem(std::string name);
        void modifyItem(ItemToPurchase &item);

        std::string customerName() const;
        std::string date() const;

        int numItemsInCart() const;
        int costOfCart() const;

        void printTotal();
        void printDescriptions();

};

#endif