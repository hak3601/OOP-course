#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>

// Enum for question type
enum QuestionType {
    TRUE_FALSE,
    MULTIPLE_CHOICE,
    COMPLETION
};

// Base class for a generic Question
class Question {
protected:
    std::string questionText;
    QuestionType type;
    int maxScore;

public:
    Question(const std::string &text, QuestionType qType, int score)
        : questionText(text), type(qType), maxScore(score) {}
    virtual ~Question() {}

    virtual void display() const = 0;
    virtual int grade(const std::string &answer) = 0;

    int getMaxScore() const { return maxScore; }
    std::string getQuestionText() const { return questionText; }
};

// Derived class for True/False Question
class TrueFalseQuestion : public Question {
    bool correctAnswer;

public:
    TrueFalseQuestion(const std::string &text, int score, bool correctAns)
        : Question(text, TRUE_FALSE, score), correctAnswer(correctAns) {}

    void display() const override;
    int grade(const std::string &answer) override;
};

// Derived class for Multiple Choice Question
class MultipleChoiceQuestion : public Question {
    std::vector<std::string> options;
    std::string correctAnswer;

public:
    MultipleChoiceQuestion(const std::string &text, int score, const std::vector<std::string> &opts, const std::string &correctAns)
        : Question(text, MULTIPLE_CHOICE, score), options(opts), correctAnswer(correctAns) {}

    void display() const override;
    int grade(const std::string &answer) override;
};

// Derived class for Completion (Fill in the Blank) Question
class CompletionQuestion : public Question {
    std::string correctAnswer;

public:
    CompletionQuestion(const std::string &text, int score, const std::string &correctAns)
        : Question(text, COMPLETION, score), correctAnswer(correctAns) {}

    void display() const override;
    int grade(const std::string &answer) override;
};

#endif // QUESTIONS_H