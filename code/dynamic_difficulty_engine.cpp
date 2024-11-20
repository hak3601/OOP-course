#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>  // for using abs
#include "dynamic_difficulty_engine.h"
using namespace std;


DynamicDifficultyEngine::DynamicDifficultyEngine(int low, int up) : difficulty_lowerbound(low), difficulty_upperbound(up){}
int DynamicDifficultyEngine::getUpperbound(){return difficulty_upperbound;}
int DynamicDifficultyEngine::getLowerbound(){return difficulty_lowerbound;}
int DynamicDifficultyEngine::getCurrentDifficulty(){return cur_difficulty;}
int DynamicDifficultyEngine::recommendDifficulty(int cur_idx, int cur_total_score, int cur_gained_score){
    int ret_difficulty = 1;
    float div = static_cast<float>(cur_gained_score) / cur_total_score;
    ret_difficulty = (div * difficulty_upperbound);
}

