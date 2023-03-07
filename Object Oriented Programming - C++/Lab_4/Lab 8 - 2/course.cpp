//
// Created by Suvir Wadhwa on 24/10/21.
//
//#include "registrar.h"
#include "course.h"
#include "registrar.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Albert {

    Course::Course(const string& courseName) : name(courseName) {}

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

    const string &Course::getName() const { return name; }

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

}