#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "utils.cpp"
#include "exam.h"
#include "questions.h"
using namespace std;

Exam::Exam(const string &title, vector<Question*> qs) : exam_title(title), questions(qs) {}


