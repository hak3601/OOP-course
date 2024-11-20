#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "utils.h"
#include "exam.h"
#include "questions.h"
using namespace std;

Exam::Exam(const string &title, const string &datafolder) : exam_title(title), datafolder(datafolder) {}
Exam::~Exam() {}

/*-------------------------------------------------------------------------------------------*/
void TestExam::startExam() { // the main function of test exam
    cur_idx = 0;
    string prof_name = "Prof.Ko";
    string exam_file_name = exam_title+"-test-"+prof_name+".csv";
    vector<vector<string>> raw_questions = readCSV(datafolder, exam_file_name);

    questions = vec2Questions(raw_questions);
    
    cout << exam_title << " starts now." << endl;
    
    endExam();
}
// Display the list of questions and their current state (answered or not)
// Display the list of questions and their current state (answered or not)
void TestExam::displayQuestionList() const { // 
    cout << "Question List:\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        if (static_cast<int>(i) == cur_idx) {
            // Highlight the current question using ANSI escape codes
            setTextColor(10,-1);
            cout << i + 1 << ". " 
                << (answers[i].empty() ? "X" : answers[i]);
            resetTextColor();
            cout << "\t";
        } else {
            cout << i + 1 << ". " 
                << (answers[i].empty() ? "X" : answers[i]) 
                << "\t";
        }
    }
}
// Handle the end-of-exam options
void TestExam::handleEndOfExam() {
    char command;
    displayQuestionList(); // Display the question list at the end of the exam
    cout << endl << "Options: [s]ubmit, [m]ove to questions" << endl;
    cout << "Enter command: ";
    cin >> command;

    switch (command) {
        case 's':
            saveToCSV();
            cout << "Exam submitted. Thank you!" << endl;
            exit(0);
        case 'm':
            goToPreviousQuestion();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}

void TestExam::displayQuestions() const {
    if (cur_idx >= 0 && cur_idx < static_cast<int>(questions.size())) {
        cout << "--- Portable Exam Menu ---" << endl;
        cout << "Question " << questions[cur_idx]->getIdx() << ": " << questions[cur_idx]->getQuestionText() << endl;
        cout << "Current Answer: " << (answers[cur_idx].empty() ? "None" : answers[cur_idx]) << endl;
    } else if (cur_idx == static_cast<int>(questions.size())) {
        // At the end of the exam
        cout << "--- End of Exam ---" << endl;
        cout << "Options: [s]ubmit, [p]revious questions" << endl;
    } else {
        cout << "Invalid question index!" << endl;
    }
}

// Edit the answer for the current question
void TestExam::editAnswer(const string& newAnswer) {
    if (cur_idx >= 0 && cur_idx < static_cast<int>(answers.size())) {
        answers[cur_idx] = newAnswer;
        cout << "Answer updated!" << endl;
    } else {
        cout << "Cannot edit answer. Invalid question index!" << endl;
    }
}

// Move to a specific previous question by input
void TestExam::goToPreviousQuestion() {
    int questionNumber;
    cout << "Enter the question number to go back to: ";
    cin >> questionNumber;
    // Adjust for zero-based indexing
    questionNumber -= 1;

    if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size())) {
        cur_idx = questionNumber;
        cout << "Moved to question " << cur_idx + 1 << "." << endl;
    } else {
        cout << "Invalid move. Please enter a valid question number." << endl;
    }
}

// Handle options after navigating to a previous question
void TestExam::handlePostNavigationOptions() {
    char command;
    while (true) {
        cout << endl << "Options: [e]dit answer, [s]ubmit, [g]o back to another question" << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == 'e') {
            cout << "Enter new answer: ";
            cin.ignore(); // Ignore newline from previous input
            string input;
            getline(cin, input);
            editAnswer(input);
        } else if (command == 's') {
            saveToCSV();
            cout << "Exam submitted. Thank you!" << endl;
            exit(0);
        } else if (command == 'g') {
            goToAnotherQuestion(); // Ask user which question to go to
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Go to another specified question by the user
void TestExam::goToAnotherQuestion() {
    int questionNumber;
    cout << "Enter the question number to go back to: ";
    cin >> questionNumber;
    // Adjust for zero-based indexing
    questionNumber -= 1;

    if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size())) {
        cur_idx = questionNumber;
        cout << "Moved to question " << cur_idx + 1 << "." << endl;
        displayQuestions(); // Display the question after moving
    } else {
        cout << "Invalid question number. Please try again." << endl;
    }
}

// Get the current index
int TestExam::getCurrentIndex() const {
    return cur_idx;
}

// Save the questions and answers to a CSV file
void TestExam::saveToCSV() const {
    string stream = datafolder+"/exam_results.csv";
    ofstream outFile(stream);
    if (outFile.is_open()) {
        outFile << "Question,Answer\n";
        for (size_t i = 0; i < questions.size(); ++i) {
            outFile << "\"" << questions[i]->getQuestionText() << "\",\"" 
                    << (answers[i].empty() ? "None" : answers[i]) << "\"\n";
        }
        outFile.close();
        cout << "Results saved to 'exam_results.csv'." << endl;
    } else {
        cerr << "Error: Could not open file for writing." << endl;
    }
}

// Move to the next question (or end the exam)
void TestExam::goToNextQuestion() {
    if (cur_idx < static_cast<int>(questions.size()) - 1) {
        ++cur_idx;
        cout << "Moved to the next question." << endl;
    } else if (cur_idx == static_cast<int>(questions.size()) - 1) {
        ++cur_idx; // Move to end state
        cout << "You have reached the end of the exam." << endl;
    } else {
        cout << "Already at the end of the exam." << endl;
    }
}




TestExam::TestExam(const string &title, const string &datafolder) : Exam(title,datafolder) {}
TestExam::~TestExam() {}
void TestExam::setMaxScore(){
    
}
void TestExam::endExam() {} // will be called when exam is over and will update the test result file
void TestExam::recordScore(const string &, int) {} // 
void TestExam::printSummary() const {}
void TestExam::timeIsOver() {}

/*-------------------------------------------------------------------------------------------*/


