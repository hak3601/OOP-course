// // File: portable_exam.cpp
// #include <iostream>
// #include <vector>
// #include <string>
// #include <fstream>

// #if defined(_WIN32)
// #include <windows.h>
// #endif

// using namespace std;

// class PortableExam {
// private:
//     vector<string> questions;
//     vector<string> answers;
//     int currentIndex;

// public:
//     PortableExam(const vector<string>& questionsList) 
//         : questions(questionsList), currentIndex(0) {
//         answers.resize(questions.size(), ""); // Initialize answers with empty strings
//         enableANSIColors(); // Enable ANSI colors for Windows if needed
//     }

//     // Display the list of questions and their current state (answered or not)
//     void displayQuestionList() const { // 
//         cout << "Question List:\n";
//         for (size_t i = 0; i < questions.size(); ++i) {
//             if (static_cast<int>(i) == currentIndex) {
//                 // Highlight the current question using ANSI escape codes
//                 cout << "\033[1;32m" << i + 1 << ". " 
//                     << (answers[i].empty() ? "X" : answers[i]) 
//                     << "\033[0m" << endl;
//             } else {
//                 cout << i + 1 << ". " 
//                     << (answers[i].empty() ? "X" : answers[i]) 
//                     << endl;
//             }
//         }
//     }

//     // Display the current question
//     void displayCurrentQuestion() const {
//         if (currentIndex >= 0 && currentIndex < static_cast<int>(questions.size())) {
//             cout << "--- Portable Exam Menu ---" << endl;
//             cout << "Question " << currentIndex + 1 << ": " << questions[currentIndex] << endl;
//             cout << "Current Answer: " << (answers[currentIndex].empty() ? "None" : answers[currentIndex]) << endl;
//         } else if (currentIndex == static_cast<int>(questions.size())) {
//             // At the end of the exam
//             cout << "--- End of Exam ---" << endl;
//             cout << "Options: [s]ubmit, [p]revious questions" << endl;
//         } else {
//             cout << "Invalid question index!" << endl;
//         }
//     }

//     // Edit the answer for the current question
//     void editAnswer(const string& newAnswer) {
//         if (currentIndex >= 0 && currentIndex < static_cast<int>(answers.size())) {
//             answers[currentIndex] = newAnswer;
//             cout << "Answer updated!" << endl;
//         } else {
//             cout << "Cannot edit answer. Invalid question index!" << endl;
//         }
//     }

//     // Move to a specific previous question by input
//     void goToPreviousQuestion() {
//         int questionNumber;
//         cout << "Enter the question number to go back to: ";
//         cin >> questionNumber;
//         // Adjust for zero-based indexing
//         questionNumber -= 1;

//         if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size())) {
//             currentIndex = questionNumber;
//             cout << "Moved to question " << currentIndex + 1 << "." << endl;
//             displayCurrentQuestion(); // Display the question after moving
//             handlePostNavigationOptions(); // Allow further actions
//         } else {
//             cout << "Invalid move. Please enter a valid question number." << endl;
//         }
//     }

//     // Move to the next question (or end the exam)
//     void goToNextQuestion() {
//         if (currentIndex < static_cast<int>(questions.size()) - 1) {
//             ++currentIndex;
//             cout << "Moved to the next question." << endl;
//         } else if (currentIndex == static_cast<int>(questions.size()) - 1) {
//             ++currentIndex; // Move to end state
//             cout << "You have reached the end of the exam." << endl;
//         } else {
//             cout << "Already at the end of the exam." << endl;
//         }
//     }

//     // Handle the end-of-exam options
//     void handleEndOfExam() {
//         char command;
//         displayQuestionList(); // Display the question list at the end of the exam
//         cout << "Options: [s]ubmit, [p]revious questions" << endl;
//         cout << "Enter command: ";
//         cin >> command;

//         switch (command) {
//             case 's':
//                 saveToCSV();
//                 cout << "Exam submitted. Thank you!" << endl;
//                 exit(0);
//             case 'p':
//                 goToPreviousQuestion();
//                 break;
//             default:
//                 cout << "Invalid option. Please try again." << endl;
//         }
//     }

//     // Save the questions and answers to a CSV file
//     void saveToCSV() const {
//         ofstream outFile("exam_results.csv");
//         if (outFile.is_open()) {
//             outFile << "Question,Answer\n";
//             for (size_t i = 0; i < questions.size(); ++i) {
//                 outFile << "\"" << questions[i] << "\",\"" 
//                         << (answers[i].empty() ? "None" : answers[i]) << "\"\n";
//             }
//             outFile.close();
//             cout << "Results saved to 'exam_results.csv'." << endl;
//         } else {
//             cerr << "Error: Could not open file for writing." << endl;
//         }
//     }

//     // Handle options after navigating to a previous question
//     void handlePostNavigationOptions() {
//         char command;
//         while (true) {
//             cout << "Options: [e]dit answer, [s]ubmit, [g]o back to another question" << endl;
//             cout << "Enter command: ";
//             cin >> command;

//             if (command == 'e') {
//                 cout << "Enter new answer: ";
//                 cin.ignore(); // Ignore newline from previous input
//                 string input;
//                 getline(cin, input);
//                 editAnswer(input);
//             } else if (command == 's') {
//                 saveToCSV();
//                 cout << "Exam submitted. Thank you!" << endl;
//                 exit(0);
//             } else if (command == 'g') {
//                 goToAnotherQuestion(); // Ask user which question to go to
//                 break;
//             } else {
//                 cout << "Invalid option. Please try again." << endl;
//             }
//         }
//     }

//     // Go to another specified question by the user
//     void goToAnotherQuestion() {
//         int questionNumber;
//         cout << "Enter the question number to go back to: ";
//         cin >> questionNumber;
//         // Adjust for zero-based indexing
//         questionNumber -= 1;

//         if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size())) {
//             currentIndex = questionNumber;
//             cout << "Moved to question " << currentIndex + 1 << "." << endl;
//             displayCurrentQuestion(); // Display the question after moving
//         } else {
//             cout << "Invalid question number. Please try again." << endl;
//         }
//     }

//     // Get the current index
//     int getCurrentIndex() const {
//         return currentIndex;
//     }
// };

// int main() {
//     // Example questions for demonstration
//     vector<string> questionsList;
//     questionsList.push_back("What is your name?");
//     questionsList.push_back("What is your favorite color?");
//     questionsList.push_back("What is the capital of France?");

//     PortableExam exam(questionsList);

//     char command;
//     string input;
//     while (true) {
//         if (exam.getCurrentIndex() == static_cast<int>(questionsList.size())) {
//             // Special handling if at the end of the exam
//             exam.handleEndOfExam();
//             continue;
//         }

//         exam.displayQuestionList();
//         cout << endl;
//         exam.displayCurrentQuestion();
//         cout << "Commands: [e]dit answer, [p]revious question, [n]ext question, [q]uit" << endl;
//         cout << "Enter command: ";
//         cin >> command;

//         switch (command) {
//             case 'e':
//                 cout << "Enter new answer: ";
//                 cin.ignore(); // Ignore newline from previous input
//                 getline(cin, input);
//                 exam.editAnswer(input); // Automatically moves to the next question after editing
//                 break;
//             case 'p':
//                 exam.goToPreviousQuestion();
//                 break;
//             case 'n':
//                 exam.goToNextQuestion();
//                 break;
//             case 'q':
//                 cout << "Exiting the exam." << endl;
//                 return 0;
//             default:
//                 cout << "Invalid command. Please try again." << endl;
//         }
//     }
// }
