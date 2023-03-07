//
// Created by Suvir Wadhwa on 24/10/21.
//
#include <iostream>
#include <string>
#include <vector>

#ifndef LAB_9_STUDENT_H
#define LAB_9_STUDENT_H

namespace Albert {

    class Course;

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);

    public:
        // Student methods needed by Registrar
        Student(const std::string &name);

        const std::string &getName() const;

        bool addCourse(Course *course);

        // Student method needed by Course
        void removedFromCourse(Course* course);

    private:
        std::string name;
        std::vector<Course*> courses;
    };

}

#endif //LAB_9_STUDENT_H