#include "Wizard.h"
#include <iostream>

using namespace std;

Wizard::Wizard(const string &name, double health, double attackStrength, int rank) :
    Character(WIZARD, name, health, attackStrength),
    rank_(rank)
{}

void Wizard::attack(Character &enemy) {
    if (enemy.getType() == WIZARD) {
        Wizard& enemyWizard = dynamic_cast<Wizard &>(enemy);
        enemyWizard.damage(attackStrength * rank_ / enemyWizard.rank_);

        cout << "Wizard " << name << " attacks " << enemy.getName() << " --- POOF!!" << endl
             << enemy.getName() << " takes " << (attackStrength * rank_ / enemyWizard.rank_) << " damage." << endl; 
    }
    else {
        enemy.damage(attackStrength);
        cout << "Wizard " << name << " attacks " << enemy.getName() << " --- POOF!!" << endl
             << enemy.getName() << " takes " << (attackStrength) << " damage." << endl; 
    }
}