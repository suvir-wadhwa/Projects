//Suvir Wadhwa
//10/01/2021
// Lab 5
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
struct Complex {
    double real;
    double img;
};

class PlainOldClass {
public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; }
    void setX( int val )  { x = val; }
private:
    int x;
};

class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    void setX( int x )  { this->x = x;}
private:
    int x;
};

class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
            : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};

class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {

        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};

class Amplifier {
public:
    void attachSpeakers(SpeakerSystem& spkrs)
    {
        if(attachedSpeakers)
            cout << "already have speakers attached!\n";
        else
            attachedSpeakers = &spkrs;
    }

    void detachSpeakers() { // should there be an "error" message if not attached?
        attachedSpeakers = nullptr;
    }

    void playMusic( ) const {
        if (attachedSpeakers)
            attachedSpeakers -> vibrateSpeakerCones(440);
        else
            cout << "No speakers attached\n";
    }
private:
    SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if(newRoomate.roomie != nullptr && roomie != nullptr ) {
            roomie = &newRoomate;        // now I have a new roomie
            newRoomate.roomie = this;    // and now they do toosx
        }
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};

int main()
{
    int x;
    x = 10;
    cout << "x = " << x << endl;

    int* p;
    p = &x;
    cout << "p = " << p << endl;

    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;

    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;

    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
    //pD  = p;
    //p   = pD;

    int joe = 24;
    const int sal = 19;
    int*  pI; // holds address, int pointer
    pI = &joe;
    *pI = 234;
    //pI = &sal;
    *pI = 7623;

    const int* pcI;
    pcI = &joe;
    //*pcI = 234; not working due to const
    pcI = &sal;
    //*pcI = 7623;

    //int* const cpI;
    //int* const cpI(&joe);
    //int* const cpI(&sal);
    //cpI = &joe;
    //*cpI = 234;
    //cpI = &sal;
    //*cpI = 7623;

    //const int* const cpcI;
    //const int* const cpcI(&joe);
    //const int* const cpcI(&sal);
    //cpcI = &joe;   *cpcI = 234;
    //cpcI = &sal;
    //*cpcI = 7623;

    Complex c = {11.23,45.67};
    Complex* pC(&c);

    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;

    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;

    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";

    //cout << pDyn << endl;
    //delete pDyn;
    //cout << pDyn << endl;
    //int* pDyn2 = pDyn;
    //pDyn = nullptr;
    //cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    //cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

    //double* pDouble = nullptr;

    //cout << "Can we dereference nullptr?  " << *pDyn << endl;
    //cout << "Can we dereference nullptr?  " << *pDouble << endl;

    //long jumper = 12238743;
    //delete jumper;
    //long* ptrTolong = &jumper;
    //delete ptrTolong;
    //Complex cmplx;
    //delete cmplx;

    //The new expression yields a pointer value that points to the heap memory the system lets the program use.

    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

// fill vector with Colours from the file
// this could be from an actual file but here we are using the keyboard instead of a file
// (so we don't have to create an actual file)
// Do you remember the keystroke combination to indicate "end of file" at the keyboard?
// somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

// display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }
//if (ptrVar) same thing as ptrVar != nullptr

    SpeakerSystem speaker1;

    Amplifier ampl1;
    ampl1.attachSpeakers(speaker1);

    Person joeBob("Joe Bob");
    Person billyJane("Billy Jane");

    joeBob.movesInWith(billyJane);

    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;


}

