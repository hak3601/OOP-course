#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "questions.h"
using namespace std;

vector<string> listFilesInDirectory(const string&, vector<string>&, const string&);
string generateRandomCode();
void printButton(const vector<string>&);
vector<string> fetchEnroledOrInstructing(const string&, const string&, const string&, const string&);
vector<string> parseString2Vec(string);
vector<vector<string>> readCSV(const string&, const string&);
vector<Question*> vec2Questions(vector<vector<string>>);
void setTextColor(int foreground, int background);
void resetTextColor();
void clearConsole();
vector<string> splitString2CourseAndProf(string);
void copyCSV(const string&, const string&);