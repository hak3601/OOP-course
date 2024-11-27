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
    User(const User &);

    virtual string getName() const = 0;
    virtual string getId() const = 0;
    virtual vector<string> getInternalContent() = 0;
    virtual void displayCourses() = 0;
};

class Student : public User
{
private:
    vector<string> enroled_courses;

public:
    Student();
    Student(string, string, vector<string>);
    Student(const Student &);

    Student &operator=(const Student &);

    vector<string> getInternalContent();
    void displayCourses();
    void take_exam();
    string getName() const;
    string getId() const;
};

class Professor : public User
{
private:
    vector<string> instructing_courses;

public:
    Professor();
    Professor(string, string, vector<string>);
    Professor(const Professor &);

    Professor &operator=(const Professor &);

    vector<string> getInternalContent();
    void displayCourses();
    void create_exam();
    void mark_exam();
    void comment_exam();
    string getName() const;
    string getId() const;
};

#endif