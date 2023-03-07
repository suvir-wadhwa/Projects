// Suvir Wadhwa
// CS - 2124 HW 4
// Code to set up Warriors and nobles and make nobles battle with each other,
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior;
class Noble;



class Warrior { // Class warrior, creates a warrior
    // with a strength and name
    friend ostream& operator<<(ostream& os, const Warrior& warr);
public:
    Warrior(const string& warr_name, double warr_strength) : name(warr_name), strength(warr_strength) {}
    // Enables Noble to check if warrior already has noble.
    Noble* getNoble() const {return noble;}
    // Enables Noble to link to a warrior
    void setNoble(Noble* set_noble) {
        noble = set_noble;
    }
    // enables noble to get a warriors strength

    double getStrength() const {return strength;}

    // enables Noble to set a warriors strength
    void setStrength(double stren) {
        strength = stren;
    }
    void setDead() {
        dead = true;
    }
    const string& getName() const { return name;}

private:
    bool dead = false;
    double strength;
    string name;
    Noble* noble = nullptr;
};

ostream& operator<<(ostream& os, const Warrior& warr) { // Output operator for Warrior
    os << "\t" << warr.name << ": " << warr.strength << endl;
    return os;
}


class Noble { // Class noble, creates a Noble and enables it to
    // add warriors, fire them, and make one noble battle another.
    friend ostream& operator<<(ostream& os, const Noble& nob);
public:
    Noble(const string& noble_name) : name(noble_name) {}
    bool hire(Warrior& warr) {
        if (!dead) {
            if (warr.getNoble() == nullptr) {
                warr.setNoble(this);
                warriors.push_back(&warr);
                strength += warr.getStrength();
                return true;
            }
            return false;
        }
        return false;
    }

    void fire(Warrior& warr) { // fires a warrior from noble's warriors pointer vector
        size_t index;
        for (size_t i = 0; i < warriors.size(); i ++)
            if (warriors[i] == &warr) {
                strength -= warr.getStrength();
                warr.setNoble(nullptr);
                index = i;
                break;
            }
        for (size_t j = index + 1; j < warriors.size(); j++){
            warriors[j - 1] = warriors[j];
        }
        warriors.pop_back();
        cout << "You don't work for me anymore "
        << warr.getName() << "! -- " << name << "." << endl;
    }
    void battle(Noble& enemy) { // Makes 2 nobles battle
        cout << name << " battles " << enemy.name << endl;
        if (dead && enemy.dead) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        else if (dead || enemy.dead) {
            cout << "He's dead, " << name << endl;
        }
        else {
            if (enemy.strength == strength) { // if noble's strengths are equal
                dead = true;
                enemy.dead = true;
                strength = 0;
                enemy.strength = 0;
                for (Warrior *warr: warriors) {
                    warr->setStrength(0);
                    warr->setDead();
                }
                for (Warrior *warr: enemy.warriors) {
                    warr->setStrength(0);
                    warr->setDead();
                }
                cout << "Mutual Annihalation: " << name << " and "
                     << enemy.name << " die at each other's hands" << endl;
            } else if (enemy.strength > strength) { // if self is weaker than enemy
                dead = true;
                for (Warrior *warr: warriors) {
                    warr->setStrength(0);
                    warr->setDead();
                }
                for (Warrior *warr: enemy.warriors) {
                    warr->setStrength(warr->getStrength()
                    * (1 - (strength / enemy.strength)));
                }
                enemy.strength = enemy.strength *
                        (1 - (strength / enemy.strength));
                strength = 0;
                cout << enemy.name << " defeats " << name << endl;
            } else if (strength > enemy.strength){ // if self is stronger that enemy
                enemy.dead = true;
                for (Warrior *warr: enemy.warriors) {
                    warr->setStrength(0);
                    warr->setDead();
                }
                for (Warrior *warr: warriors) {
                    warr->setStrength(warr->getStrength() *
                    (1 - (enemy.strength / strength)));
                }
                strength = strength * (1 - (enemy.strength / strength));
                enemy.strength = 0;
                cout << name << " defeats " << enemy.name << endl;
            }
        }
    }

private:
    bool dead = false;
    double strength;
    string name;
    vector<Warrior*> warriors;
};

ostream& operator<<(ostream& os, const Noble& nob) { // Output Operator for noble
    os << nob.name << " has an army of " << nob.warriors.size() << endl;
    for (Warrior* warr : nob.warriors){
        os << *warr;
    }
    return os;
}


int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}
