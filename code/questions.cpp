#include "questions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// Helper function to trim whitespace from a string
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Implementation of display function for TrueFalseQuestion
void TrueFalseQuestion::display() const {
    cout << "Question: " << questionText << endl;
    cout << "Please enter 'True' or 'False': " << endl;
}

// Implementation of grade function for TrueFalseQuestion
int TrueFalseQuestion::grade(const string &answer) {
    string lowerAnswer = answer;
    transform(lowerAnswer.begin(), lowerAnswer.end(), lowerAnswer.begin(), ::tolower);
    
    bool isCorrect = (correctAnswer && lowerAnswer == "true") || (!correctAnswer && lowerAnswer == "false");
    return isCorrect ? maxScore : 0;
}

void loadTrueFalseQuestionsFromCSV(const string &filePath, vector<Question*> &questions) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, questionText, correctAnswerStr, maxScoreStr;

        // Read CSV values
        if (getline(ss, id, ',') &&
            getline(ss, questionText, ',') &&
            getline(ss, correctAnswerStr, ',') &&
            getline(ss, maxScoreStr)) {

            // Trim whitespace
            questionText = trim(questionText);
            correctAnswerStr = trim(correctAnswerStr);
            maxScoreStr = trim(maxScoreStr);

            // Convert the max score from string to integer with error handling
            int maxScore;
            try {
                maxScore = stoi(maxScoreStr);
            } catch (const invalid_argument&) {
                cerr << "Error: Invalid score in CSV file for question: " << questionText << endl;
                continue;
            }

            // Convert the correct answer from string to boolean (case-insensitive)
            transform(correctAnswerStr.begin(), correctAnswerStr.end(), correctAnswerStr.begin(), ::tolower);
            if (correctAnswerStr != "true" && correctAnswerStr != "false") {
                cerr << "Error: Invalid correct answer in CSV file for question: " << questionText << endl;
                continue;
            }
            bool correctAnswer = (correctAnswerStr == "true");

            // Create a new TrueFalseQuestion and add it to the vector
            questions.push_back(new TrueFalseQuestion(questionText, maxScore, correctAnswer));
        } else {
            cerr << "Error: Malformed CSV line - " << line << endl;
        }
    }

    file.close();
}
