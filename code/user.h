#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

class User
{
protected:
    string name;
    string id;

public:
    User(string, string);

    virtual string getName() const = 0;
    virtual string getId() const = 0;
    virtual vector<string> getInternalContent() const = 0;
    virtual void displayCourses() const = 0;
};

class Student : public User
{
private:
    vector<string> enroled_courses;

public:
    Student(string, string, vector<string>);

    vector<string> getInternalContent() const;
    void displayCourses() const;
    string getName() const;
    string getId() const;
};

class Professor : public User
{
private:
    vector<string> instructing_courses;

public:
    Professor(string, string, vector<string>);

    vector<string> getInternalContent()const;
    void displayCourses()const;
    string getName() const;
    string getId() const;
};

#endif