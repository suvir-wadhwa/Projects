// CS-UY 2124 HW-3
// Suvir Wadhwa
// Program to run a simulation of a war setting based on solider presence and strength.
// This time, including the warrior's weapon.
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warr);
private:
    class Weapon {
    public:
        string name;
        int strength;
    };
    Weapon weapon;
public:
    string name;
    // Methods
    // To access strength
    int getStrength() const { return weapon.strength;}
    void setStrength(int stren) {
        weapon.strength = stren;
    }
    // To access name
    string getName() const {return weapon.name;}
    void setName(const string& str){
        weapon.name = str;
    }
};

ostream& operator<<(ostream& os, const Warrior& warr) {
    os << "Warrior: " << warr.name << ", weapon: " << warr.weapon.name
    << ", " << warr.weapon.strength;
    return os;
}

void add_warriors(ifstream& file, vector<Warrior>& warriors); // Function to add warriors from the file
void status_output(const vector<Warrior>& warriors); // Function to display remaining soldiers and their strength
void battle_output(vector<Warrior>& warriors,
                   const string& name1, const string& name2); // Function to output the result of a battle.

int main() {
    ifstream file("warriors.txt");
    if (!file) {
        cout << "file doesn't exist!";
        exit(1);
    }
    vector<Warrior> warriors;
    string command;
    while (file >> command) {
        if (command == "Warrior"){
            add_warriors(file, warriors);
        }
        if (command == "Status"){
            status_output(warriors);
        }
        else if (command == "Battle"){
            string name1;
            string name2;
            file >> name1 >> name2;
            battle_output(warriors, name1, name2);
        }
    }
    file.close();
}

void add_warriors(ifstream& file, vector<Warrior>& warriors) {
    string name;
    string weapon_name;
    int strength;
    Warrior warr;
    file >> name >> weapon_name >> strength;
    warr.name = name;
    warr.setStrength(strength);
    warr.setName(weapon_name);
    warriors.push_back(warr);
}


void status_output(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}

void battle_output(vector<Warrior>& warriors,
                   const string& name1, const string& name2) {
    for (Warrior& warrior1 : warriors) {
        if (warrior1.name == name1){
            for (Warrior& warrior2 : warriors) {
                if (warrior2.name == name2){
                    cout << warrior1.name << " battles " << warrior2.name << endl;
                    if (warrior1.getStrength() == 0 && warrior2.getStrength() == 0) {
                        cout << "oh, NO! They're both dead! Yuck!" << endl;
                    }
                    else if (warrior1.getStrength() == 0){
                        cout << "He's dead, " << warrior2.name << endl;
                    }
                    else if (warrior2.getStrength() == 0) {
                        cout << "He's dead, " << warrior1.name << endl;
                    }
                    else if (warrior1.getStrength() == warrior2.getStrength()){
                        warrior1.setStrength(0);
                        warrior2.setStrength(0);
                        cout << "Mutual Annihilation: " << warrior1.name << " and ";
                        cout << warrior2.name << " die at each other's hands" << endl;
                    }
                    else if (warrior1.getStrength() > warrior2.getStrength()){
                        warrior1.setStrength((warrior1.getStrength() - warrior2.getStrength()));
                        warrior2.setStrength(0);
                        cout << warrior1.name << " defeats " << warrior2.name << endl;
                    }
                    else {
                        warrior2.setStrength((warrior2.getStrength() - warrior1.getStrength()));
                        warrior1.setStrength(0);
                        cout << warrior2.name << " defeats " << warrior1.name << endl;
                    }
                }
            }
        }
    }
}

