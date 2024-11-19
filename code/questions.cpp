#include "questions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

Question::Question(int idx, const string& text, int point) : idx(idx), question_text(text), point(point) {};

TrueFalseQuestion::TrueFalseQuestion(int idx, const string &text, int point, bool correctAns)
        : Question(idx, text, point), correct_answer(correctAns) {}
void TrueFalseQuestion::display() const{
    printf("%d. %s (%s points)\nt/f? >> ", idx, question_text, point);
}
bool TrueFalseQuestion::grade(string user_ans){
    bool boolean_user_ans;
    if(!user_ans.compare("t") || !user_ans.compare("T") || !user_ans.compare("true") || !user_ans.compare("True")) boolean_user_ans = true;
    else if(!user_ans.compare("f") || !user_ans.compare("F") || !user_ans.compare("false") || !user_ans.compare("False")) boolean_user_ans = false;
    return boolean_user_ans == correct_answer;
}

MultipleChoiceQuestion::MultipleChoiceQuestion(int idx, const string &text, int point, const string &opts, const string &correctans)
        : Question(idx, text, point), options(opts), correct_answer(correctans) {}
void MultipleChoiceQuestion::display() const{
    printf("%d. %s (%d points)", idx, question_text, point);
    for(const auto& op : options){
        cout << op << endl;
    }
    cout << "Which is correct? >> ";
}
bool MultipleChoiceQuestion::grade(string user_ans){
    return !user_ans.compare(correct_answer);
}


CompletionQuestion::CompletionQuestion(int idx, const string &text, int point, const string &correctans)
        : Question(idx, text, point), correct_answer(correctans) {}
void CompletionQuestion::display() const{
    printf("%d. %s (%d points)\nFill in the blank >> ", idx, question_text, point);
}
bool CompletionQuestion::grade(string user_ans){
    return !user_ans.compare(correct_answer);
}