#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>

using namespace std;

// Base class for a generic Question
class Question
{
protected:
    int idx;
    string question_text;
    int point;
    string correct_answer;

public:
    Question(int, const string &, int, const string &);

    virtual string display() const = 0;
    virtual int getIdx();
    virtual string getQuestionText();
    virtual int getpoint();
    string getCorrectAnswer();
    virtual int grade(string) = 0;
    virtual string getQversion() = 0;
    virtual string getOptions() = 0;
};

// Derived class for True/False Question
class TrueFalseQuestion : public Question
{
private:
    string q_ver;

public:
    TrueFalseQuestion(string, int, const string &, int, const string &);
    int grade(string);
    string display() const;
    string getQversion();
    string getOptions();
};

// Derived class for Multiple Choice Question
class MultipleChoiceQuestion : public Question
{
private:
    string options;
    string q_ver;

public:
    MultipleChoiceQuestion(string, int, const string &, int, const string &, const string &);
    int grade(string);
    string display() const;
    string getQversion();
    string getOptions();
};

// Derived class for Completion (Fill in the Blank) Question
class CompletionQuestion : public Question
{
private:
    string q_ver;

public:
    CompletionQuestion(string, int, const string &, int, const string &);
    int grade(string);
    string display() const;
    string getQversion();
    string getOptions();
};

#endif // QUESTIONS_H