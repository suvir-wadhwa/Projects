/*
  rec06_start.cpp
 */
// Suvir Wadhwa
// Lab 6

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// First class:

class LabRecords {
    friend ostream& operator<<(ostream& os, const LabRecords& rec);
public:
    LabRecords(const string& name) : student_name(name) {
        for (int i = 0; i < 14; i ++){
            grades.push_back(-1);
        }
    }
    const string& getName() const { return student_name;}

    void addGrade(int week, int grade){
        grades[week - 1] = grade;
    }

private:
    string student_name;
    vector<int> grades;
};

ostream& operator<<(ostream& os, const LabRecords& rec) {
    os << "Name: " << rec.student_name << ", Grades: ";
    for (int grade : rec.grades) {
        os << grade << " ";
    }
    os << endl;
    return os;
}

class Section {
    friend ostream& operator<<(ostream& os, const Section& sec);
    class Time {
        friend ostream& operator<<(ostream& os, const Time& time1) {
            os << "[Day: " << time1.day << ", Start time: ";
            if (time1.time >= 12){
                os << (time1.time - 12) << "pm]";
            }
            else {
                os << (time1.time) << "am]";
            }
            return os;
        }
    public:
        Time(const string& weekday, int hour) : time(hour), day(weekday){
        }
    private:
        int time;
        string day;
    };
public:
    Section(const string& section_name, const string& day, int hour) : sec_name(section_name), date(day, hour){
    }
    void addStudent(const string& name) {
        LabRecords* record(new LabRecords(name));
        records.push_back(record);
        number_of_students ++;
    }
    void addGrade(const string& name, int week, int grade) {
        for (LabRecords* record : records){
            if (record->getName() == name){
                record->addGrade(week, grade);
            }
        }
    }
    ~Section() {
        cout << "Deleting Section " << sec_name << endl;
        for (LabRecords* record : records) {
            cout << "Deleting " << record->getName() << endl;
            delete record;
            record = nullptr;
        }
    }
    Section(const Section& anotherSection)  : sec_name(anotherSection.sec_name), date(anotherSection.date), number_of_students(anotherSection.number_of_students){
        for (const LabRecords* record : anotherSection.records) {
            records.push_back(new LabRecords(*record));
        }
    }
private:
    vector<LabRecords*> records;
    string sec_name;
    Time date;
    int number_of_students = 0;
};

ostream& operator<<(ostream& os, const Section& sec) {
    os << "Section: " << sec.sec_name << ", Time slot: " << sec.date
       << ", ";
    if (sec.number_of_students == 0){
        os << "Students: None";
    }
    else {
        os <<  "Students: " << endl;
        for (const LabRecords* record : sec.records) {
            os  << *record;
        }
    }
    return os;
}

//Section: A2, Time slot: [Day: Tuesday, Start time: 4pm], Students: None
class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& worker);
public:
    LabWorker(const string& name) : worker_name(name) {}

    void addGrade(const string& name, int grade, int week) {
        lab_section->addGrade(name, week, grade);
    }
    void addSection(Section& section) {
        lab_section = &section;
    }
private:
    string worker_name;
    Section* lab_section = nullptr;
        };

ostream& operator<<(ostream& os, const LabWorker& worker) {
    if (worker.lab_section == nullptr) {
        os << worker.worker_name << " does not have a section";
    }
    else {
        os << worker.worker_name << " has " << *(worker.lab_section);
    }
    return os;
}

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

} // main
