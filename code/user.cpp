#include "user.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class User{
protected:
    string name;
    string id;
public:
    User(string user_name, string user_id) : name(user_name), id(user_id) {}
    User(const User &other) : name(other.name), id(other.id) {}
    virtual ~User() {}


    string getName(){return name;}
    string getId(){return id;}
};

class Student : public User{
private:
    vector<string> enroled_courses;

public:
    Student() : User("NULL", "NULL") {}
    Student(string student_name, string student_id, vector<string> student_enroled_courses)
        : User(student_name, student_id), enroled_courses(student_enroled_courses) {}
    Student(const Student& other)
        : User(other), enroled_courses(other.enroled_courses) {}
    ~Student() {}

    Student& operator=(const Student& other) {
    if (this != &other) { // Self-assignment check
        User::operator=(other); // Use assignment operator of base class
        enroled_courses = other.enroled_courses; // Assign vector
    }
    return *this;
    }

    void displayEnroledCourses(){
        printf("<Currently enroled courses by '%s'>", getName());
        for(const auto& course : enroled_courses){
            cout << course << endl;
        }
    }
    void take_exam();
};