/*
  CS2124 - Sec C
  oop.cpp
 */

#include <iostream>
#include <string>
using namespace std;

//struct Person {
class Person {

    friend ostream& operator<<(ostream& os, const Person& someone);

private:
    string name;
    int age;

public:
    // Person(const string& theName) {
    // 	name = theName;
    // }
    
    Person(const string& theName, int age)
	: name(theName), age(age) { // initialization list
    }

    //void personEating(const Person& aPerson) {
    //void eating() {
    void eating() const {
	//cout << aPerson.name << " eating\n";
	cout << name << " eating\n";
    }

    //const string& getName() { return name; }
    const string& getName() const { 
	//name = "Fred";
	return name; 
    }

    int getAge() const { return age; }

};

void personEating(const Person& aPerson) {
    //cout << aPerson.name << " eating\n";
    //cout << aPerson.getName() << " eating\n";
    aPerson.eating();
}

ostream& operator<<(ostream& os, const Person& someone) {
    //    os << "Name: " << someone.getName();
    //os << "Name: " << someone.getName() << ", age: " << someone.getAge();
    os << "Name: " << someone.name << ", age: " << someone.age;
    return os;
}

int main() {
    //Person john;
    //Person john("John");
    Person john("John", 19);
    //john.name = "John";
    //john.setName("John");
    personEating(john);
    john.eating();

    cout << john;
    //operator<<(cout, john);

    //john.operator<<(cout); // WRONG
    //cout.operator<<(john); // I don't want to!!!!

    cout << john << endl;
    (cout << john) << endl;

    //Person mary;

    vector<Person> vp;
    ifstream ifs("persons.txt");

    string name;
    int age;
    // while (ifs >> name >> age) {
    // 	Person someone(name, age);
    // 	vp.push_back(someone);
    // }
    while (ifs >> name >> age) {
	vp.emplace_back(name, age);
    }
}
