#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <time.h>
#include <sstream>
#include "utils.h"
#include "exam.h"
#include "questions.h"
#include <thread>
#include "dynamic_difficulty_engine.h"
using namespace std;

Exam::Exam(const string &title, const string &datafolder, const User *user, const string &examfile) : exam_title(title), datafolder(datafolder), object_user(user), examfile(examfile) {}

/*-------------------------------------------------------------------------------------------*/
TrainExam::TrainExam(const string &title, const string &datafolder, const User *user, const string &prof_name, const string &examfile) : Exam(title, datafolder, user, examfile), prof_name(prof_name)
{
    string exam_file_name = examfile;
    vector<vector<string>> raw_questions = readCSV(datafolder, exam_file_name);
    int low = 100;
    int top = 0;
    for (const auto &vv : raw_questions)
    {
        low = (low < stoi(vv[4])) ? low : stoi(vv[4]);
        top = (top > stoi(vv[4])) ? top : stoi(vv[4]);
    }
    DDE = new DynamicDifficultyEngine(low, top);
}


void TrainExam::startExam()
{
    cur_idx = 1;
    string exam_file_name = examfile;
    vector<vector<string>> raw_questions = readCSV(datafolder, exam_file_name);

    questions = vec2Questions(raw_questions);

    char command;
    string input;
    while (true)
    {
        clearConsole();
        if (questions.empty())
        {
            break;
        }

        cout << endl;
        setTextColor(3, -1);
        menuPrintButton(vector<string>{"Training Exam"});
        resetTextColor();
        displayQuestionList();

        cout << endl;
        displayQuestions();
        cout << "Commands: [e]dit answer, [q]uit" << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == 'e')
        {
            cout << "Enter answer: ";
            cin.ignore(); // Ignore newline from previous input
            getline(cin, input);
            editAnswer(input); // Automatically moves to the next question after editing
        }
        else if (command == 'q')
        {
            cout << "Exiting training." << endl;
            break;
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }

        delete questions[DDE->getCurIdx()];
        questions.erase(questions.begin() + DDE->getCurIdx());
        cur_idx++;
    }

    printSummary();
}

void TrainExam::editAnswer(string user_ans)
{
    int right_or_wrong = questions[DDE->getCurIdx()]->grade(user_ans);
    user_taken_answers.push_back(vector<string>{user_ans, questions[DDE->getCurIdx()]->getCorrectAnswer(), to_string(questions[DDE->getCurIdx()]->grade(user_ans))});

    cur_total_score += questions[DDE->getCurIdx()]->getpoint();
    if (right_or_wrong)
    { // user got it right
        individual_problem_RW_tracker.push_back(vector<string>{"O", to_string(questions[DDE->getCurIdx()]->getpoint())});
        cur_gained_score += questions[DDE->getCurIdx()]->getpoint();
    }
    else
    { // user got it wrong
        individual_problem_RW_tracker.push_back(vector<string>{"X", to_string(questions[DDE->getCurIdx()]->getpoint())});
    }
}

void TrainExam::displayQuestionList() const
{
    for (size_t i = 0; i < individual_problem_RW_tracker.size(); i++)
    {
        if (!individual_problem_RW_tracker[i][0].compare("O"))
        {
            setTextColor(10, -1);
            cout << i + 1 << ". O ";
            resetTextColor();
        }
        else
        {
            setTextColor(1, -1);
            cout << i + 1 << ". X ";
            resetTextColor();
        }
        cout << " ";
    }
}

void TrainExam::endExam()
{
    cout << "end train" << endl;
}

void TrainExam::displayQuestions()
{
    int recommended_level = DDE->recommendDifficulty(cur_idx, cur_total_score, cur_gained_score, questions, individual_problem_RW_tracker);
    int prob_idx = 0;
    for (size_t i = 0; i < questions.size(); i++)
    {
        if (questions[i]->getpoint() == recommended_level)
        {
            prob_idx = i;
            break;
        }
    }

    user_taken_questions.push_back(questions[prob_idx]->display());

    if (prob_idx >= 0 && prob_idx < static_cast<int>(questions.size()))
    {
        setTextColor(3, -1);
        cout << "Question " << cur_idx << ": ";
        resetTextColor();
        cout << questions[prob_idx]->getQuestionText() << transformQuestionVersion2string(questions[prob_idx]->getQversion()) << "   (" << questions[prob_idx]->getpoint() << " points)\n" << endl;
        if (questions[prob_idx]->getQversion() == "MC")
        {
            cout << questions[prob_idx]->getOptions() << "\n" << endl;
        }
    }
    else
    {
        cout << "question is empty" << endl;
    }
    DDE->setCurIdx(prob_idx);
    cout << "current level : " << DDE->getCurrentDifficulty() << "\n"
         << endl;
}

void TrainExam::printSummary() const
{ // wrong questions, total score, accuracy, point distribution.
    clearConsole();
    if (user_taken_questions.empty())
    {
        cout << "No questions were taken." << endl;
        return;
    }
    setTextColor(3, -1);
    printButton(vector<string>({"    ***    Summary of your training    ***    "}));
    resetTextColor();
    setTextColor(12, -1);
    cout << "\n[Questions that you got wrong]\n"
         << endl;
    resetTextColor();
    for (size_t i = 0; i < user_taken_questions.size() - 1; i++)
    {
        if (stoi(user_taken_answers[i][2]) == 0)
        {
            cout << user_taken_questions[i] << " \nYour answer : ";
            setTextColor(1, -1);
            cout << user_taken_answers[i][0];
            resetTextColor();
            cout << ", Correct answer : ";
            setTextColor(10, -1);
            cout << user_taken_answers[i][1] << endl;
            resetTextColor();
            cout << "" << endl;
        }
    }

    setTextColor(3, -1);
    cout << "--------------------------------------------------\n"
         << endl;
    resetTextColor();
    setTextColor(12, -1);
    cout << "[Your score] ";
    resetTextColor();
    cout << cur_gained_score << " (point gained) / " << cur_total_score << " (total point)\n"
         << endl;

    vector<int> point_cnt_dict(DDE->getUpperbound() - DDE->getLowerbound() + 1);

    for (const auto &vv : individual_problem_RW_tracker)
    {
        if (!vv[0].compare("O"))
        {
            point_cnt_dict[-DDE->getLowerbound() + stoi(vv[1])] += 1;
        }
    }

    for (size_t i = 0; i < point_cnt_dict.size(); i++)
    {
        setTextColor(14, -1);
        cout << DDE->getLowerbound() + i << " point : ";
        resetTextColor();
        for (size_t j = 0; j < point_cnt_dict[i] * 2; j++)
        {
            this_thread::sleep_for(chrono::milliseconds(50));
            if (j % 2 != 0)
            {
                setTextColor(10, i + 1);
                cout << "  ";
                resetTextColor();
            }
            else
            {
                cout << " ";
            }
        }
        cout << "\n"
             << endl;
    }
}

/*-------------------------------------------------------------------------------------------*/
void TestExam::startExam()
{ // the main function of test exam
    cur_idx = 0;
    string exam_file_name = exam_title + "-test-" + prof_name + ".csv";
    vector<vector<string>> raw_questions = readCSV(datafolder, exam_file_name);

    questions = vec2Questions(raw_questions);
    answers.resize(questions.size(), "");
    cout << exam_title << " starts now.";

    char command;
    string input;
    while (true)
    {
        clearConsole();
        if (cur_idx == static_cast<int>(questions.size()))
        {
            // Special handling if at the end of the exam
            if (handleEndOfExam() == 1)
                break;
            continue;
        }

        displayQuestionList();
        cout << endl;
        displayQuestions();
        cout << "Commands: [e]dit answer, [m]ove to question, [n]ext question" << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == 'e')
        {
            cout << "Enter new answer: ";
            cin.ignore(); // Ignore newline from previous input
            getline(cin, input);
            editAnswer(input); // Automatically moves to the next question after editing
            goToNextQuestion();
        }
        else if (command == 'm')
        {
            goToPreviousQuestion();
        }
        else if (command == 'n')
        {
            goToNextQuestion();
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }
    }
    printSummary();
}

void TestExam::printSummary() const
{

    clearConsole();

    setTextColor(3, -1);
    printButton(vector<string>({"    ***    Summary of exam    ***    "}));
    resetTextColor();
    setTextColor(12, -1);
    cout << "[Your score] ";
    resetTextColor();
    cout << total_score << "/" << max_score << endl;
}
// Display the list of questions and their current state (answered or not)
void TestExam::displayQuestionList() const
{
    setTextColor(3, -1);
    cout << "Question List:\n";
    resetTextColor();
    for (size_t i = 0; i < questions.size(); ++i)
    {
        if (static_cast<int>(i) == cur_idx)
        {
            // Highlight the current question using ANSI escape codes
            setTextColor(10, -1);
            cout << i + 1 << ". "
                 << (answers[i].empty() ? "X" : answers[i]);
            resetTextColor();
            cout << "\t";
        }
        else
        {
            cout << i + 1 << ". "
                 << (answers[i].empty() ? "X" : answers[i])
                 << "\t";
        }
    }
}
// Handle the end-of-exam options
int TestExam::handleEndOfExam()
{
    char command;
    displayQuestionList(); // Display the question list at the end of the exam
    cout << endl
         << "Options: [s]ubmit, [m]ove to questions" << endl;
    cout << "Enter command: ";
    cin >> command;

    switch (command)
    {
    case 's':
        endExam();
        saveToCSV();
        cout << "Exam submitted. Thank you!" << endl;
        return 1;
    case 'm':
        goToPreviousQuestion();
        return 2;
    default:
        cout << "Invalid option. Please try again." << endl;
    }
}

void TestExam::displayQuestions()
{
    if (cur_idx >= 0 && cur_idx < static_cast<int>(questions.size()))
    {
        cout << "--- Exam Menu ---\n"
             << endl;
        setTextColor(3, -1);
        setTextColor(3, -1);
        cout << "Question " << cur_idx << ": ";
        resetTextColor();
        cout << questions[cur_idx]->getQuestionText() << transformQuestionVersion2string(questions[cur_idx]->getQversion()) << "   (" << questions[cur_idx]->getpoint() << " points)\n" << endl;
        if (questions[cur_idx]->getQversion() == "MC")
        {
            cout << questions[cur_idx]->getOptions() << "\n" << endl;
        }

        cout << "Current Answer: " << (answers[cur_idx].empty() ? "None" : answers[cur_idx]) << endl;
    }
    else if (cur_idx == static_cast<int>(questions.size()))
    {
        // At the end of the exam
        cout << "--- End of Exam ---" << endl;
        cout << "Options: [s]ubmit, [p]revious questions" << endl;
    }
    else
    {
        cout << "Invalid question index!" << endl;
    }
}

// Edit the answer for the current question
void TestExam::editAnswer(const string &newAnswer)
{
    if (cur_idx >= 0 && cur_idx < static_cast<int>(answers.size()))
    {
        answers[cur_idx] = newAnswer;
        cout << "Answer updated!" << endl;
    }
    else
    {
        cout << "Cannot edit answer. Invalid question index!" << endl;
    }
}

// Move to a specific previous question by input
void TestExam::goToPreviousQuestion()
{
    int questionNumber;
    cout << "Enter the question number to go back to: ";
    cin >> questionNumber;
    // Adjust for zero-based indexing
    questionNumber -= 1;

    if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size()))
    {
        cur_idx = questionNumber;
        cout << "Moved to question " << cur_idx + 1 << "." << endl;
    }
    else
    {
        cout << "Invalid move. Please enter a valid question number." << endl;
    }
}

// Handle options after navigating to a previous question
void TestExam::handlePostNavigationOptions()
{
    char command;
    while (true)
    {
        cout << endl
             << "Options: [e]dit answer, [s]ubmit, [g]o back to another question" << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == 'e')
        {
            cout << "Enter new answer: ";
            cin.ignore(); // Ignore newline from previous input
            string input;
            getline(cin, input);
            editAnswer(input);
        }
        else if (command == 's')
        {
            saveToCSV();
            cout << "Exam submitted. Thank you!" << endl;
        }
        else if (command == 'g')
        {
            goToAnotherQuestion(); // Ask user which question to go to
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Go to another specified question by the user
void TestExam::goToAnotherQuestion()
{
    int questionNumber;
    cout << "Enter the question number to go back to: ";
    cin >> questionNumber;
    // Adjust for zero-based indexing
    questionNumber -= 1;

    if (questionNumber >= 0 && questionNumber < static_cast<int>(questions.size()))
    {
        cur_idx = questionNumber;
        cout << "Moved to question " << cur_idx + 1 << "." << endl;
        displayQuestions(); // Display the question after moving
    }
    else
    {
        cout << "Invalid question number. Please try again." << endl;
    }
}

// Get the current index
int TestExam::getCurrentIndex() const
{
    return cur_idx;
}

// Save the questions and answers to a CSV file
void TestExam::saveToCSV() const
{
    string stream = datafolder + "/" + exam_title + "-" + this->getProfessorName() + "-" + "exam_results.csv";
    ofstream outFile(stream, ios::app);
    if (outFile.is_open())
    {
        outFile << "Student : " << object_user->getName() << ", ID : " << object_user->getId() << ", Score : " << total_score << "/" << max_score << "\n";
        for (size_t i = 0; i < questions.size(); ++i)
        {
            outFile << "\"" << questions[i]->getQuestionText() << "\",\""
                    << "Student answer => " << (answers[i].empty() ? "None" : answers[i]) << "\",\""
                    << "Correct answer => " << questions[i]->getCorrectAnswer() << "\"\n";
        }
        outFile.close();
        clearConsole();
        cout << "Your score is : " << total_score << "/" << max_score << endl;
        cout << "Results saved to " << stream << "." << endl;
    }
    else
    {
        cerr << "Error: Could not open file for writing." << endl;
    }
}

// Move to the next question (or end the exam)
void TestExam::goToNextQuestion()
{
    if (cur_idx < static_cast<int>(questions.size()) - 1)
    {
        ++cur_idx;
        cout << "Moved to the next question." << endl;
    }
    else if (cur_idx == static_cast<int>(questions.size()) - 1)
    {
        ++cur_idx; // Move to end state
        cout << "You have reached the end of the exam." << endl;
    }
    else
    {
        cout << "Already at the end of the exam." << endl;
    }
}
TestExam::TestExam(const string &title, const string &datafolder, const User *user, const string &prof_name, const string &examfile) : Exam(title, datafolder, user, examfile), prof_name(prof_name) {}
void TestExam::endExam()
{
    for (size_t i = 0; i < answers.size(); i++)
    {
        total_score += questions[i]->grade(answers[i]);
        max_score += questions[i]->getpoint();
    }

} // will be called when exam is over and will update the test result file
string TestExam::getProfessorName() const { return prof_name; }

/*-------------------------------------------------------------------------------------------*/
