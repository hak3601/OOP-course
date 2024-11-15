#include "user.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

User::User(string user_name, string user_id) : name(user_name), id(user_id) {}
User::User(const User &other) : name(other.name), id(other.id) {}
User::~User() {}
string User::getName() {return name;}
string User::getId() {return id;}

Student::Student() : User("NULL", "NULL") {}
Student::Student(string student_name, string student_id, vector<string> student_enroled_courses)
        : User(student_name, student_id), enroled_courses(student_enroled_courses) {}
Student::Student(const Student& other)
        : User(other), enroled_courses(other.enroled_courses) {}
Student::~Student() {}

Student& Student::operator=(const Student& other) {
    if (this != &other) { // Self-assignment check
        User::operator=(other); // Use assignment operator of base class
        enroled_courses = other.enroled_courses; // Assign vector
    }
    return *this;
}

vector<string> Student::getEnroledCourses() {return enroled_courses;}
vector<string> Professor::getInstructingCourses() {return instructing_courses;}

Professor::Professor() : User("NULL", "NULL") {}
Professor::Professor(string prof_name, string prof_id, vector<string> prof_instructing_courses)
        : User(prof_name, prof_id), instructing_courses(prof_instructing_courses) {}
Professor::Professor(const Professor& other)
        : User(other), instructing_courses(other.instructing_courses) {}
Professor::~Professor() {}

Professor& Professor::operator=(const Professor& other) {
    if (this != &other) { // Self-assignment check
        User::operator=(other); // Use assignment operator of base class
        instructing_courses = other.instructing_courses; // Assign vector
    }
    return *this;
}