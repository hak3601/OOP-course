#include "questions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

Question::Question(int idx, const string &text, int point)
        : idx(idx), question_text(text), point(point) {}
int Question::getIdx() {return idx;}
string Question::getQuestionText() {return question_text;}
int Question::getpoint() {return point;}

TrueFalseQuestion::TrueFalseQuestion(int idx, const string &text, int point, bool correctAns)
        : Question(idx, text, point), correctAnswer(correctAns) {}
void TrueFalseQuestion::display() const{
    printf("%d. %s (%s points)\nT/F? >> ", idx, question_text, point);
}


MultipleChoiceQuestion::MultipleChoiceQuestion(int idx, const string &text, int point, const vector<string> &opts, const string &correctans)
        : Question(idx, text, point), options(opts), correct_answer(correctans) {}
void MultipleChoiceQuestion::display() const{
    printf("%d. %s (%d points)", idx, question_text, point);
    for(const auto& op : options){
        cout << op << endl;
    }
    cout << "Which is correct? >> ";
}

CompletionQuestion::CompletionQuestion(int idx, const string &text, int point, const string &correctans)
        : Question(idx, text, point), correct_answer(correctans) {}
void CompletionQuestion::display() const{
    printf("%d. %s (%d points)\nFill in the blank >> ", idx, question_text, point);
}
