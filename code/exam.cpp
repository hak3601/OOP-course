#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "utils.cpp"
#include "exam.h"
#include "questions.h"
using namespace std;




Exam::Exam(const string &title, const string &datafolder) : exam_title(title), datafolder(datafolder) {}
Exam::~Exam() {}

/*-------------------------------------------------------------------------------------------*/
void TestExam::startExam() { // the main function of test exam
    string prof_name = "Prof.Ko";
    string exam_file_name = exam_title+"-test-"+prof_name+".csv";
    vector<vector<string>> raw_questions = readCSV(datafolder, exam_file_name);

    questions = vec2Questions(raw_questions);
    cout << exam_title << "Starts now.";
    
    endExam();
}

TestExam::TestExam(const string &title, const string &datafolder) : Exam(title,datafolder) {}
TestExam::~TestExam() {}
void TestExam::setMaxScore(){
    
}
void TestExam::endExam() {} // will be called when exam is over and will update the test result file
void TestExam::displayQuestions() const {} // ~
void TestExam::recordScore(const string &, int) {} // 
void TestExam::printSummary() const {}


