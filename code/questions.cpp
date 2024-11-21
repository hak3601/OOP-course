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
string Question::getCorrectAnswer() {return correct_answer;}
Question::~Question() {};

TrueFalseQuestion::TrueFalseQuestion(string q_ver ,int idx, const string &text, int point, const string& correct_answer)
        : q_ver(q_ver), Question(idx, text, point, correct_answer) {}

string TrueFalseQuestion::display() const{
    return question_text + " (" + to_string(point) + " points)";
}

int TrueFalseQuestion::grade(string user_ans){
    string converted_ans = "";
    if (!user_ans.compare("None")){
        return 0;
    }
    if(!user_ans.compare("t") || !user_ans.compare("T") || !user_ans.compare("true") || !user_ans.compare("True")) converted_ans = "True";
    else if(!user_ans.compare("f") || !user_ans.compare("F") || !user_ans.compare("false") || !user_ans.compare("False")) converted_ans = "False";
    if(!converted_ans.compare(correct_answer)){
        return point;
    } else{
        return 0;
    }
}


MultipleChoiceQuestion::MultipleChoiceQuestion(string q_ver,int idx, const string &text, int point, const string &opts, const string& correct_answer)
        : q_ver(q_ver),Question(idx, text, point, correct_answer), options(opts) {}
string MultipleChoiceQuestion::display() const{
    return question_text + " (" + to_string(point) + " points)\n" + options;
}

int MultipleChoiceQuestion::grade(string user_ans){
    if (user_ans == "None"){
        return 0;
    } else if(!user_ans.compare(correct_answer)){
        return point;
    } else{
        return 0;
    }
}
string TrueFalseQuestion::getQversion(){return q_ver;}
string MultipleChoiceQuestion::getQversion(){return q_ver;}
string CompletionQuestion::getQversion(){return q_ver;}
string MultipleChoiceQuestion::getOptions(){return options;}
string TrueFalseQuestion::getOptions(){return "";}
string CompletionQuestion::getOptions(){return " ";}
CompletionQuestion::CompletionQuestion(string q_ver,int idx, const string &text, int point, const string& correct_answer)
        : q_ver(q_ver),Question(idx, text, point, correct_answer) {}
string CompletionQuestion::display() const{
    return question_text + " (" + to_string(point) + " points)";
}
int CompletionQuestion::grade(string user_ans){
    if (user_ans == "None"){
        return 0;
    } else if(!user_ans.compare(correct_answer)){
        return point;
    } else{
        return 0;
    }
    
}
