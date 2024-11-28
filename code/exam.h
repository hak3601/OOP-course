#ifndef EXAM_H
#define EXAM_H

#include <string>
#include <vector>
#include <map>
#include "user.h"
#include "questions.h" // Include the questions header
#include "dynamic_difficulty_engine.h"
using namespace std;

// Class representing an Exam
class Exam
{
protected:
    string exam_title;
    string datafolder;
    const User *object_user;

    vector<Question *> questions;
    int total_score = 0;
    int cur_idx = 0;
    string examfile;

public:
    Exam(const string &, const string &, const User *, const string &);
    virtual void startExam() = 0;
    virtual void endExam() = 0;          // will be called when exam is over and will update the test result file
    virtual void displayQuestions() = 0; // ~
    virtual void printSummary() const = 0;
};

class TrainExam : public Exam
{
private:
    DynamicDifficultyEngine *DDE;
    vector<vector<string>> individual_problem_RW_tracker;
    int cur_total_score = 0;
    int cur_gained_score = 0;
    string prof_name;
    vector<string> user_taken_questions;
    vector<vector<string>> user_taken_answers;

public:
    TrainExam(const string &, const string &, const User *, const string &, const string &);
    void startExam();        // will be called in main
    void endExam();          // will be called when exam is over and will update the test result file
    void displayQuestions(); // ~
    void printSummary() const;
    void displayQuestionList() const;
    void editAnswer(string);
};

class TestExam : public Exam
{
private:
    int max_score = 0;
    string prof_name;
    vector<string> answers;

public:
    TestExam(const string &, const string &, const User *, const string &, const string &);
    void startExam();        // will be called in main
    void endExam();          // will be called when exam is over and will update the test result file
    void displayQuestions(); // ~
    void printSummary() const;
    int handleEndOfExam();
    void displayQuestionList() const;
    void editAnswer(const string &);
    void goToPreviousQuestion();
    void handlePostNavigationOptions();
    void saveToCSV() const;
    void goToNextQuestion();
    void goToAnotherQuestion();
    int getCurrentIndex() const;
    string getProfessorName() const;
};

#endif // EXAM_H