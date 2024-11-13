#include "questions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Implementation of TrueFalseQuestion methods
void TrueFalseQuestion::display() const {
    cout << "Question: " << questionText << " (True/False)" << endl;
}

int TrueFalseQuestion::grade(const string &answer) {
    string userAnswer = answer;
    transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
    bool isCorrect = (userAnswer == "true" && correctAnswer) || (userAnswer == "false" && !correctAnswer);
    return isCorrect ? maxScore : 0;
}

// Utility function to trim whitespace and quotes
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\n\r\"'");
    size_t last = str.find_last_not_of(" \t\n\r\"'");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

// Function to load TrueFalseQuestions from CSV file
void loadTrueFalseQuestionsFromCSV(const string &fileName, vector<Question*> &questions) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return;
    }

    string line;
    // Read each line from the CSV file
    while (getline(file, line)) {
        stringstream ss(line);
        string author, course, type;
        getline(ss, author, ',');
        getline(ss, course, ',');
        getline(ss, type, ',');

        // Check if the type matches "tf" for True/False questions
        if (type == "tf") {
            int id;
            string text, answer;
            ss >> id;
            ss.ignore(); // Ignore the comma after the ID
            getline(ss, text, ',');
            getline(ss, answer, ',');

            // Trim quotes and whitespace from text
            text = trim(text);
            answer = trim(answer);

            // Convert answer to boolean
            bool correctAnswer = (answer == "True" || answer == "true");

            // Create a TrueFalseQuestion and add it to the vector
            questions.push_back(new TrueFalseQuestion(text, 1, correctAnswer)); // Example score is set to 1
        }
    }

    file.close();
}
