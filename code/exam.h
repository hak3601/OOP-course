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
    int max_score;

public:
    Exam(const string &title, vector<Question*> qs);
    ~Exam();

    void startExam();
    void endExam();
    void displayQuestions() const;
    void recordScore(const string &user_id, int score);
    void publishResults() const;
    void printSummary() const;
};

class TrainExam : public Exam{
private:
    DynamicDifficultyEngine DDE;
public:

};

class TestExam : public Exam{
private:

public:

};

#endif // EXAM_H