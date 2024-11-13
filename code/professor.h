#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "user.h"
#include <string>
#include <vector>
using namespace std;
class Professor : public User{
private:
    vector<string> instructing_courses;

public:
    Professor(string, int);
    Professor(const Professor&);
    ~Professor();

    Professor& operator=(const Professor&);

    friend void displayInstructingCourses();
    friend void create_exam();
    friend void mark_exam();
    friend void comment_exam();
};


#endif 