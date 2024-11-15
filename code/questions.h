#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>

using namespace std;

// Base class for a generic Question
class Question {
protected:
    int idx;
    string question_text;
    int point;

public:
    Question(int, const string&, int);
    virtual ~Question() {}

    virtual void display() const = 0;

    virtual int getIdx();
    virtual string getQuestionText();
    virtual int getpoint();
    
};

// Derived class for True/False Question
class TrueFalseQuestion : public Question {
    bool correctAnswer;

public:
    TrueFalseQuestion(int, const string&, int, bool);

    void display() const override;
};

// Derived class for Multiple Choice Question
class MultipleChoiceQuestion : public Question {
    vector<string> options;
    string correct_answer;

public:
    MultipleChoiceQuestion(int, const string&, int, const vector<string>&, const string&);

    void display() const override;
};

// Derived class for Completion (Fill in the Blank) Question
class CompletionQuestion : public Question {
    string correct_answer;

public:
    CompletionQuestion(int, const string&, int, const string&);

    void display() const override;
};

#endif // QUESTIONS_H