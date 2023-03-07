/*
  rec11.cpp
  Starting code 21F
 */

#include <iostream>
#include <vector>
using namespace std;

class Instrument { // Abstract Class
public:
    virtual void makeSound() = 0;
    virtual void Play()  = 0;
private:
};

class Brass : public Instrument {
public:
    Brass(unsigned mouthpiece) : mouth_size(mouthpiece) {}

    void makeSound() override {
        cout << "To make a sound... blow on a mouthpiece of size " << mouth_size << endl;
    }
private:
    unsigned mouth_size;
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned val) : Brass(val) {}
    void Play() override {
        cout << "Toot";
    }
};

class Trombone : public Brass {
public:
    Trombone(unsigned val) : Brass(val) {}
    void Play() override {
        cout << "Blat";
    }
};

class String : public Instrument {
public:
    String(unsigned pit) : pitch(pit) {}
    void makeSound() override {
        cout << "To make a sound... bow a string with pitch " << pitch << endl;
    }
private:
    const unsigned pitch;
};

class Violin : public String {
public:
    Violin(unsigned val) : String(val) {}
    void Play() override {
        cout << "Screech";
    }
};

class Cello : public String {
public:
    Cello(unsigned val) : String(val) {}
    void Play() override {
        cout << "Squawk";
    }
};

class Percussion : public Instrument {
public:
    Percussion() {}

    void makeSound() override {
        cout << "To make a sound... hit me!" << endl;
    }
};

class Drum : public Percussion {
public:
    Drum() {}
    void Play() override {
        cout << "Boom";
    }
private:
};

class Cymbal : public Percussion {
public:
    Cymbal() {}
    void Play() override {
        cout << "Crash";
    }
private:
};


class MILL {
public:
    void dailyTestPlay() const {
        for (Instrument* inst : inventory) {
            if (inst != nullptr) {
                inst->makeSound();
            }
        }
    }
    void receiveInstr(Instrument& inst) {
        inst.makeSound();
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i] == nullptr) {
                inventory[i] = &inst;
                return;
            }
        }
        inventory.push_back(&inst);
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i] != nullptr) {
                Instrument* output = inventory[i];
                inventory[i] = nullptr;
                return output;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> inventory;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    void Play() const {
        if (instr) instr->Play();
        else cerr << "have no instr\n";
    }

    bool hasInst() const {
        return (instr != nullptr);
    }

private:
    Instrument* instr;
};


class Orch {
public:
    void play() const {
        for (Musician* mus : musicians) {
            if (mus->hasInst()) {
                mus->Play();
            }
        }
        cout << endl;
    }

    void addPlayer(Musician& mus) {
        musicians.push_back(&mus);
    }

private:
    vector<Musician*> musicians;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ----------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12);
     Violin violin(567);

    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    MILL mill;

    cout << "Put the instruments into the MILL ------------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);

    cout << "Daily test -----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

    cout << "Define some Musicians-------------------------------------------\n";
    Musician harpo;
    Musician groucho;

     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();
     cout << endl;
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << endl << endl;

     groucho.testPlay();
     cout << endl;
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     harpo.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

     // fifth
     mill.receiveInstr(*groucho.giveBackInstr());
     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
     mill.receiveInstr(*harpo.giveBackInstr());


     cout << endl;
     cout << "dailyTestPlay()re" << endl;
     mill.dailyTestPlay();
     cout << endl;

     cout << endl;


    //
    // PART TWO
    //

    //
    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    //*/
}
