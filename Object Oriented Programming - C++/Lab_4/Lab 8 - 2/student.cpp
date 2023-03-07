//
// Created by Suvir Wadhwa on 24/10/21.
//
#include <iostream>
#include <string>
#include <vector>
#include "registrar.h"
#include "course.h"
#include "student.h"
using namespace std;

namespace Albert {

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

    const string &Student::getName() const { return name; }

    bool Student::addCourse(Course *course) {
        bool exists = false;
        for (Course *cour: courses) {
            if (cour == course) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << "Course is already present!" << endl;
            return false;
        } else {
            courses.push_back(course);
            return true;
        }
    }

// Student method needed by Course
    void Student::removedFromCourse(Course *course) {
        size_t index = 0;
        for (Course *cour: courses) {
            if (cour->getName() == course->getName()) {
                break;
            }
        }
        for (size_t j = index + 1; j < courses.size(); j++) {
            courses[j - 1] = courses[j];
        }
        courses.pop_back();
    }

}