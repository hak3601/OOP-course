// File: portable_exam.cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#if defined(_WIN32)
#include <windows.h>
#endif

class PortableExam {
private:
    std::vector<std::string> questions;
    std::vector<std::string> answers;
    int currentIndex;

public:
    PortableExam(const std::vector<std::string>& questionsList) 
        : questions(questionsList), currentIndex(0) {
        answers.resize(questions.size(), ""); // Initialize answers with empty strings
        enableANSIColors(); // Enable ANSI colors for Windows if needed
    }

    // Enable ANSI color support for Windows terminals
    void enableANSIColors() {
        #if defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            GetConsoleMode(hOut, &dwMode);
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
        #endif
    }

    // Display the list of questions and their current state (answered or not)
    void displayQuestionList() const {
        std::cout << "Question List:\n";
        for (size_t i = 0; i < questions.size(); ++i) {
            if (static_cast<int>(i) == currentIndex) {
                // Highlight the current question using ANSI escape codes
                std::cout << "\033[1;32m" << i + 1 << ". " 
                          << (answers[i].empty() ? "X" : answers[i]) 
                          << "\033[0m" << std::endl;
            } else {
                std::cout << i + 1 << ". " 
                          << (answers[i].empty() ? "X" : answers[i]) 
                          << std::endl;
            }
        }
    }

    // Display the current question
    void displayCurrentQuestion() const {
        if (currentIndex >= 0 && currentIndex < static_cast<int>(questions.size())) {
            std::cout << "--- Portable Exam Menu ---" << std::endl;
            std::cout << "Question " << currentIndex + 1 << ": " << questions[currentIndex] << std::endl;
            std::cout << "Current Answer: " << (answers[currentIndex].empty() ? "None" : answers[currentIndex]) << std::endl;
        } else if (currentIndex == static_cast<int>(questions.size())) {
            // At the end of the exam
            std::cout << "--- End of Exam ---" << std::endl;
            std::cout << "Options: [s]ubmit, [p]revious questions" << std::endl;
        } else {
            std::cout << "Invalid question index!" << std::endl;
        }
    }

    // Edit the answer for the current question
    void editAnswer(const std::string& newAnswer) {
        if (currentIndex >= 0 && currentIndex < static_cast<int>(answers.size())) {
            answers[currentIndex] = newAnswer;
            std::cout << "Answer updated!" << std::endl;
        } else {
            std::cout << "Cannot edit answer. Invalid question index!" << std::endl;
        }
    }

    // Move to a specific previous question by input
    void goToPreviousQuestion() {
        int questionNumber;
        std::cout << "Enter the question number to go back to: ";
        std::cin >> questionNumber;
        // Adjust for zero-based indexing
        questionNumber -= 1;

        if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size())) {
            currentIndex = questionNumber;
            std::cout << "Moved to question " << currentIndex + 1 << "." << std::endl;
            displayCurrentQuestion(); // Display the question after moving
            handlePostNavigationOptions(); // Allow further actions
        } else {
            std::cout << "Invalid move. Please enter a valid question number." << std::endl;
        }
    }

    // Move to the next question (or end the exam)
    void goToNextQuestion() {
        if (currentIndex < static_cast<int>(questions.size()) - 1) {
            ++currentIndex;
            std::cout << "Moved to the next question." << std::endl;
        } else if (currentIndex == static_cast<int>(questions.size()) - 1) {
            ++currentIndex; // Move to end state
            std::cout << "You have reached the end of the exam." << std::endl;
        } else {
            std::cout << "Already at the end of the exam." << std::endl;
        }
    }

    // Handle the end-of-exam options
    void handleEndOfExam() {
        char command;
        displayQuestionList(); // Display the question list at the end of the exam
        std::cout << "Options: [s]ubmit, [p]revious questions" << std::endl;
        std::cout << "Enter command: ";
        std::cin >> command;

        switch (command) {
            case 's':
                saveToCSV();
                std::cout << "Exam submitted. Thank you!" << std::endl;
                exit(0);
            case 'p':
                goToPreviousQuestion();
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }

    // Save the questions and answers to a CSV file
    void saveToCSV() const {
        std::ofstream outFile("exam_results.csv");
        if (outFile.is_open()) {
            outFile << "Question,Answer\n";
            for (size_t i = 0; i < questions.size(); ++i) {
                outFile << "\"" << questions[i] << "\",\"" 
                        << (answers[i].empty() ? "None" : answers[i]) << "\"\n";
            }
            outFile.close();
            std::cout << "Results saved to 'exam_results.csv'." << std::endl;
        } else {
            std::cerr << "Error: Could not open file for writing." << std::endl;
        }
    }

    // Handle options after navigating to a previous question
    void handlePostNavigationOptions() {
        char command;
        while (true) {
            std::cout << "Options: [e]dit answer, [s]ubmit, [g]o back to another question" << std::endl;
            std::cout << "Enter command: ";
            std::cin >> command;

            if (command == 'e') {
                std::cout << "Enter new answer: ";
                std::cin.ignore(); // Ignore newline from previous input
                std::string input;
                std::getline(std::cin, input);
                editAnswer(input);
            } else if (command == 's') {
                saveToCSV();
                std::cout << "Exam submitted. Thank you!" << std::endl;
                exit(0);
            } else if (command == 'g') {
                goToAnotherQuestion(); // Ask user which question to go to
                break;
            } else {
                std::cout << "Invalid option. Please try again." << std::endl;
            }
        }
    }

    // Go to another specified question by the user
    void goToAnotherQuestion() {
        int questionNumber;
        std::cout << "Enter the question number to go back to: ";
        std::cin >> questionNumber;
        // Adjust for zero-based indexing
        questionNumber -= 1;

        if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size())) {
            currentIndex = questionNumber;
            std::cout << "Moved to question " << currentIndex + 1 << "." << std::endl;
            displayCurrentQuestion(); // Display the question after moving
        } else {
            std::cout << "Invalid question number. Please try again." << std::endl;
        }
    }

    // Get the current index
    int getCurrentIndex() const {
        return currentIndex;
    }
};

int main() {
    // Example questions for demonstration
    std::vector<std::string> questionsList;
    questionsList.push_back("What is your name?");
    questionsList.push_back("What is your favorite color?");
    questionsList.push_back("What is the capital of France?");

    PortableExam exam(questionsList);

    char command;
    std::string input;
    while (true) {
        if (exam.getCurrentIndex() == static_cast<int>(questionsList.size())) {
            // Special handling if at the end of the exam
            exam.handleEndOfExam();
            continue;
        }

        exam.displayQuestionList();
        std::cout << std::endl;
        exam.displayCurrentQuestion();
        std::cout << "Commands: [e]dit answer, [p]revious question, [n]ext question, [q]uit" << std::endl;
        std::cout << "Enter command: ";
        std::cin >> command;

        switch (command) {
            case 'e':
                std::cout << "Enter new answer: ";
                std::cin.ignore(); // Ignore newline from previous input
                std::getline(std::cin, input);
                exam.editAnswer(input); // Automatically moves to the next question after editing
                break;
            case 'p':
                exam.goToPreviousQuestion();
                break;
            case 'n':
                exam.goToNextQuestion();
                break;
            case 'q':
                std::cout << "Exiting the exam." << std::endl;
                return 0;
            default:
                std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
}
