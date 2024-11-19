#include "questions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

Question::Question(int idx, const string& text, int point, const string& correct_answer) : idx(idx), question_text(text), point(point), correct_answer(correct_answer) {};
int Question::getIdx() {return idx;}
string Question::getQuestionText() {return question_text;}
int Question::getpoint() {return point;}
string Question::getCurrectAnswer() {return correct_answer;}


TrueFalseQuestion::TrueFalseQuestion(int idx, const string &text, int point, const string& correct_answer)
        : Question(idx, text, point, correct_answer) {}
void TrueFalseQuestion::display() const{
    printf("%d. %s (%s points)\nt/f? >> ", idx, question_text, point);
}
int TrueFalseQuestion::grade(string user_ans){
    string converted_ans = "";
    if(!user_ans.compare("t") || !user_ans.compare("T") || !user_ans.compare("true") || !user_ans.compare("True")) converted_ans = "True";
    else if(!user_ans.compare("f") || !user_ans.compare("F") || !user_ans.compare("false") || !user_ans.compare("False")) converted_ans = "False";
    return 0==converted_ans.compare(correct_answer);
}


MultipleChoiceQuestion::MultipleChoiceQuestion(int idx, const string &text, int point, const string &opts, const string& correct_answer)
        : Question(idx, text, point, correct_answer), options(opts) {}
void MultipleChoiceQuestion::display() const{
    printf("%d. %s (%d points)", idx, question_text, point);
    for(const auto& op : options){
        cout << op << endl;
    }
    cout << "Which is correct? >> ";
}
int MultipleChoiceQuestion::grade(string user_ans){
    return !user_ans.compare(correct_answer);
}


CompletionQuestion::CompletionQuestion(int idx, const string &text, int point, const string& correct_answer)
        : Question(idx, text, point, correct_answer) {}
void CompletionQuestion::display() const{
    printf("%d. %s (%d points)\nFill in the blank >> ", idx, question_text, point);
}
int CompletionQuestion::grade(string user_ans){
    return !user_ans.compare(correct_answer);
}