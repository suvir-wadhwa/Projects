// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs) {
        Node* curr = rhs.header->next;
        while (curr != rhs.trailer) {
            os << curr->data << " ";
            curr = curr->next;
        }
        return os;
    }
    struct Node {
        Node(int data = 0, Node* next = nullptr, Node* prev = nullptr)
                : data(data), next(next), prev(prev){}
        int data;
        Node* next;
        Node* prev;
    };
public:
    class iterator {
        friend class List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return (lhs.iter == rhs.iter);
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.iter != rhs.iter;
        }
    public:
        iterator(Node* node) : iter(node) {}

        iterator& operator++() {
            iter = iter->next;
            return *this;
        }
        iterator& operator--() {
            iter = iter->prev;
            return *this;
        }
        int& operator*() {
            return iter->data;
        }

    private:
        Node* iter;
    };

    List() : header(new Node()), trailer(new Node()), length(0) {
        header->next = trailer;
        trailer->prev = header;
    }
    void push_back(int data) {
        Node* prev = trailer->prev;
        Node* new_node = new Node(data, trailer, prev);
        trailer->prev = new_node;
        prev->next = new_node;
        length ++;
    }
     int pop_back() {
        int output = trailer->prev->data;
        Node* previous = trailer->prev->prev;
        previous->next = trailer;
        delete trailer->prev;
        trailer->prev = previous;
        length --;
        return output;
    }
    int& front() {
        return header->next->data;
    }
    int front() const {
        return header->next->data;
    }
    int& back() {
        return trailer->prev->data;
    }
    int back() const {
        return trailer->prev->data;
    }
    int size() const {
        return length;
    }
    void push_front(int data) {
        Node* next = header->next;
        Node* new_node = new Node(data, next, header);
        next->prev = new_node;
        header->next = new_node;
        length ++;
    }
    int pop_front() {
        int output = header->next->data;
        Node* next = header->next->next;
        next->prev = header;
        delete header->next;
        header->next = next;
        length --;
        return output;
    }
    void clear() {
        Node* curr = header->next;
        header->next = trailer;
        while (curr != trailer) {
            curr = curr->next;
            delete curr->prev;
        }
        trailer->prev = header;
        length = 0;
    }
    int& operator[](int index) {
        Node* curr = header->next;
        int val = 0;
        while (val != index) {
            curr = curr->next;
            val ++;
        }
        return curr->data;
    }
    int operator[](int index) const {
        Node* curr = header->next;
        int val = 0;
        while (val != index) {
            curr = curr->next;
            val ++;
        }
        return curr->data;
    }
    iterator begin() {return iterator(header->next);}
    iterator end() {return iterator(trailer);}
    iterator insert(const iterator& it, int data) {
        Node* prev = it.iter->prev;
        Node* new_node = new Node(data, it.iter, prev);
        it.iter->prev = new_node;
        prev->next = new_node;
        length ++;
        return iterator(new_node);
    }
    iterator erase(const iterator& it) {
        Node* next = it.iter->next;
        Node* prev = it.iter->prev;
        prev->next = next;
        delete it.iter;
        next->prev = prev;
        length --;
        return next;
    }

private:
    Node* header;
    Node* trailer;
    int length;

};


// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

//// Task 8
//void doNothing(List aList) {
//    cout << "In doNothing\n";
//    printListInfo(aList);
//    cout << endl;
//    cout << "Leaving doNothing\n";
//}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}


class iterator {

public:
    iterator(Node *node) : iter(node) {}

    iterator&operator+=(int val) {
        iter->data += val;
        return *this;
    }

    iterator &operator--() {
        iter = iter->prev;
        return *this;
    }

    int &operator*() {
        return iter->data;
    }

private:
    Node *iter;
}

class iterator {
    friend bool operator!=(const iterator& lhs, const iterator& rhs) {
        return lhs.iter != rhs.iter;
    }
public:
    iterator(Node* node) : iter(node) {}

    iterator& operator++() {
        iter = iter->next;
        return *this;
    }
    iterator& operator--() {
        iter = iter->prev;
        return *this;
    }
    int& operator*() {
        return iter->data;
    }