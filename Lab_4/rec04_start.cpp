///*
//  rec04_start.cpp
// */
//
//// Provided
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>
//using namespace std;
//
//// Task 1
//// Define an Account struct
//struct Account {
//    string name;
//    int number;
//};
//
//
//// Task 2
//// Define an Account class
//class Account {
//private:
//    string name;
//    int number;
//
//public:
//    Account(const string &acc_name, int acc_number) : name(acc_name), number(acc_number) { // initializing
//    };
//
//    const string& getName() const {
//        return name;
//    }
//
//    int getNumber() const { return number; }
//
//};
//
//// Task 3
//// Define an Account and Transaction classes
//
//// Task 4
//// Define an Account with a nested public Transaction class
//
//// Task 5
//// Define an Account with a nested private Transaction class
//
//
// main() {
//
//    // Task 1: account as struct
//    //      1a
//    cout << "Task1a:\n";
//    ifstream file("accounts.txt");
//    if (!ifstream){
//        cout << "File doesn't exist!";
//        exit(1);
//    }
//    vector<Account> accounts;
//    string name;
//    int number;
//    while (file >> name >> number){
//        Account acc;
//        acc.name = name;
//        acc.number = number;
//        accounts.push_back(acc);
//    }
//    file.close();
//    for (const Account& acc : accounts){
//        cout << "name" << acc.name << " number" << acc.number << endl;
//    }
//    //      1b
//    cout << "Task1b: " << endl;
//    cout << "Filling vector of struct objects, using {} initialization:\n";
//    accounts.clear();
//    file.open("accounts.txt");
//     while (file >> name >> number) {
//         Account acc2{name, number};
//         accounts.push_back(acc2);
//     }
//     file.close();
//     for (const Account& acc : accounts) {
//         cout << "name" << acc.name << " number" << acc.number << endl;
//     }
//
//
//    //==================================
//    // Task 2: account as class
//
//    //      2a
//    cout << "==============\n";
//    cout << "\nTask2a:";
//    cout << "\nFilling vector of class objects, using local class object:\n";
//    accounts.clear();
//    file.open("accounts.txt");
//    while (file >> name >> number) {
//             Account acc3(name, number);
//             accounts.push_back(acc3);
//         }
//    file.close();
//    for (const Account& acc : accounts){
//        cout << "name" << acc.getName() << " number" << acc.getNumber() << endl;
//    }
//
//
//    cout << "\nTask2b:\n";
//    cout << "output using output operator with getters\n";
//
//
//    cout << "\nTask2c:\n";
//    cout << "output using output operator as friend without getters\n";
//
//
//    cout << "\nTask2d:\n";
//    cout << "Filling vector of class objects, using temporary class object:\n";
//
//
//    cout << "\nTask2e:\n";
//    cout << "Filling vector of class objects, using emplace_back:\n";
//
//
//    cout << "==============\n";
//    cout << "\nTask 3:\nAccounts and Transaction:\n";
//
//
//    cout << "==============\n";
//    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
//
//    cout << "==============\n";
//    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
//
//
//}
