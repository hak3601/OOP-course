#include <vector>
#include <numeric>
#include <iostream>

class PerformanceTracker {
private:
    std::vector<int> question_difficulty;
    int correct_answers = 0;
    double time_spent = 0.0;

public:
    // Is it for recording student's answer? I don't know what this method's role is
    void recordAnswer(bool correct, double time) {
        // Yet to be developed
    }

    // making report
    void generateReport() {
        int total_questions = question_difficulty.size();
        double accuracy = (total_questions > 0) ? (static_cast<double>(correct_answers) / total_questions) * 100 : 0;

        std::cout << "Total Questions: " << total_questions << std::endl;
        std::cout << "Correct Answers: " << correct_answers << std::endl;
        std::cout << "Accuracy (%): " << accuracy << std::endl;
    }
};
