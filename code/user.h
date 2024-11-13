#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;
class User{
private:
    string name;
    int id;
public:
    User(string);
    User(int );
    User(const User&);
    ~User();
};

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