#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "questions.h"
using namespace std;

vector<string> fetchEnroledOrInstructing(const string&, const string&, const string&, const string&);
vector<string> parseString2Vec(string);
vector<vector<string>> readCSV(const string&, const string&);
vector<Question*> vec2Questions(vector<vector<string>>);
void setTextColor(int foreground, int background);
void resetTextColor();
void clearConsole();