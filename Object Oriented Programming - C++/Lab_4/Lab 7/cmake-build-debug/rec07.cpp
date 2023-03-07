/*
  Recitation 07 - Start
  CS2124
 
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

// 
// Position class
// 
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


// 
// Directory class
// 
class Directory {
    // 
    // nested Entry class
    // 
    class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs) {
	    os << rhs.name << ' ' << rhs.room
	       << ' ' << rhs.phone << ", " << *rhs.pos;
	    return os;
	}
    public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
	    : name(name), room(room), phone(phone), pos(&position) {
	}
	const string& getName() const { return name; }
	unsigned getPhone() const { return phone; }
    private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    // ...
    
    friend ostream& operator<<(ostream& os, const Directory& direc) {
	    os << direc.company << " has " << direc.size
	       << " employees." << endl;
	       
	       
	       
	       
	       for(size_t i = 0; i < direc.size; i++ ) {
	           cout << *(direc.entries[i]) << endl;
	       }
	       
	    return os;
	}

public:
    
    Directory(const string& companyName) : company(companyName) {
        size = 0;
        capacity = 1;
        
    }
    
    ~Directory() {
	for(size_t i = 0; i < size; i++){
    delete entries[i];
    
    }
    delete [] entries;
    }
    
    Directory(const Directory& anotherDirec){
        entries = new Entry*[anotherDirec.capacity];
        capacity = anotherDirec.capacity;
        size = anotherDirec.size;
        for(int i = 0; i < size; i++)
        {
        entries[i] = new Entry(*anotherDirec.entries[i]);
        }
        
    }
    
    
    Directory& operator=(const Directory& direc){
        if ( this != &direc ) {  // if we are NOT doing self-assignment
	    // 1. Free up our resources
	    for(size_t i = 0; i < size; i++){
        delete entries[i];
    
        }
        delete [] entries;
        // 2. allocate and copy 
        entries = new Entry*[direc.capacity];
        capacity = direc.capacity;
        size = direc.size;
        for(int i = 0; i < size; i++)
        {
        entries[i] = new Entry(*direc.entries[i]);
        }
        
        
        }
        return *this;
    }
    
    int operator[](const string& name) const {
        for(size_t i = 0; i < size; i++){
    if(entries[i]->getName() == name)
    return entries[i]->getPhone();
    }
    //if the phone number assosiciated with the name is not found...
    return 0;
    }
        
    
    
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            
            Entry** oldData = entries;
            entries = new Entry*[2*capacity];
            
            for (size_t i = 0; i < size; ++i){
		        entries[i] = oldData[i];
                
            }
            capacity *= 2;
		    delete [] oldData;
		    
            

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

private:	
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;
}; // class Directory

void doNothing(Directory dir) { 
    // You need to overload the Directory output operator before
    // uncommenting the next line.

    cout << dir << endl;
}

int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    
    // Create a Directory
    Directory d("HAL");
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;
    
    
    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;
    
    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";
    
    //should display 1592
    cout << d2["Carmack"] << endl;
    
    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);
    

    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
    	
} // main