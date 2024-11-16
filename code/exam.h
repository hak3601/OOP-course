#ifndef EXAM_H
#define EXAM_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "user.cpp"
#include "questions.cpp" // Include the questions header
#include "dynamic_difficulty_engine.cpp"
using namespace std;

// Class representing an Exam
class Exam {
protected:
    User* object_user;
    string exam_title;
    vector<Question*> questions;
    int duration; // in minutes
    chrono::system_clock::time_point start_time;
    int total_score;
    vector<vector<string>> individual_problem_RW_tracker; 

public:
    Exam(const string &title, vector<Question*> qs);
    ~Exam();

    virtual void startExam() = 0; // will be called in main
    virtual void endExam() = 0; // will be called when exam is over and will update the test result file
    virtual void displayQuestions() const = 0; // ~
    virtual void recordScore(const string &user_id, int score) = 0; // 
    virtual void printSummary() const = 0;
};

class TrainExam : public Exam{
private:
    DynamicDifficultyEngine DDE;
public:

};

class TestExam : public Exam{
private:
    int max_score;
public:

};

#endif // EXAM_H