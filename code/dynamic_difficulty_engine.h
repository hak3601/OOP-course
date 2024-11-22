#ifndef DDE_H
#define DDE_H

#include "questions.h"
using namespace std;
class DynamicDifficultyEngine{
private:
    int difficulty_upperbound;
    int difficulty_lowerbound;
    int cur_difficulty;
    int cur_idx_in_questions;
public:
    DynamicDifficultyEngine(int, int);
    int getUpperbound();
    int getLowerbound();
    int getCurrentDifficulty();
    int setCurrentDifficulty(int);
    int getCurIdx();
    void setCurIdx(int);
    int recommendDifficulty(int, int, int, vector<Question*>, vector<string>);
};
#endif