#pragma once
#include "Character.h"

class Warrior : public Character {
private:
    string allegiance_;
public:
    Warrior(const string &name, double health, double attackStrength, const string &allegiance);
 	void attack(Character &);

};