#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;
class User{
protected:
    string name;
    string id;
public:
    User(string, string);
    User(const User&);
    ~User();

    string getName();
    string getId();
};

class Student : public User{
private:
    vector<string> enroled_courses;

public:
    Student();
    Student(string, string, vector<string>);
    Student(const Student&);
    ~Student();

    Student& operator=(const Student&);

    vector<string> getEnroledCourses();
    void take_exam();
};

class Professor : public User{
private:
    vector<string> instructing_courses;

public:
    Professor();
    Professor(string, string, vector<string>);
    Professor(const Professor&);
    ~Professor();

    Professor& operator=(const Professor&);

    vector<string> getInstructingCourses();
    void displayInstructingCourses();
    void create_exam();
    void mark_exam();
    void comment_exam();
};

#endif 