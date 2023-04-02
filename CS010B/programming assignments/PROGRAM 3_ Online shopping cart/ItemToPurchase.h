#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H

#include <string>

class ItemToPurchase {
    private:

        std::string _name;
        std::string _description;
        int _price;
        int _quantity;
    
    public:

        ItemToPurchase();
        ItemToPurchase(std::string name, std::string description, int price, int quantity); 

        int price() const;
        std::string name() const;
        int quantity() const ;
        std::string description() const;

        void setName(std::string s);
        void setPrice(int p);
        void setQuantity(int p);
        void setDescription(std::string d);

        void printItemCost() const;
        void printItemDescription() const;
};

#endif