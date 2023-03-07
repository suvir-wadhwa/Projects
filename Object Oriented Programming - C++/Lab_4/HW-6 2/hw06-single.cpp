// Suvir Wadhwa
// HW-5 CS-UY 2124
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Warrior;
class Noble;


class Warrior { // Class warrior, creates a warrior
    // with a strength and name
    friend ostream& operator<<(ostream& os, const Warrior& warr);
public:
    Warrior(const string& warr_name, double warr_strength);
    // Enables Noble to check if warrior already has noble.
    bool getNoble() const;
    // Enables Noble to link to a warrior
    void setNoble(bool exist, Noble* nob_pointer);
    // enables noble to get a warriors strength
    double getStrength() const;
    // enables Noble to set a warriors strength
    void setStrength(double stren);
    void setDead();
    const string& getName() const;
    void runaway();
    bool isHired() const;

private:
    bool dead = false;
    double strength;
    string name;
    bool noble = false;
    Noble* nob = nullptr;
};


class Noble { // Class noble, creates a Noble and enables it to
    // add warriors, fire them, and make one noble battle another.
    friend ostream& operator<<(ostream& os, const Noble& nob);
public:
    Noble(const string& noble_name);
    bool hire(Warrior& warr);
    bool fire(Warrior& warr);
    const string& getName() const;
    void remove_warrior(Warrior* warr);
    void battle(Noble& enemy);
    void kill_warriors(const vector<Warrior*>& warr);
private:
    bool dead = false;
    double strength;
    string name;
    vector<Warrior*> warriors;
};

void change_warriors_strength(vector<Warrior*>& warr, double& strength1, double& strength2);


// Main: Reads input from the file, carries out different commands
int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}



// Warrior Class:
Warrior::Warrior(const string& warr_name, double warr_strength)
        : name(warr_name), strength(warr_strength) {}
// Enables Noble to check if warrior already has noble.
bool Warrior::getNoble() const {return noble;}
// Enables Noble to link to a warrior
void Warrior::setNoble(bool exist, Noble* nob_pointer) {
    noble = exist;
    nob = nob_pointer;
}
// enables noble to get a warriors strength

double Warrior::getStrength() const {return strength;}

// enables Noble to set a warriors strength
void Warrior::setStrength(double stren) {
    strength = stren;
}
void Warrior::setDead() {
    dead = true;
}
const string& Warrior::getName() const { return name;}

void Warrior::runaway() {
    if (nob != nullptr) {
        cout << name << " flees in terror, abandoning his lord, " << nob->getName() << endl;
        noble = false;
        nob->remove_warrior(this);
        nob = nullptr;
    }
}

bool Warrior::isHired() const {return noble;}

ostream& operator<<(ostream& os,
                    const Warrior& warr) { // Output operator for Warrior
    os << "\t" << warr.name << ": " << warr.strength << endl;
    return os;
}

// Noble Class:


void Noble::kill_warriors(const vector<Warrior*>& warrior) {
    for (Warrior *warr: warrior) {
        warr->setStrength(0);
        warr->setDead();
    }
}


Noble::Noble(const string& noble_name) : name(noble_name) {}

bool Noble::hire(Warrior& warr) {
    if (!dead) {
        if (!warr.getNoble()) {
            warr.setNoble(true, this);
            warriors.push_back(&warr);
            strength += warr.getStrength();
            return true;
        }
        else {cout << "Warrior " << warr.getName()
                   << " is already hired!" << endl;}
        return false;
    }
    return false;
}

const string& Noble::getName() const {return name; }

bool Noble::fire(Warrior& warr) { // fires a warrior
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
    for (const Warrior* warr2: warriors) {
        if (&warr == warr2) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "Warrior is not in noble's army!" << endl;
        return false;
    }
    else {
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

void Noble::remove_warrior(Warrior* warr) {
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

ostream& operator<<(ostream& os, const Noble& nob) { // Output Operator for noble
    os << nob.name << " has an army of " <<
       nob.warriors.size() << endl;
    for (const Warrior* warr : nob.warriors){
        os << *warr;
    }
    return os;
}


