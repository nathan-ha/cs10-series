#include "Warrior.h"
#include <iostream>

using namespace std;

Warrior::Warrior(const string &name, double health, double attackStrength, const string &allegiance) :
    Character(WARRIOR, name, health, attackStrength),
    allegiance_(allegiance)
{}

void Warrior::attack(Character &enemy) {
    if (enemy.getType() == WARRIOR) {
        Warrior& enemyWarrior = dynamic_cast<Warrior&>(enemy);
        if (enemyWarrior.allegiance_ == allegiance_) {
            cout << "Warrior " << name << " does not attack Warrior " << enemyWarrior.name << ".\n"
                 << "They share an allegiance with " << allegiance_ << ".\n";
            return;
        }
    }
    enemy.damage(attackStrength * health / MAX_HEALTH);

    cout << "Warrior " << name << " attacks " << enemy.getName() << " --- SLASH!!" << endl
         << enemy.getName() << " takes " << (attackStrength * health / MAX_HEALTH) << " damage." << endl; 
}