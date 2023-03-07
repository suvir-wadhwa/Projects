//
// Created by Suvir Wadhwa on 02/11/21.
//

#include <vector>
#include <iostream>
#include <string>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {

    Warrior::Warrior(const string &warr_name, double warr_strength)
            : name(warr_name), strength(warr_strength) {}

// Enables Noble to check if warrior already has noble.
    bool Warrior::getNoble() const { return noble; }

// Enables Noble to link to a warrior
    void Warrior::setNoble(bool exist, Noble *nob_pointer) {
        noble = exist;
        nob = nob_pointer;
    }
// enables noble to get a warriors strength

    double Warrior::getStrength() const { return strength; }

// enables Noble to set a warriors strength
    void Warrior::setStrength(double stren) {
        strength = stren;
    }

    void Warrior::setDead() {
        dead = true;
    }

    const string &Warrior::getName() const { return name; }

    void Warrior::runaway() {
        if (nob != nullptr) {
            cout << name << " flees in terror, abandoning his lord, " << nob->getName() << endl;
            noble = false;
            nob->remove_warrior(this);
            nob = nullptr;
        }
    }

    bool Warrior::isHired() const { return noble; }

    ostream &operator<<(ostream &os,
                        const Warrior &warr) { // Output operator for Warrior
        os << "\t" << warr.name << ": " << warr.strength << endl;
        return os;
    }

}