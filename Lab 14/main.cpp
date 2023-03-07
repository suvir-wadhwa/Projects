// rec14_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// task 9: Function to print a list using iterators
void printList(const list<int>& in_list) {
//    for (list<int>::iterator i = in_list.begin(); i != in_list.end(); i ++){
//    cout << *i << " ";
//    }
    for (list<int>::const_iterator i = in_list.begin(); i != in_list.end(); i ++) {
        cout << *i << " ";
    }
}
// task 10: Function to print a list using ranged for.
void printList2(const list<int>& in_list) {
    for (int val : in_list) { cout << val << " ";}
}

// task 11: Print using auto instead of writing iterators
void printList3(const list<int>& in_list) {
    for (auto i = in_list.begin(); i != in_list.end(); i ++) {
        cout << *i << " ";
        i++;
    }
}

// task 12: Function to find an item in a list
list<int>::const_iterator find(const list<int>& in_list, int num) {
    for (list<int>::const_iterator i = in_list.begin(); i != in_list.end(); i++) {
        if (*i == num) {
            cout << "Found!" << endl;
            return i;
        }
    }
    cout << "Not Found!" << endl;
    return in_list.end();
}

// task 13: Function to find an item in a list using auto
auto find2(const list<int>& in_list, int num) {
    for (auto i = in_list.begin(); i != in_list.end(); i++) {
        if (*i == num) {
            cout << "Found!" << endl;
            return i;
        }
    }
    cout << "Not Found!" << endl;
    return in_list.end();
}

// task 15: Function to check if input is even
bool isEven(int num) {
    return (num % 2 == 0);
}

// task 16: Class with Functor
class Func {
public:
    bool operator()(int num) const {
        return (num % 2 == 0);
    }
};

// task 19: My implementation of the Find Algorithm
list<int>::iterator ourFind(list<int>::iterator begin,
                            list<int>::iterator end, int val) {
    cout << "My Version!" << endl;
    for (list<int>::iterator i = begin; i != end; i++){
        if (*i == val) {
            return i;
        }
    }
    return end;
}

// task 20: My implementation of the Find Algorithm using templates
template<typename T, typename I>
T ourFind(T begin, T end, I val) {
    cout << "My Templated Version!" << endl;
    for (T i = begin; i != end; i++){
        if (*i == val) {
            return i;
        }
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> values = {1, 2, 3, 4, 5,  6};
    for (int val : values) {cout << val << " ";}

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> value_list(values.begin(), values.end());
    for (int val : value_list) { cout << val << " ";}

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(values.begin(), values.end());
    for (int val : values) {cout << val << " ";}
    cout << endl;
    for (int val : value_list) { cout << val << " ";}

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < values.size(); i++) {
        if (i % 2 == 0) {cout << values[i] << " ";}
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t i = 0; i <  value_list.size(); i++) {
//        if (i % 2 == 0) {cout << value_list[i] << " ";}
//    }
    cout << "\n=======\n";

    //
    // Iterators
    //
    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator i = values.begin(); i != values.end(); i+= 2) {
        cout << *i << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator i = value_list.begin(); i != value_list.end() ; i++, i++) {
        cout << *i << " ";
//        i++;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    value_list.sort();
    for (int val : value_list) { cout << val << " ";}

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(value_list);
    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(value_list);

    cout << "\n=======\n";
    //
    // Auto
    //
    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printList3(value_list);

    cout << "\n=======\n";


    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    if (find(value_list, 3) == value_list.end()) {
        cout << "Not Found" << endl;

    }
    else {
        cout << "Found"  << endl;
    }

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    if (find2(value_list, 3) == value_list.end()) {
        cout << "Not Found" << endl;

    }
    else {
        cout << "Found"  << endl;
    }
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    list<int>::iterator val = find(value_list.begin(), value_list.end(), 9);
    if (val == value_list.end()) {
        cout << "NOT FOUND\n";
    }
    else {
        cout << *val << endl;
    }


    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    list<int>::iterator val2 = find_if(value_list.begin(), value_list.end(), isEven);
    if (val2 == value_list.end()) {
        cout << "NOT FOUND\n";
    }
    else {
        cout << *val2 << endl;
    }


    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    list<int>::iterator val3 = find_if(value_list.begin(), value_list.end(), Func());
    if (val3 == value_list.end()) {
        cout << "NOT FOUND\n";
    }
    else {
        cout << *val3 << endl;
    }


    cout << "\n=======\n";

    // 17. Lambda
    cout << "Task 17:\n";
    list<int>::iterator val4 = find_if(value_list.begin(), value_list.end(), [] (int num) {return num % 2 == 0;});
    if (val4 == value_list.end()) {
        cout << "NOT FOUND\n";
    }
    else {
        cout << *val4 << endl;
    }
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[value_list.size()];
    copy(value_list.begin(), value_list.end(), arr);
    for (size_t i = 0; i < value_list.size(); i++) {
        cout << arr[i] << " ";
    }
    if (find(arr, arr + value_list.size(), 9) == arr + value_list.size()) {
        cout << "not found" << endl;
    }
    else {
        cout << "Found!!!!!\n";
    }
    delete [] arr;

    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::iterator task_19 = ourFind(value_list.begin(), value_list.end(), 3);
    if (task_19 == value_list.end()) {
        cout << "not found" << endl;
    }
    else {
        cout << *task_19 << endl;
        cout << "Found!\n";
    }

    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    vector<int>::iterator task_20 = ourFind(values.begin(), values.end(), 3);

    if (task_20 == values.end()) {
        cout << "not found" << endl;
    }
    else {
        cout << *task_20 << endl;
        cout << "Found!\n";
    }

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> tokens;
    ifstream file("pooh-nopunc.txt");
    if (!file) {
        cout << "File didn't open!" << endl;
    }
    else {
        string token;
        while (file >> token) {
            if ((find(tokens.begin(), tokens.end(), token) == tokens.end())) {
                tokens.push_back(token);
            }
        }
        file.close();
    }
    cout << "Size: " << tokens.size() << endl;
//    cout << "All Tokens:\n";
//    for (const string& tok : tokens) { cout << tok << endl;}
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> tokens2;
    ifstream file2("pooh-nopunc.txt");
    if (!file2) {
        cout << "File didn't open!" << endl;
    }
    else {
        string token;
        while (file2 >> token) {
            tokens2.insert(token);
        }
        file2.close();
    }
    cout << "Size: " << tokens2.size() << endl;
//    cout << "All Tokens:\n";
//    for (const string& tok : tokens2) { cout << tok << endl;}

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    ifstream file3("pooh-nopunc.txt");
    if (!file3) {
        cout << "File didn't open!" << endl;
    }
    else {
        string token;
        int count = 0;
        while (file3 >> token) {
            wordMap[token].push_back(count);
            count++;
        }
        file3.close();
        for (const auto &member: wordMap) {
            cout << member.first << ": ";
            for (auto i: member.second) {
                cout << i << ' ';
            }
            cout << endl;
        }
    }

    cout << "=======\n";
}
