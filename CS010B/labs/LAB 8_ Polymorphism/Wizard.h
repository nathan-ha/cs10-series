#pragma once
#include "Character.h"

class Wizard : public Character {
private:
    int rank_;
public:
    Wizard(const string &name, double health, double attackStrength, int rank);
 	void attack(Character &);
};