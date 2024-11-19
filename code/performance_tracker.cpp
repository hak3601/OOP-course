#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

class PerformanceTracker {
private:
    vector<int> question_difficulty;
    int correct_answers = 0;
    double time_spent = 0.0;

public:
    // Is it for recording student's answer? I don't know what this method's role is
    void recordAnswer(bool correct, double time) {
        // Yet to be developed
    }

    // making report
    // How about getting performance instead of accuracy? 
    void generateReport() {
        int total_questions = question_difficulty.size();
        double accuracy = (total_questions > 0) ? (static_cast<double>(correct_answers) / total_questions) * 100 : 0;

        cout << "Total Questions: " << total_questions << endl;
        cout << "Correct Answers: " << correct_answers << endl;
        cout << "Accuracy (%): " << accuracy << endl;
    }
};
