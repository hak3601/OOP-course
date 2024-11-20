#ifndef DDE_H
#define DDE_H
class DynamicDifficultyEngine{
private:
    int difficulty_upperbound;
    int difficulty_lowerbound;
    int cur_difficulty;
public:
    DynamicDifficultyEngine(int, int);
    int getUpperbound();
    int getLowerbound();
    int getCurrentDifficulty();
    int recommendDifficulty(int, int, int);
};
#endif