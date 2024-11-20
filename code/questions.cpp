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


TrueFalseQuestion::TrueFalseQuestion(string q_ver ,int idx, const string &text, int point, const string& correct_answer)
        : q_ver(q_ver), Question(idx, text, point, correct_answer) {}
void TrueFalseQuestion::display() const{
    cout << idx << ". " << question_text << " (" << point << " points)\nt/f? >> ";
}
int TrueFalseQuestion::grade(string user_ans){
    string converted_ans = "";
    if (!user_ans.compare("None")){
        return 0;
    }
    if(!user_ans.compare("t") || !user_ans.compare("T") || !user_ans.compare("true") || !user_ans.compare("True")) converted_ans = "True";
    else if(!user_ans.compare("f") || !user_ans.compare("F") || !user_ans.compare("false") || !user_ans.compare("False")) converted_ans = "False";
    return 0==converted_ans.compare(correct_answer);
}


MultipleChoiceQuestion::MultipleChoiceQuestion(string q_ver,int idx, const string &text, int point, const string &opts, const string& correct_answer)
        : q_ver(q_ver),Question(idx, text, point, correct_answer), options(opts) {}
void MultipleChoiceQuestion::display() const{
    cout << idx << ". " << question_text << " (" << point << " points)";
    for(const auto& op : options){
        cout << op << endl;
    }
    cout << "Which is correct? >> ";
}
int MultipleChoiceQuestion::grade(string user_ans){
    if (user_ans == "None"){
        return 0;
    }
    return !user_ans.compare(correct_answer);
}
string TrueFalseQuestion::getQversion(){return q_ver;}
string MultipleChoiceQuestion::getQversion(){return q_ver;}
string CompletionQuestion::getQversion(){return q_ver;}
string MultipleChoiceQuestion::getOptions(){return options;}
string TrueFalseQuestion::getOptions(){return "";}
string CompletionQuestion::getOptions(){return " ";}
CompletionQuestion::CompletionQuestion(string q_ver,int idx, const string &text, int point, const string& correct_answer)
        : q_ver(q_ver),Question(idx, text, point, correct_answer) {}
void CompletionQuestion::display() const{
    cout << idx << ". " << question_text << " (" << point << " points)\nFill in the blank >> ";
}
int CompletionQuestion::grade(string user_ans){
    if (user_ans == "None"){
        return 0;
    }
    return !user_ans.compare(correct_answer);
}