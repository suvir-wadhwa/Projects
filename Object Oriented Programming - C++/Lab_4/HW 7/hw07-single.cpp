// Suvir Wadhwa
//HW 07

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Protector;

class Noble { // Class noble, creates a Noble and enables it to
    // add warriors, fire them. Two types: Lords and PersonWithStrengthToFight
public:
    Noble(const string& noble_name);
    void battle(Noble& enemy);
    virtual void defend() = 0;
    virtual double getStrength() = 0;
    virtual void changeStrength(double power, bool dead) = 0;
    string getName() const;
protected:
    bool isDead() const;
    void setDead();
private:
    bool dead = false;
    string name;
};

class Lord : public Noble {
public:
    Lord(const string& lord_name);
    void remove_warrior(Protector* prot);
    bool hires(Protector& prot);
    double getStrength() override;
    bool fires(Protector& prot);
    void defend() override;
    void changeStrength(double power, bool dead) override;
private:
    double army_strength = 0;
    vector<Protector*> protectors;
};

class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const string& nob_name, int nob_strength);
    double getStrength() override;
    void changeStrength(double power, bool dead) override;
    void defend() override;
private:
    double strength;
};


class Protector { //Base class for fighters that lords hire. 2 main divisions: Wizards, Warriors.
    // Warriors then split further into Archer and swordsman
public:
    Protector(const string& prot_name, int prot_strength);
    virtual void defend() const = 0;
    bool isHired() const;
    void setLord(Lord* myLord);
    void runaway();

    double getStrength() const;
    void setStrength(double stren);
    bool isDead();
    void setDead();
    string getName() const;
protected:
    string getLordName() const;
private:
    Lord* lord = nullptr;
    string name;
    double strength;
    bool dead = false;
};

class Wizard : public Protector {
public:
    Wizard(const string& wiz_name, int wiz_strength);
    void defend() const override;
};

class Warrior : public Protector {
public:
    Warrior(const string& warr_name, int warr_strength);
private:
};

class Archer : public Warrior {
public:
    Archer(const string& arch_name, int arch_strength);
    void defend() const override;
private:
    //
};

class Swordsman : public Warrior {
public:
    Swordsman(const string& sword_name, int sword_strength);
    void defend() const override;
private:
};



int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy(
            "Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay(
            "Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}

// Methods for Nobles:

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


// Protector
Protector::Protector(const string& prot_name, int prot_strength)
: name(prot_name), strength(prot_strength) {}

bool Protector::isHired() const {return lord != nullptr; }
void Protector::setLord(Lord* myLord) {
    lord = myLord;
}

void Protector::runaway() {
    if (lord != nullptr) {
        cout << name << " flees in terror, abandoning his lord, "
                        "" << lord->getName() << endl;
        lord->remove_warrior(this);
        lord = nullptr;
    }
}

double Protector::getStrength() const { return strength; }
void Protector::setStrength(double stren) {
    strength = stren;
}
bool Protector::isDead() {return dead;}
void Protector::setDead() {dead = true;}
string Protector::getName() const {return name; }

string Protector::getLordName() const {
    if (lord != nullptr) {
        return lord->getName();
    }
    return "There's no lord";
}

Wizard::Wizard(const string& wiz_name, int wiz_strength) :
Protector(wiz_name, wiz_strength) {}
void Wizard::defend() const {
    cout << "POOF" << endl;
}

Warrior::Warrior(const string& warr_name, int warr_strength) :
Protector(warr_name, warr_strength) {}


Archer::Archer(const string& arch_name, int arch_strength) :
Warrior(arch_name, arch_strength) {}
void Archer::defend() const {
    cout << "TWANG!  " << getName() << " says: Take that in the"
                                       " name of my lord, " <<
                                       getLordName() << endl;
}

Swordsman::Swordsman(const string& sword_name, int sword_strength) :
Warrior(sword_name, sword_strength) {}
void Swordsman::defend() const  {
    cout << "CLANG!  " << getName() << " says: Take that in the"
                                       " name of my lord, " <<
                                       getLordName() << endl;
}
