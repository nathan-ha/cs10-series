#pragma once
#include "Character.h"

class Elf : public Character {
private:
    string familyName_;
public:
    Elf(const string &name, double health, double attackStrength, const string &familyName);
 	void attack(Character &);
};