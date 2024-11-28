#include "user.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

User::User(string user_name, string user_id) : name(user_name), id(user_id) {}

/*-------------------------------------------------------------------------------------------*/
Student::Student(string student_name, string student_id, vector<string> student_enroled_courses)
    : User(student_name, student_id), enroled_courses(student_enroled_courses) {}
string Student::getName() const { return name; }
string Student::getId() const { return id; }

vector<string> Student::getInternalContent() { return enroled_courses; }
void Student::displayCourses()
{
    int idx = 1;
    for (const auto &c_name : enroled_courses)
    {
        cout << idx << ". " << c_name << endl;
        idx++;
    }
}

/*-------------------------------------------------------------------------------------------*/
vector<string> Professor::getInternalContent() { return instructing_courses; }

Professor::Professor(string prof_name, string prof_id, vector<string> prof_instructing_courses)
    : User(prof_name, prof_id), instructing_courses(prof_instructing_courses) {}
string Professor::getName() const { return name; }
string Professor::getId() const { return id; }

void Professor::displayCourses()
{
    int idx = 1;
    for (const auto &c_name : instructing_courses)
    {
        cout << idx << ". " << c_name << endl;
        idx++;
    }
}