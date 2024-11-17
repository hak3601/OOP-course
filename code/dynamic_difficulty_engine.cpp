#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>  // for using abs
using namespace std;

class DynamicDifficultyEngine {
private:
    float current_student_correct_rate;  // tracing student's performance(I think it would be from performance tracker)
    unsigned int current_problem_number; // current question's number
    int current_difficulty_level;  // current difficulty level

public:
    // initialize difficulty engine
    DynamicDifficultyEngine(int initial_difficulty) : current_difficulty_level(initial_difficulty), current_problem_number(0), current_student_correct_rate(0.0f) {
        
    }

    // get new question from the question set 
    int getNextQuestion(bool correct_answer) {
        adjustDifficulty(correct_answer);  // adjusting difficulty of the new question

        cout << "Next question difficulty: " << endl;
        // return proper_difficulty (may be problem set);
    }

    // help getNextQuestion to get the proper question reflecting the difficulty
    void adjustDifficulty(bool correct_answer) {
        // adjusting difficulty based on whether the answer is correct
        if (correct_answer) {
            current_difficulty_level = min(current_difficulty_level + 1, 10);  // minimum difficulty: 10
        } else {
            current_difficulty_level = max(current_difficulty_level - 1, 1);  // minimum difficulty: 1
        }
        cout << "Adjusted Difficulty Level: " << current_difficulty_level << endl;
    }
};
