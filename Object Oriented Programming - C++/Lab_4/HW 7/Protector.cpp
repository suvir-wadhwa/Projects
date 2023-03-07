//
// Created by Suvir Wadhwa on 18/11/21.
//
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {

    Protector::Protector(const string& prot_name, int
    prot_strength) : name(prot_name), strength(prot_strength) {}

    bool Protector::isHired() const {return lord != nullptr; }
    void Protector::setLord(Lord* myLord) {
        lord = myLord;
    }

    void Protector::runaway() {
        if (lord != nullptr) {
            cout << name << " flees in terror, abandoning "
                            "his lord, " << lord->getName() << endl;
            lord->remove_warrior(this);
            lord = nullptr;
        }
    }

    double Protector::getStrength() const { return strength; }
    void Protector::setStrength(double stren) {
        strength = stren;
    }
    bool Protector::isDead() const {return dead;}
    void Protector::setDead() {dead = true;}
    string Protector::getName() const {return name; }

    string Protector::getLordName() const {
        if (lord != nullptr) {
            return lord->getName();
        }
        return "There's no lord";
    }

    Wizard::Wizard(const string& wiz_name, int wiz_strength)
    : Protector(wiz_name, wiz_strength) {}
    void Wizard::defend() const {
        cout << "POOF" << endl;
    }

    Warrior::Warrior(const string& warr_name, int warr_strength)
    : Protector(warr_name, warr_strength) {}


    Archer::Archer(const string& arch_name, int arch_strength)
    : Warrior(arch_name, arch_strength) {}
    void Archer::defend() const {
        cout << "TWANG!  " << getName() << " says: Take that in the"
                                           " name of my lord, "
                                           << getLordName() << endl;
    }

    Swordsman::Swordsman(const string& sword_name, int sword_strength)
    : Warrior(sword_name, sword_strength) {}
    void Swordsman::defend() const  {
        cout << "CLANG!  " << getName() << " says: Take that in the"
                                           " name of my lord, " << getLordName() << endl;
    }


}