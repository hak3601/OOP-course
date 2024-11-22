#include "user.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

User::User(string user_name, string user_id) : name(user_name), id(user_id) {}
User::User(const User &other) : name(other.name), id(other.id) {}


/*-------------------------------------------------------------------------------------------*/
Student::Student() : User("NULL", "NULL") {}
Student::Student(string student_name, string student_id, vector<string> student_enroled_courses)
        : User(student_name, student_id), enroled_courses(student_enroled_courses) {}
Student::Student(const Student& other)
        : User(other), enroled_courses(other.enroled_courses) {}
Student::~Student() {}
string Student::getName()const {return name;}
string Student::getId()const {return id;}

Student& Student::operator=(const Student& other) {
    if (this != &other) { // Self-assignment check
        User::operator=(other); // Use assignment operator of base class
        enroled_courses = other.enroled_courses; // Assign vector
    }
    return *this;
}

vector<string> Student::getInternalContent() {return enroled_courses;}
void Student::displayCourses(){
    for(const auto& c_name : enroled_courses){
        cout << "- " << c_name << endl;
    }
}
void Student::take_exam(){}

/*-------------------------------------------------------------------------------------------*/
vector<string> Professor::getInternalContent() {return instructing_courses;}

Professor::Professor() : User("NULL", "NULL") {}
Professor::Professor(string prof_name, string prof_id, vector<string> prof_instructing_courses)
        : User(prof_name, prof_id), instructing_courses(prof_instructing_courses) {}
Professor::Professor(const Professor& other)
        : User(other), instructing_courses(other.instructing_courses) {}
Professor::~Professor() {}
string Professor::getName() const{return name;}
string Professor::getId() const{return id;}
Professor& Professor::operator=(const Professor& other) {
    if (this != &other) { // Self-assignment check
        User::operator=(other); // Use assignment operator of base class
        instructing_courses = other.instructing_courses; // Assign vector
    }
    return *this;
}
void Professor::displayCourses(){}
void Professor::create_exam(){}
void Professor::mark_exam(){}
void Professor::comment_exam(){}