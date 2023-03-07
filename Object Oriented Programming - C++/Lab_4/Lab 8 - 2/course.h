//
// Created by Suvir Wadhwa on 24/10/21.
//

#include <iostream>
#include <string>
#include <vector>

#ifndef LAB_9_COURSE_H
#define LAB_9_COURSE_H

namespace Albert {

    class Student;


    class Course {
        friend std::ostream &operator<<(std::ostream &os, const Course &rhs);

    public:
        // Course methods needed by Registrar
        Course(const std::string &courseName);

        const std::string& getName() const;

        bool addStudent(Student *student);

        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    };

}

#endif //LAB_9_COURSE_H