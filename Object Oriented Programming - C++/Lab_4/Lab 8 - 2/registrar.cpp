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

    ostream &operator<<(ostream &os, const Registrar &rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (Course *course: rhs.courses) {
            os << *course << endl;
        }
        os << "Students: " << endl;
        for (Student *stud: rhs.students) {
            os << *stud << endl;
        }
        return os;
    }

    Registrar::Registrar() {}

    bool Registrar::addCourse(const string &course_name) {
        bool exists = false;
        for (Course *course: courses) {
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


    bool Registrar::addStudent(const string &stud_name) {
        bool exists = false;
        for (Student *student: students) {
            if (stud_name == student->getName()) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << "Student is already added!" << endl;
            return false;
        } else {
            students.push_back(new Student(stud_name));
            return true;
        }
    }

    bool Registrar::enrollStudentInCourse(const string &studentName, const string &courseName) {
        for (Course *course: courses) {
            if (course->getName() == courseName) {
                for (Student *stud: students) {
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

    bool Registrar::cancelCourse(const string &courseName) {
        for (Course *course: courses) {
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
        for (Course *course: courses) {
            delete course;
        }
        for (Student *student: students) {
            delete student;
        }
        courses.clear();
        students.clear();
    }

    size_t Registrar::findCourse(const string &course_name) const {
        for (std::size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == course_name) {
                return i;
            }
        }
        return -1;
    }

    size_t Registrar::findStudent(const string &stud_name) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() == stud_name) {
                return i;
            }
        }
        return -1;
    }

}