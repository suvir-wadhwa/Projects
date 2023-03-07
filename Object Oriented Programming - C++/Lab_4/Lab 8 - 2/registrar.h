//
// Created by Suvir Wadhwa on 24/10/21.
//

#include <iostream>
#include <string>
#include <vector>

#ifndef LAB_9_REGISTRAR_H
#define LAB_9_REGISTRAR_H

namespace Albert {

    class Course;
    class Student;

    class Registrar {
        friend std::ostream &operator<<(std::ostream &os, const Registrar &rhs);

    public:
        Registrar();

        bool addCourse(const std::string &course_name);

        bool addStudent(const std::string &stud_name);

        bool enrollStudentInCourse(const std::string &studentName, const std::string &courseName);

        bool cancelCourse(const std::string &courseName);

        void purge();

    private:
        std::size_t findStudent(const std::string &stud_name) const;

        std::size_t findCourse(const std::string &course_name) const;

        std::vector<Course *> courses;
        std::vector<Student*> students;

    };

}
#endif //LAB_9_REGISTRAR_H