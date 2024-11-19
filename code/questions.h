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
    string correct_answer;

public:
    Question(int, const string&, int, const string&);

    virtual void display() const = 0;

    virtual int getIdx();
    virtual string getQuestionText();
    virtual int getpoint();
    virtual bool grade(string);
};

// Derived class for True/False Question
class TrueFalseQuestion : public Question {
private:

public:
    TrueFalseQuestion(int, const string&, int, const string&);
    bool grade(string);
    void display() const override;
};

// Derived class for Multiple Choice Question
class MultipleChoiceQuestion : public Question {
private:
    string options;
    

public:
    MultipleChoiceQuestion(int, const string&, int, const string&, const string&);
    bool grade(string);
    void display() const override;
};

// Derived class for Completion (Fill in the Blank) Question
class CompletionQuestion : public Question {
private:
    string correct_answer;

public:
    CompletionQuestion(int, const string&, int, const string&);
    bool grade(string);
    void display() const override;
};

#endif // QUESTIONS_H