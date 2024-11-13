#ifndef EXAM_H
#define EXAM_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "questions.h" // Include the questions header

// Class representing an Exam
class Exam {
    std::string examTitle;
    std::vector<Question*> questions;
    int duration; // in minutes
    std::chrono::system_clock::time_point startTime;
    std::map<std::string, int> userScores; // Maps user IDs to scores
    std::map<std::string, std::string> userComments; // Maps user IDs to comments

public:
    Exam(const std::string &title, int dur);
    ~Exam();

    void addQuestion(Question *question);
    void startExam();
    void endExam();
    void displayQuestions() const;
    void recordScore(const std::string &userID, int score);
    void addComment(const std::string &userID, const std::string &comment);
    void publishResults() const;
    void printSummary() const;
};

#endif // EXAM_H