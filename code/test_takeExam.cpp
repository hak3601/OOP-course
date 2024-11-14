#include <vector>
#include "questions.h"
#include "questions.cpp"
#include <iostream>

// Function to test grading of questions with predefined answers
void testTrueFalseQuestions(const std::vector<Question*> &questions, const std::vector<std::string> &testAnswers) {
    for (size_t i = 0; i < questions.size(); ++i) {
        questions[i]->display();
        int score = questions[i]->grade(testAnswers[i]);
        std::cout << "Provided Answer: " << testAnswers[i] << std::endl;
        std::cout << "Score: " << score << " / " << questions[i]->getMaxScore() << std::endl;
    }
}

int main() {
    std::vector<Question*> questions;
    loadTrueFalseQuestionsFromCSV("../data/trueFalseQ.csv", questions);

    // Predefined answers for testing
    std::vector<std::string> testAnswers = {"True", "False"};

    // Ensure the number of test answers matches the number of questions
    if (testAnswers.size() != questions.size()) {
        std::cerr << "Error: Number of test answers does not match the number of questions." << std::endl;
        return 1;
    }

    // Test the grading function
    testTrueFalseQuestions(questions, testAnswers);

    // Clean up dynamically allocated memory
    for (auto& question : questions) {
        delete question;
    }

    return 0;
}
/*
*   cd "/Users/htetarkar/Documents/GitHub/Uni_course/OOP-course/code/"
*   g++ -std=c++14 test_takeExam.cpp -o test && ./test
*/