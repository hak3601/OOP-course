#ifndef EXAM_H
#define EXAM_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "user.h"
#include "questions.h" // Include the questions header
//#include "dynamic_difficulty_engine.h"
using namespace std;

// Class representing an Exam
class Exam {
protected:
    string exam_title;
    string datafolder;
    User* object_user;
    
    vector<Question*> questions;
    int duration; // in minutes
    chrono::system_clock::time_point start_time;
    int total_score;

public:
    Exam(const string &,const string &);
    ~Exam();
    virtual void startExam();
    virtual void endExam() = 0; // will be called when exam is over and will update the test result file
    virtual void displayQuestions() const = 0; // ~
    virtual void recordScore(const string &, int) = 0; // 
    virtual void printSummary() const = 0;
};

class TrainExam : public Exam{
private:
    //DynamicDifficultyEngine DDE;
    vector<vector<string>> individual_problem_RW_tracker; 
public:
    // void startExam(); // will be called in main
    // void endExam(); // will be called when exam is over and will update the test result file
    // void displayQuestions() const; // ~
    // void recordScore(const string &, int); // 
    // void printSummary() const;
};

class TestExam : public Exam{
private:
    int max_score;
public:
    TestExam(const string &,const string &);
    ~TestExam();
    void startExam(); // will be called in main
    void setMaxScore();
    void timeIsOver();
    void endExam(); // will be called when exam is over and will update the test result file
    void displayQuestions() const; // ~
    void recordScore(const string &, int); // 
    void printSummary() const;
};

#endif // EXAM_H