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

    Noble::Noble(const string &noble_name) : name(noble_name) {}

    void Noble::kill_warriors(const vector<Warrior*>& warrior) {
        for (Warrior* warr: warrior) {
            warr->setStrength(0);
            warr->setDead();
        }
    }

    bool Noble::hire(Warrior &warr) {
        if (!dead) {
            if (!warr.getNoble()) {
                warr.setNoble(true, this);
                warriors.push_back(&warr);
                strength += warr.getStrength();
                return true;
            } else {
                cout << "Warrior " << warr.getName()
                     << " is already hired!" << endl;
            }
            return false;
        }
        return false;
    }

    const string &Noble::getName() const { return name; }

    bool Noble::fire(Warrior &warr) { // fires a warrior
        // from noble's warriors pointer vector
        size_t index = 0;
        if (dead) {
            cout << "You, Noble: " << name
                 << " are dead!" << endl;
            return false;
        }
        if (!warr.getNoble()) {
            cout << "Warrior: " << warr.getName()
                 << " is not hired!" << endl;
            return false;
        }
        bool exists = false;
        for (const Warrior *warr2: warriors) {
            if (&warr == warr2) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            cout << "Warrior is not in noble's army!" << endl;
            return false;
        } else {
            bool found = false;
            for (size_t i = 0; i < warriors.size(); i++)
                if (warriors[i] == &warr) {
                    strength -= warr.getStrength();
                    warr.setNoble(false, nullptr);
                    index = i;
                    found = true;
                    break;
                }
            if (found) {
                for (size_t j = index + 1; j <
                                           warriors.size(); j++) {
                    warriors[j - 1] = warriors[j];
                }
            }
            warriors.pop_back();
            cout << "You don't work for me anymore "
                 << warr.getName() << "! -- " <<
                 name << "." << endl;
            return true;
        }
    }

    void Noble::remove_warrior(Warrior *warr) {
        size_t index = 0;
        bool found = false;
        for (size_t i = 0; i < warriors.size(); i++)
            if (warriors[i] == warr) {
                strength -= warr->getStrength();
                warr->setNoble(false, nullptr);
                index = i;
                found = true;
                break;
            }
        if (found) {
            for (size_t j = index + 1; j <
                                       warriors.size(); j++) {
                warriors[j - 1] = warriors[j];
            }
        }
        warriors.pop_back();
    }

    void Noble::battle(Noble &enemy) { // Makes 2 nobles battle
        cout << name << " battles " <<
             enemy.name << endl;
        if (dead && enemy.dead) {
            cout << "Oh, NO!  They're both dead!"
                    "  Yuck!" << endl;
        } else if (enemy.dead) {
            cout << "He's dead, " << name << endl;
        } else if (dead) {
            cout << "You're dead, genius!" << endl;
        } else {
            if (enemy.strength == strength) { // if noble's strengths are equal
                dead = true;
                enemy.dead = true;
                strength = 0;
                enemy.strength = 0;
                kill_warriors(warriors);
                kill_warriors(enemy.warriors);
                cout << "Mutual Annihalation: " << name << " and "
                     << enemy.name << " die at "
                                      "each other's hands" << endl;
            } else if (enemy.strength > strength) { // if self is weaker than enemy
                dead = true;
                kill_warriors(warriors);
                change_warriors_strength(enemy.warriors, strength, enemy.strength);
                cout << enemy.name << " defeats " << name << endl;
            } else if (strength > enemy.strength) { // if self is stronger that enemy
                enemy.dead = true;
                kill_warriors(enemy.warriors);
                change_warriors_strength(warriors, enemy.strength, strength);
                cout << name << " defeats " << enemy.name << endl;

            }
        }
    }

    void change_warriors_strength(vector<Warrior*>& warr, double& strength1, double& strength2) {
        for (Warrior*warr: warr) {
            warr->setStrength(warr->getStrength() *
                              (1 - (strength1 / strength2)));
        }
        strength2 = strength2 * (1 - (strength1 / strength2));
        strength1 = 0;
    }


    ostream &operator<<(ostream &os, const Noble &nob) { // Output Operator for noble
        os << nob.name << " has an army of " <<
           nob.warriors.size() << endl;
        for (const Warrior *warr: nob.warriors) {
            os << *warr;
        }
        return os;
    }
}