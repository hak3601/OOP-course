#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include <string>
#include <vector>
using namespace std;
class Student : public User{
private:
    vector<string> enroled_courses;

public:
    Student(string, int);
    Student(const Student&);
    ~Student();

    Student& operator=(const Student&);

    friend void displayEnroledCourses();
    friend void take_exam();
};


#endif 