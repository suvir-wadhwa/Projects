/*
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* student);
    void removeStudentsFromCourse();
private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* course);
    // Student method needed by Course
    void removedFromCourse(Course* course);
private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& course_name);
    bool addStudent(const string& stud_name);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string& stud_name) const {
        for (size_t i = 0; i < students.size(); i ++) {
            if (students[i]->getName() == stud_name) {
                return i;
            }
        }
        return -1;
    }
    size_t findCourse(const string& course_name) const {
        for (size_t i = 0; i < courses.size(); i ++) {
            if (courses[i]->getName() == course_name) {
                return i;
            }
        }
        return -1;
    }
    vector<Course*> courses;
    vector<Student*> students;
};

int main() {
    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

// Methods for Courses
ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.empty()) {
        os << "No Students" << endl;
    }
    else {
        for (Student* student : rhs.students) {
            os << student->getName() << " ";
        }
    }
    return os;
}

Course::Course(const string& courseName) : name(courseName) {}
const string& Course::getName() const {return name; }
bool Course::addStudent(Student* student) {
    bool exists = false;
    for (Student* stud : students) {
        if (stud == student) {
            exists = true;
            break;
        }
    }
    if (exists) {
        cout << "Student exists in course!" << endl;
        return false;
    }
    else {
        students.push_back(student);
        return true;
    }
}
void Course::removeStudentsFromCourse() {
    students.clear();
}

// Methods for Students
ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.empty()) {
        os << "No Courses" << endl;
    }
    else {
        for (Course* course: rhs.courses) {
            os << course->getName() << " ";
        }
    }
    return os;
}

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const {return name; }
bool Student::addCourse(Course* course) {
    bool exists = false;
    for (Course* cour : courses) {
        if (cour == course) {
            exists = true;
            break;
        }
    }
    if (exists) {
        cout << "Course is already present!" << endl;
        return false;
    }
    else {
        courses.push_back(course);
        return true;
    }
}

// Student method needed by Course
void Student::removedFromCourse(Course* course) {
    size_t index = 0;
    for (Course* cour : courses) {
        if (cour->getName() == course->getName()) {
            break;
        }
    }
    for (size_t j = index + 1; j < courses.size(); j++){
        courses[j - 1] = courses[j];
    }
    courses.pop_back();
}

// Methods for Registrar:
ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report" << endl;
    os << "Courses: " << endl;
    for (Course* course : rhs.courses) {
        os << *course << endl;
    }
    os << "Students: " << endl;
    for (Student* stud : rhs.students) {
        os << *stud << endl;
    }
    return os;
}

Registrar::Registrar() {}

bool Registrar::addCourse(const string& course_name) {
    bool exists = false;
    for (Course* course : courses) {
        if (course_name == course->getName()) {
            exists = true;
            break;
        }
    }
    if (exists) {
        cout << "Course is already added!" << endl;
        return false;
    }
    else {
        courses.push_back(new Course(course_name));
        return true;
    }
}


bool Registrar::addStudent(const string& stud_name) {
    bool exists = false;
    for (Student* student : students) {
        if (stud_name == student->getName()) {
            exists = true;
            break;
        }
    }
    if (exists) {
        cout << "Student is already added!" << endl;
        return false;
    }
    else {
        students.push_back(new Student(stud_name));
        return true;
    }
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    for (Course* course : courses) {
        if (course->getName() == courseName) {
            for (Student* stud : students) {
                if (stud->getName() == studentName) {
                    course->addStudent(stud);
                    stud->addCourse(course);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Registrar::cancelCourse(const string& courseName) {
    for (Course* course: courses) {
        size_t index = findCourse(courseName);
        if (course->getName() == courseName) {
            for (size_t j = index + 1; j < courses.size(); j++) {
                courses[j - 1] = courses[j];
            }
            courses.pop_back();
            for (Student *stud: students) {
                stud->removedFromCourse(course);
            }
            return true;
        }
    }
    return false;
}


void Registrar::purge() {
    for (Course* course : courses)
    {
        delete course;
    }
    for (Student* student : students) {
        delete student;
    }
    courses.clear();
    students.clear();
}
