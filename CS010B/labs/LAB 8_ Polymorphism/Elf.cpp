#include "Elf.h"
#include <iostream>

using namespace std;

Elf::Elf(const string &name, double health, double attackStrength, const string &familyName) :
    Character(ELF, name, health, attackStrength),
    familyName_(familyName)
{}

void Elf::attack(Character &enemy) {
    if (enemy.getType() == ELF) {
        Elf& enemyElf = dynamic_cast<Elf &>(enemy);
        if (enemyElf.familyName_ == familyName_) {
            cout << "Elf " << name << " does not attack Elf " << enemyElf.name << ".\nThey are both members of the " << familyName_ << " family.\n";
            return;
        }
    }
    enemy.damage(attackStrength * health / MAX_HEALTH);
    cout << "Elf " << name << " shoots an arrow at " << enemy.getName() << " --- TWANG!!" << endl
         << enemy.getName() << " takes " << (attackStrength * health / MAX_HEALTH) << " damage." << endl; 
}