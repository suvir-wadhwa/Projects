/*
  rec04_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    int number;
};


// Task 2
// Define an Account class
class Account2 {
    friend ostream& operator<<(ostream& os, const Account2& acc);
private:
    string name;
    int number;

public:
    Account2(const string &acc_name, int acc_number) : name(acc_name), number(acc_number) { // initializing
    }

    const string& getName() const {
        return name;
    }

    int getNumber() const { return number; }
};

ostream& operator<<(ostream& os, const Account2& acc) {
    // os << "Name: " << acc.getName() << ", number: " << acc.getNumber() << endl;
    os << "Name: " << acc.name << ", number: " << acc.number;
    return os;
}

// Task 3
// Define an Account and Transaction classes
class Transactions {
    friend ostream& operator<<(ostream& os, const Transactions& tran);
private:
    string dep_with;
    int amount;
public:
    Transactions(const string& deposit_with, int amm) : dep_with(deposit_with), amount(amm) { // initializing
    }

    const string& getDepWith() const {
        return dep_with;
    }

    int getAmount() const { return amount; }
};

ostream& operator<<(ostream& os, const Transactions& tran) {
    os << "Deposit/Withdrawal: " << tran.dep_with << ", amount: " << tran.amount;
    return os;
}

// New Account Class
class Account3 {
    friend ostream& operator<<(ostream& os, const Account3& acc);
private:
    string name;
    int number;
    int balance = 0;
    vector<Transactions> history;

public:
    Account3(const string& acc_name, int acc_number) : name(acc_name), number(acc_number) { // initializing
    }

    const string& getName() const {
        return name;
    }

    int getNumber() const { return number; }

    void deposit(int amount) {
        history.push_back(Transactions("Deposit", amount));
        // cout << balance << endl;
        // cout << amount << endl;
        balance = balance + amount;
        // cout << balance << endl;
    }

    void withdrawal(int amount) {
        if (balance < amount) {
            cout << "Account# " << number << " has only " << balance << ". Insufficient for withdrawal of " << amount << endl;
            return;
        }
        history.push_back(Transactions("Withdrawal", amount));
        // cout << balance << endl;
        // cout << amount << endl;
        balance = balance - amount;
        // cout << balance << endl;
    }
};

ostream& operator<<(ostream& os, const Account3& acc) {
    os << "Deposit/Withdrawal: " << acc.name << ", number: " << acc.number << " balance: " << acc.balance << endl;
    for (const Transactions& currTrans : acc.history) {
        os << currTrans << endl;
        return os;
    }
}


// Task 4
// Define an Account with a nested public Transaction class

// Task 5
// Define an Account with a nested private Transaction class


int main() {
        // Task 1: account as struct
        //      1a
        cout << "Task1a:\n";
        ifstream file("accounts.txt");
        if (!file) {
            cout << "File doesn't exist!";
            exit(1);
        }
        vector<Account> accounts;
        string name;
        int number;
        while (file >> name >> number) {
            Account acc;
            acc.name = name;
            acc.number = number;
            accounts.push_back(acc);
        }
        file.close();
        for (const Account &acc: accounts) {
            cout << "name" << acc.name << " number" << acc.number << endl;
        }
        //      1b
        cout << "Task1b: " << endl;
        cout << "Filling vector of struct objects, using {} initialization:\n";
        accounts.clear();
        file.open("accounts.txt");
        while (file >> name >> number) {
            Account acc2{name, number};
            accounts.push_back(acc2);
        }
        file.close();
        for (const Account &acc: accounts) {
            cout << "name" << acc.name << " number" << acc.number << endl;
        }


        //==================================
        // Task 2: account as class

        //      2a
        cout << "==============\n";
        cout << "\nTask2a:";
        cout << "\nFilling vector of class objects, using local class object:\n";
        vector<Account2> accounts2;
        file.open("accounts.txt");
        while (file >> name >> number) {
            Account2 acc3(name, number);
            accounts2.push_back(acc3);
        }
        file.close();
        for (const Account2 &acc: accounts2) {
            cout << "name" << acc.getName() << " number" << acc.getNumber() << endl;
        }

        cout << "\nTask2b:\n";
        cout << "output using output operator with getters\n";
        accounts2.clear();
        file.open("accounts.txt");
        while (file >> name >> number) {
            Account2 acc3(name, number);
            accounts2.push_back(acc3);
        }
        file.close();
        for (const Account2 &acc: accounts2) {
            cout << "name" << acc.getName() << " number" << acc.getNumber() << endl;
        }

        cout << "\nTask2c:\n";
        cout << "output using output operator as friend without getters\n";
        accounts2.clear();
        file.open("accounts.txt");
        while (file >> name >> number) {
            Account2 acc3(name, number);
            accounts2.push_back(acc3);
        }
        file.close();
        for (const Account2 &acc: accounts2) {
            cout << "name" << acc.getName() << " number" << acc.getNumber() << endl;
        }

        cout << "\nTask2d:\n";
        cout << "Filling vector of class objects, using temporary class object:\n";
        accounts2.clear();
        file.open("accounts.txt");
        while (file >> name >> number) { ;
            accounts2.push_back(Account2(name, number));
        }
        for (const Account2& acc: accounts2) {
            cout << acc << endl;
        }
        file.close();


        cout << "\nTask2e:\n";
        cout << "Filling vector of class objects, using emplace_back:\n";

        accounts2.clear();
        file.open("accounts.txt");
        while (file >> name >> number) { ;
            accounts2.emplace_back(name, number);
        }
        for (const Account2& acc: accounts2) {
            cout << acc << endl;
        }
        file.close();


        cout << "==============\n";
        cout << "\nTask 3:\nAccounts and Transaction:\n";

        ifstream file2("transactions.txt");
        if (! file2){
            cout << "File doesn't exist";
            exit(1);
        }
        vector<Account3> accounts3;
        string type1;
        while (file2 >> type1) {
            // cout << type1 << endl;
            if (type1 == "Account") {
                string name3;
                int acc_number;
                file2 >> name3 >> acc_number;
//                cout << name3 << acc_number << endl;
                // cout << name3 << " " << acc_number << endl;
                accounts3.emplace_back(name3, acc_number);
            } else if (type1 == "Deposit") {
                int acc_num;
                int amm;
                file2 >> acc_num >> amm;
                for (Account3& acc: accounts3) {
                    if (acc_num == acc.getNumber()) {
                        // Transactions tran("Deposit", amm);
                        acc.deposit(amm);
                        //cout << acc.getName() << acc.getNumber() << "Deposit" << amm << endl;
                    }
                }
            } else if (type1 == "Withdraw") {
                int acc_num;
                int amm;
                file2 >> acc_num >> amm;
//                cout << amm << endl;
                for (Account3 &acc: accounts3) {
                    if (acc.getNumber() == acc_num) {
                        // Transactions tran("Deposit", amm);
                        acc.withdrawal(amm);
                    }
                }
            }
        }

        for (Account3& account : accounts3) {
            cout << account << endl;
        }




        cout << "==============\n";
        cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

        cout << "==============\n";
        cout << "\nTask 5:\nTransaction nested in private section of Account:\n";


    }