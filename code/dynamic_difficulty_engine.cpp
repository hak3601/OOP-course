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
    vector<int> questionSet;

public:
    // initialize difficulty engine
    DynamicDifficultyEngine(int initialDifficulty) : current_difficulty_level(initialDifficulty), current_problem_number(0), current_student_correct_rate(0.0f) {
        // generate the questions with various difficulty from 1 to 10.
        for (int i = 1; i <= 10; ++i) {
            questionSet.push_back(i);
        }
        srand(time(nullptr));  // initialize random value
    }

    // get new question from the question set 
    int getNextQuestion(bool correctAnswer) {
        adjustDifficulty(correctAnswer);  // adjusting difficulty of the new question

        // bring the question closest difficulty
        int closestDifficulty = questionSet[0];
        for (int questionDifficulty : questionSet) {
            if (abs(questionDifficulty - current_difficulty_level) < abs(closestDifficulty - current_difficulty_level)) {
                closestDifficulty = questionDifficulty;
            }
        }

        cout << "Next question difficulty: " << closestDifficulty << endl;
        return closestDifficulty;
    }

    // help getNextQuestion to get the proper question reflecting the difficulty
    void adjustDifficulty(bool correctAnswer) {
        // adjusting difficulty based on whether the answer is correct
        if (correctAnswer) {
            current_difficulty_level = min(current_difficulty_level + 1, 10);  // minimum difficulty: 10
        } else {
            current_difficulty_level = max(current_difficulty_level - 1, 1);  // minimum difficulty: 1
        }
        cout << "Adjusted Difficulty Level: " << current_difficulty_level << endl;
    }
};
