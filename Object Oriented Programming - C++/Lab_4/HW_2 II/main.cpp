// CS-UY 2124 HW-2
// Suvir Wadhwa
// Program to run a simulation of a war setting based on solider presence and strength.
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


struct Warrior {
    string name;
    int strength;
};

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
    int strength;
    Warrior warr;
    file >> name >> strength;
    warr.name = name;
    warr.strength = strength;
    warriors.push_back(warr);
}


void status_output(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << "Warrior: " << warrior.name <<
        ", strength: " << warrior.strength << endl;
    }
}

void battle_output(vector<Warrior>& warriors,
                   const string& name1, const string& name2) {
    for (Warrior& warrior1 : warriors) {
        if (warrior1.name == name1){
            for (Warrior& warrior2 : warriors) {
                if (warrior2.name == name2){
                    cout << warrior1.name << " battles " << warrior2.name << endl;
                    if (warrior1.strength == 0 && warrior2.strength == 0) {
                        cout << "oh, NO! They're both dead! Yuck!" << endl;
                    }
                    else if (warrior1.strength == 0){
                        cout << "He's dead, " << warrior2.name << endl;
                    }
                    else if (warrior2.strength == 0) {
                        cout << "He's dead, " << warrior1.name << endl;
                    }
                    else if (warrior1.strength == warrior2.strength){
                        warrior1.strength = 0;
                        warrior2.strength = 0;
                        cout << "Mutual Annihilation: " << warrior1.name << " and ";
                        cout << warrior2.name << " die at each other's hands" << endl;
                    }
                    else if (warrior1.strength > warrior2.strength){
                        warrior1.strength = warrior1.strength - warrior2.strength;
                        warrior2.strength = 0;
                        cout << warrior1.name << " defeats " << warrior2.name << endl;
                    }
                    else {
                        warrior2.strength = warrior2.strength - warrior1.strength;
                        warrior1.strength = 0;
                        cout << warrior2.name << " defeats " << warrior1.name << endl;
                    }
                }
            }
        }
    }
}

