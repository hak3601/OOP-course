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
    User();
    User(string, string);
    User(const User&);
    virtual ~User() = default;

    string getName();
    string getId();
    virtual vector<string> getInternalContent() = 0;
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

    vector<string> getInternalContent();
    void displayInstructingCourses();
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

    vector<string> getInternalContent()override;
    void displayInstructingCourses();
    void create_exam();
    void mark_exam();
    void comment_exam();
};

#endif 