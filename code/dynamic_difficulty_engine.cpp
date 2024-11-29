#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>  // for using abs
#include <set>
#include <random>
#include "dynamic_difficulty_engine.h"
using namespace std;


DynamicDifficultyEngine::DynamicDifficultyEngine(int low, int up) : difficulty_lowerbound(low), difficulty_upperbound(up){}
int DynamicDifficultyEngine::getUpperbound(){return difficulty_upperbound;}
int DynamicDifficultyEngine::getLowerbound(){return difficulty_lowerbound;}
int DynamicDifficultyEngine::getCurrentDifficulty(){return cur_difficulty;}
int DynamicDifficultyEngine::setCurrentDifficulty(int dif){cur_difficulty = dif;}
int DynamicDifficultyEngine::getCurIdx() {return cur_idx_in_questions;}
void DynamicDifficultyEngine::setCurIdx(int s) {cur_idx_in_questions = s;}
int DynamicDifficultyEngine::recommendDifficulty(int cur_idx, int cur_total_score, int cur_gained_score, vector<Question*> questions, vector<vector<string>> RW_tracker) {
    int recommended_level = difficulty_lowerbound;
    if(cur_idx > 1 && cur_gained_score != 0){
        float div = static_cast<float>(log2f(cur_gained_score)+1.0f) / (log2f(cur_total_score)+1.0f);
        recommended_level = (div * difficulty_upperbound);
    }
    
    random_device rd;
    mt19937 gen(rd());
    int ret_level = -1;
    int over_cnt = 0;
    int under_cnt = 0;
    set<int> over;
    set<int> under;
    for (size_t i = 0; i < questions.size(); i++) 
    {
        if(questions[i]->getpoint() == recommended_level){ // if there is a question in questions that match the recommended point
            ret_level = recommended_level;
            break;
        } else if(questions[i]->getpoint() < recommended_level){
            under_cnt++;
            under.insert(questions[i]->getpoint());
        } else {
            over_cnt++;
            over.insert(questions[i]->getpoint());
        }
    }

    if(ret_level < 0){
        cout << "The training set ran out of recommended difficulty level " << recommended_level << "! ";
        if(!RW_tracker.back()[0].compare("O")){ // recommend higher level
            for (size_t i = recommended_level + 1; i <= difficulty_upperbound; i++)
            {
                if(over.find(i) != over.end()){
                    ret_level = i;
                    break;
                }
            }
            
        } else{
            for (size_t i = recommended_level - 1; i >= difficulty_lowerbound; i--)
            {
                if(under.find(i) != under.end()){
                    ret_level = i;
                    break;
                }
            }
        }
        if(ret_level < 0){
            set<int> over_and_under;
            over_and_under.insert(under.begin(), under.end());
            over_and_under.insert(over.begin(), over.end());
            while(true){
                if(over_and_under.size() == 0){ break; }
                
                uniform_int_distribution<int> dist(getLowerbound(), getUpperbound() + 1);
                ret_level = dist(gen);
                if(over_and_under.find(ret_level)!=over_and_under.end()){
                    break;
                }
            }
        }
        
        
        cout << "Recommended level " << ret_level << " instead!" << endl;
    } 
    
    setCurrentDifficulty(ret_level);
    return ret_level;
}

