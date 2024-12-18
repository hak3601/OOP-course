#include "exam.h"
#include "questions.h"
#include "user.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

void studentMainMenu(User *, string);
void professorMainMenu(User *, string);
int verifyUser(string &, const string &, const string &);
void inspectResults(User *, int, string);
void showAvailableCourses(User *user, const string &datafolder, const string &filename);
bool updateAvailableState(User *user, const string &course, const string &datafolder, const string &filename);

int main(int argc, char const *argv[])
{
    /*
    <how to run>
    Make sure you are currently in ..\OOP-course according to the terminal.
    Write the below statement on the terminal.
    >> g++ .\code\main.cpp -o program
    >> .\program data
    Thus you located the folder name for data retrieval
    */

    string datafolder = argv[1];

    string user_name;
    string user_id;
    User *user;
    int user_type = 0;

    while (1)
    {
        clearConsole();
        setTextColor(3, -1);
        menuPrintButton(vector<string>{"*** Welcome to University Exam Management System ***"});
        resetTextColor();

        cout << "\nVerify yourself with your name and ID" << endl;
        cout << "Name >> ";
        cin >> user_name;
        cout << "ID >> ";
        cin >> user_id;
        user_type = verifyUser(user_name, user_id, datafolder);
        cout << "Checking if your information is already in the database..." << endl;
        if (user_type == 0)
        { // can't open file            return 0;
        }
        else if (user_type == 1)
        { // student
            cout << "You are a student!!" << endl;
            user = new Student(user_name, user_id, fetchEnroledOrInstructing(user_name, user_id, datafolder, "student.csv"));
            break;
        }
        else if (user_type == 2)
        { // professor
            cout << "You are a professor!!" << endl;
            user = new Professor(user_name, user_id, fetchEnroledOrInstructing(user_name, user_id, datafolder, "professor.csv"));
            break;
        }
        else if (user_type == 3)
        { // user name, ID not found in database
            char command;
            while (true)
            {
                cout << "No matching found(type 1 to retry) >> ";
                cin >> command;
                if (command == '1')
                {
                    break;
                }
            }
        }
    }
    if (user_type == 1)
    {
        studentMainMenu(user, datafolder);
    }
    else if (user_type == 2)
    {
        professorMainMenu(user, datafolder);
    }

    cout << "Program terminated" << endl;
    return 0;
}

void studentMainMenu(User *user, string datafolder)
{
    int user_command;
    string course_prof_name;
    Exam *exam;
    while (1)
    {
        clearConsole();
        setTextColor(3, -1);
        menuPrintButton(vector<string>{"Student Main Menu", user->getName(), user->getId()});
        resetTextColor();
        cout << "\n" << endl;

        vector<string> ls = {"1. Take Test", "2. Train for Test", "3. Create Train Test", "4. Exit"};
        printButton(ls);
        cout << "Enter your command >> ";
        cin >> user_command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (user_command == 1)
        { // Take test exam
            /*
            show available courses to take exam(course name(instructor))
            show the current taken test status
            user selects which test to take
            bring csv file according to course name, instructor
            create exam object ~
            */
            showAvailableCourses(user, datafolder, "courses_available.csv");
            int num;
            while(true){
                cout << "Select the corresponding number to the course >> ";
                cin >> num;
                if(num <= user->getInternalContent().size()){break;}
                cout << "Invalid input, please try again" << endl;
            }
            
            course_prof_name = user->getInternalContent()[num - 1];

            vector<string> c_f_vector = splitString2CourseAndProf(course_prof_name);

            if (!listFilesInDirectory(datafolder, c_f_vector, "test").empty() && updateAvailableState(user, course_prof_name, datafolder, "courses_available.csv"))
            {
                exam = new TestExam(c_f_vector[0], datafolder, user, c_f_vector[1], c_f_vector[0] + "-test-" + c_f_vector[1] + ".csv");
                exam->startExam();
            }
        }
        else if (user_command == 2)
        { // Train for test
            user->displayCourses();

            cout << "Select the corresponding number to the course to train >> ";
            int num;
            cin >> num;
            course_prof_name = user->getInternalContent()[num - 1];
            vector<string> c_f_vector = splitString2CourseAndProf(course_prof_name);

            vector<string> available_train_lists = listFilesInDirectory(datafolder, c_f_vector, "train");
            if (available_train_lists.empty())
            {
                cout << "No training file according to your input ..." << endl;
                while (true)
                {
                    cout << "Press [y] to go back to student main >> ";
                    char command;
                    cin >> command;
                    if (command == 'y')
                        break;
                }
                continue;
            }
            int train_idx = 1;
            for (const auto &vv : available_train_lists)
            {
                cout << train_idx << ". ";
                cout << vv << endl;
                ++train_idx;
            }

            while(true){
                cout << "Select the file to train by entering the idx : ";
                int user_idx;
                cin >> user_idx;
                if(user_idx <= available_train_lists.size()){
                    exam = new TrainExam(c_f_vector[0], datafolder, user, c_f_vector[1], available_train_lists[user_idx - 1]);
                    exam->startExam();
                    break;
                }
                cout << "Invalid input, please try again" << endl;
            }
            

            
        }
        else if (user_command == 3)
        { // Create train tests
            string outer_filepath;
            string course_name;
            string prof_name;
            cout << "Enter the FULL PATH of the csv file that you want to attach to our database >> ";
            cin >> outer_filepath;
            cout << "Enter the COURSE NAME that the csv file aims to train >> ";
            cin >> course_name;
            cout << "Enter the INSTRUCTOR NAME of the course that you are currently attending >> ";
            cin >> prof_name;

            string destination_filepath = "./" + datafolder + "/" + course_name + "-train-" + prof_name + "-" + generateRandomCode() + ".csv"; // (course name)-train-(professor name)-(random code)
            copyCSV(outer_filepath, destination_filepath);
        }
        else if (user_command == 4)
        { // Exit
            break;
        }
        else
        {
            cout << "Invalid input, please try again" << endl;
        }
        while (true)
        {
            cout << "Press [y] to go back to student main >> ";
            char command;
            cin >> command;
            if (command == 'y')
                break;
        }
    }
}

void professorMainMenu(User *user, string datafolder)
{
    int user_command;
    while (1)
    {
        clearConsole();
        setTextColor(3, -1);
        menuPrintButton(vector<string>{"Professor Main Menu", user->getName(), user->getId()});
        resetTextColor();
        cout << "\n" << endl;
        vector<string> ls = {"1. Create Test", "2. Inspect Results", "3. Exit"};
        printButton(ls);
        cout << "Enter your command >> ";
        cin >> user_command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (user_command == 1)
        { // Create exam
            string outer_filepath;
            string course_name;
            cout << "Enter the FULL PATH of the csv file that you want to attach to our database >> ";
            cin >> outer_filepath;
            cout << "Enter the COURSE NAME that the csv file aims to train >> ";
            cin >> course_name;

            string destination_filepath = "./" + datafolder + "/" + course_name + "-test-" + user->getName() + ".csv"; // (course name)-train-(professor name)-(random code)
            copyCSV(outer_filepath, destination_filepath);
        }
        else if (user_command == 2)
        { // Inspect results
            user->displayCourses();
            int num;
            while(true){
                cout << "Select number to view test exam results >> ";
                cin >> num;
                if(num <= user->getInternalContent().size()){ break; }
                cout << "Invalid input, please try again" << endl;
            }
           
            inspectResults(user, num - 1, datafolder);
        }
        else if (user_command == 3)
        { // Exit
            break;
        }
        else
        {
            cout << "Invalid input, please try again" << endl;
        }
        while (true)
        {
            cout << "Press [y] to go back to professor main >> ";
            char command;
            cin >> command;
            if (command == 'y')
                break;
        }
    }
}

void inspectResults(User *user, int idx, string datafolder)
{
    vector<string> instructings = user->getInternalContent();
    string course = instructings[idx];
    ifstream file(datafolder + "/" + course + "-" + user->getName() + "-exam_results.csv");
    string line;
    if (!file.is_open())
    {
        cerr << "error opening file" << endl;
        return;
    }
    while (getline(file, line))
    {
        if (!line.substr(0, 7).compare("Student"))
        {
            cout << "\n";
            setTextColor(10, -1);
            cout << line << endl;
            resetTextColor();
        }
        else
        {
            vector<string> tokens; // Vector to hold the split parts
            stringstream ss(line); // Create a stringstream from the string
            string token;

            while (getline(ss, token, ','))
            {                            // Split by the delimiter
                tokens.push_back(token); // Add each token to the vector
            }
            cout << tokens[0] << " ";
            setTextColor(13, -1);
            cout << tokens[1] << " ";
            resetTextColor();
            setTextColor(14, -1);
            cout << tokens[2] << " " << endl;
            resetTextColor();
        }
    }
}

int verifyUser(string &user_name, const string &user_id, const string &datafolder)
{
    /*
    return types -> 0 = file open error or empty file
                    1 = user is student
                    2 = user is professor
                    3 = user doesn't exist, try again or registerate
    Verifies whether there is a user(user_name + user_id) that matches in the DB and returns the type of the user(student or professor).
    */
    int return_value = 0;
    vector<vector<string>> csv_data = readCSV(datafolder, "student.csv");

    if (csv_data.empty())
    {
        return return_value;
    }

    for (const vector<string> vec : csv_data)
    {
        if (!transformString2Lower(user_name).compare(transformString2Lower(vec[0])) && !user_id.compare(vec[1]))
        {
            user_name = vec[0];
            return_value = 1;
            return return_value;
        }
    }

    csv_data = readCSV(datafolder, "professor.csv");
    for (const vector<string> vec : csv_data)
    {
        if (!transformString2Lower(user_name).compare(transformString2Lower(vec[0])) && !user_id.compare(vec[1]))
        {
            user_name = vec[0];
            return_value = 2;
            return return_value;
        }
    }

    return_value = 3;
    return return_value;
}

// Function to show available courses for a user
void showAvailableCourses(User *user, const string &datafolder, const string &filename)
{
    vector<string> courses; // To store available course information
    bool is_new_record = true;

    // Read CSV data
    vector<vector<string>> student_data = readCSV(datafolder, "/student.csv");
    vector<vector<string>> available_courses = readCSV(datafolder, filename);

    // Check if the user exists in the student CSV
    string userId = user->getId();

    // Find the row for the given userId
    for (size_t i = 0; i < available_courses.size(); i++)
    {
        if (!available_courses[i].empty() && available_courses[i][1] == userId)
        {
            is_new_record = false;
            break;
        }
    }
    if (is_new_record)
    {
        // Open the file for appending (datafolder/filename)
        ofstream out_file(datafolder + '/' + filename, ios::app);

        if (out_file.is_open())
        {
            out_file << user->getName() << "," << userId; // Write the userId
            for (string course : user->getInternalContent())
            {
                out_file << ",[O] " << course; // Write each course with [O] to indicate availability
            }
            out_file << endl;
            out_file.close();
        }
        else
        {
            cerr << "Unable to open the file!" << endl;
        }
    }
    int idx = 1;
    courses = fetchEnroledOrInstructing(user->getName(), user->getId(), datafolder, "courses_available.csv");
    for (string s : courses)
    {
        cout << idx << ". " << s << endl;
        idx++;
    }
}

bool updateAvailableState(User *user, const string &course, const string &datafolder, const string &filename)
{
    // Read the CSV file into a 2D vector
    vector<vector<string>> available_courses = readCSV(datafolder, filename);
    string userId = user->getId();
    int row = 0, target_pos = -1;

    // Find the row for the given userId
    for (size_t i = 0; i < available_courses.size(); i++)
    {
        if (!available_courses[i].empty() && available_courses[i][1] == userId)
        {
            row = i;
            break;
        }
    }

    // Find the column for the given course name
    for (size_t j = 2; j < available_courses[row].size(); j++)
    {
        // Check if the course name matches, any problem?
        string cell = available_courses[row][j];
        if (cell == "[O] " + course || cell == "[X] " + course)
        {
            target_pos = j;
            break;
        }
    }

    // If the course was not found, exit
    if (target_pos == -1)
    {
        cout << "Course not found for the user. Try again.\n";
        return false;
    }

    // Update the availability status
    if (available_courses[row][target_pos].substr(0, 3) == "[O]")
    {
        // Replace "[O]" with "[X]" but keep the course name
        available_courses[row][target_pos] = "[X] " + course;
    }
    else if (available_courses[row][target_pos].substr(0, 3) == "[X]")
    {
        cout << "You've already taken this course as completed. Try again.\n";
        return false;
    }

    // Open the file for writing (overwrite mode) to save updated data
    ofstream out_file(datafolder + '/' + filename, ios::trunc);
    if (out_file.is_open())
    {
        for (const auto &course_row : available_courses)
        {
            for (size_t i = 0; i < course_row.size(); ++i)
            {
                out_file << course_row[i];
                if (i < course_row.size() - 1)
                {
                    out_file << ","; // delimiter for CSV
                }
            }
            out_file << "\n";
        }
        out_file.close();
        return true;
    }
    else
    {
        cerr << "Failed to open the file for writing. Try again.\n";
        return false;
    }
}
