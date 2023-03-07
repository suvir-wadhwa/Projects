//
// Created by Suvir Wadhwa on 18/11/21.
//
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& noble_name) : name(noble_name) {}

    void Noble::battle(Noble &enemy) {
        cout << name << " battles " <<
             enemy.name << endl;
        if (dead && enemy.dead) {
            cout << "Oh, NO!  They're both dead!"
                    "  Yuck!" << endl;
        } else if (enemy.dead) {
            defend();
            cout << "He's dead, " << name << endl;
        } else if (dead) {
            enemy.defend();
            cout << "He's dead, " << enemy.name << endl;
        } else {
            defend();
            enemy.defend();
            if (enemy.getStrength() == this->getStrength()) { // if noble's strengths are equal
                enemy.changeStrength(0, true);
                changeStrength(0, true);
                cout << "Mutual Annihalation: " << name << " and "
                     << enemy.name << " die at "
                                      "each other's hands" << endl;
            } else if (enemy.getStrength() > getStrength()) { // if self is weaker than enemy
                changeStrength(0, true);
                double power = 1 - (getStrength() / enemy.getStrength());
                enemy.changeStrength(power, false);
                cout << enemy.name << " defeats " << name << endl;
            } else if (getStrength() > enemy.getStrength()) { // if self is stronger that enemy
                double power = 1 - (enemy.getStrength() / getStrength());
                changeStrength(power, false);
                enemy.changeStrength(0, true);
                cout << name << " defeats " << enemy.name << endl;
            }
        }
    }

    string Noble::getName() const {return name; }

    bool Noble::isDead() const {return dead;}

    void Noble::setDead() {dead = true;}

    Lord::Lord(const string& lord_name) : Noble(lord_name) {}

    void Lord::remove_warrior(Protector* prot) {
        size_t index = 0;
        bool found = false;
        for (size_t i = 0; i < protectors.size(); i++)
            if (protectors[i] == prot) {
                army_strength -= prot->getStrength();
                prot->setLord(nullptr);
                index = i;
                found = true;
                break;
            }
        if (found) {
            for (size_t j = index + 1; j <
                                       protectors.size(); j++) {
                protectors[j - 1] = protectors[j];
            }
        }
        protectors.pop_back();
    }


    bool Lord::hires(Protector& prot) {
        if (!isDead()) {
            if (!prot.isHired()) {
                prot.setLord(this);
                protectors.push_back(&prot);
                army_strength += prot.getStrength();
                return true;
            }
            else {cout << "Protector " << prot.getName()
                       << " is already hired!" << endl;}
            return false;
        }
        return false;
    }

    double Lord::getStrength() {
        return army_strength; }


    bool Lord::fires(Protector& prot) {
        size_t index = 0;
        if (isDead()) {
            cout << "You, Lord: " << getName()
                 << " are dead!" << endl;
            return false;
        }
        if (!prot.isHired()) {
            cout << "Protector: " << prot.getName()
                 << " is not hired!" << endl;
            return false;
        }
        bool exists = false;
        for (const Protector* prot2: protectors) {
            if (&prot == prot2) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            cout << "Warrior is not in noble's army!" << endl;
            return false;
        } else {
            bool found = false;
            for (size_t i = 0; i < protectors.size(); i++)
                if (protectors[i] == &prot) {
                    army_strength -= prot.getStrength();
                    prot.setLord(nullptr);
                    index = i;
                    found = true;
                    break;
                }
            if (found) {
                for (size_t j = index + 1; j <
                                           protectors.size(); j++) {
                    protectors[j - 1] = protectors[j];
                }
            }
            protectors.pop_back();
            cout << "You don't work for me anymore "
                 << prot.getName() << "! -- " <<
                 getName() << "." << endl;
            return true;
        }
    }

    void Lord::defend() {
        for (Protector* prot : protectors) {
            if (!prot->isDead()) {
                prot->defend();
            }
        }
    }

    void Lord::changeStrength(double power, bool dead) {
        if (dead) {
            for (Protector* prot : protectors) {
                prot->setStrength(0);
                prot->setDead();
            }
            army_strength = 0;
            this->setDead();
        }
        else {
            for (Protector* prot : protectors) {
                prot->setStrength(prot->getStrength() * power);
                army_strength *= power;
            }
        }
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(const
    string& nob_name, int nob_strength) : Noble(nob_name), strength(nob_strength) {}

    double PersonWithStrengthToFight::getStrength()  {return strength; }
    void PersonWithStrengthToFight::changeStrength(double power, bool dead)  {
        if (dead) {
            setDead();
            strength = 0;
        }
        else {
            strength *= power;
        }
    }

    void PersonWithStrengthToFight::defend() {
        cout << "UGH!!!" << endl;
    }

}