#include "exam.h"
#include "questions.h"
#include "user.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void assignUserToDatabase(const string&, const string&, const string&);
void printButton(const vector<string>&);
void studentMainMenu(User*, string);
void professorMainMenu(User*, string);
int verifyUser(const string&, const string&, const string&);
vector<string> showAvailableCourses(User* user, const string& datafolder, const string& filename);
void updateAvailableState(User* user, const string& course, const string& datafolder, const string& filename);

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
    User* user;
    
    cout << "*** Welcome to Exam Management System ***";
    
    while(1){
        cout << "\nVerify yourself with your name and ID" << endl;
        cout << "Name >> ";
        cin >> user_name;
        cout << "ID >> ";
        cin >> user_id;
        int user_type = verifyUser(user_name, user_id, datafolder);
        cout << "Checking if your information is already in the database..." << endl;
        if (user_type == 0){ // can't open file
            return 0;
        }
        else if (user_type == 1){ // student
            cout << "You are a student!!" << endl;
            user = new Student(user_name, user_id, fetchEnroledOrInstructing(user_name, user_id, datafolder, "student.csv"));
            break;
        }
        else if (user_type == 2){ // professor
            cout << "You are a professor!!" << endl;
            user = new Professor(user_name, user_id, fetchEnroledOrInstructing(user_name, user_id, datafolder, "professor.csv"));           
            break;
        }
        else if (user_type == 3) { // user name, ID not found in database
            char command;
            cout << "No matching found(type 1 to retry, type 2 to registrate) >> ";
            cin >> command;
            if(command == '2'){
                //assignUserToDatabase(user_name, user_id, datafolder);
                cout << "Now try verifying your self again." << endl;
            }
        }
    }

    if(!string("7Student").compare(typeid(*user).name())){
        studentMainMenu(user, datafolder);
    } else if(!string("9Professor").compare(typeid(*user).name())){
        professorMainMenu(user, datafolder);
    }

    cout << "Program terminated" << endl;
    delete user;
    return 0;
}

void studentMainMenu(User* user, string datafolder){
    int user_command;
    string course_name;
    Exam* exam;
    while(1){
        cout << "Student Main Menu" << endl;
        cout << "==========" << endl;

        vector<string> ls = {"1. Take Exam", "2. Train for Test", "3. Create Train Test","4. Exit"};
        printButton(ls);
        cout << "Enter your command >> ";
        cin >> user_command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(user_command == 1){ // Take test exam
            /*
            show available courses to take exam(course name(instructor))
            show the current taken test status
            user selects which test to take
            bring csv file according to course name, instructor
            create exam object ~
            */
            vector<string> available_courses = showAvailableCourses(user, datafolder, "courses_available.csv");
            for (string s: available_courses) {
                cout << s << endl;
            }
            cout << "Select the course to take exam by entering the order: ";
            getline(cin, course_name);
            updateAvailableState(user, course_name, datafolder, "courses_available.csv");
        } else if (user_command == 2){ // Train for test

        } else if (user_command == 3){ // Create train tests
            
        } else if (user_command == 4){ // Exit
            break;
        } else{
            cout << "Invalid input, please try again" << endl;
        }
    }
}

void professorMainMenu(User* user, string datafolder){
    int user_command;
    for(const auto& v : user->getInternalContent()){
        cout << v;
    }
    while(1){
        cout << "Professor Main Menu" << endl;
        cout << "==========" << endl;

        vector<string> ls = {"1. Create Exam", "2. Inspect results", "3. Exit"};
        printButton(ls);
        cout << "Enter your command >> ";
        cin >> user_command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(user_command == 1){ // Create exam

        } else if (user_command == 2){ // Inspect results

        } else if (user_command == 3){ // Exit
            break;
        } else{
            cout << "Invalid input, please try again" << endl;
        }
    }
}

void printButton(const vector<string>& labels) {
    string interval = "   ";
    for (const string& label : labels){
        string btarget_pos(label.size() + 2, '-');
        cout << "+-" << btarget_pos << "-+" << interval;
    }
    cout<<"\n";
    for (const string& label : labels){
        cout << "|  " << label << "  |" << interval;
    }
    cout<<"\n";
    for (const string& label : labels){
        string btarget_pos(label.size() + 2, '-');
        cout << "+-" << btarget_pos << "-+" << interval;
    }
    cout<<"\n";
}

// Do not use this yet
// void assignUserToDatabase(const string& name, const string& id, const string& datapath) {
//     /*
//     Assigning a new user(student or professor) to the DB.
//     */
//     string version;
//     cout << "Which type of user do you want to registrate (type s for student, type p for professor)? >> ";
//     cin >> version;
//
//     ofstream file_stream;
//     openUserFileForWrite(file_stream, datapath, version);
//
//     if (!file_stream) {
//         cerr << "Failed to open the file for writing." << endl;
//         return;
//     }
//
//     file_stream << '\n' << name << "/" << id;
//     cout << "User \'" << name << "\' with ID \'" << id << "\' has been registered successfully." << endl;
//
//     file_stream.close();
// }

int verifyUser(const string& user_name, const string& user_id, const string& datafolder){
    /*
    return types -> 0 = file open error or empty file
                    1 = user is student
                    2 = user is professor
                    3 = user doesn't exist, try again or registerate
    Verifies whether there is a user_name + user_id that matches in the DB
    */
    int return_value = 0;
    vector<vector<string>> csv_data = readCSV(datafolder, "student.csv");

    if(csv_data.empty()){return return_value;}

    for(const vector<string> vec : csv_data){
        if(!user_name.compare(vec[0]) && !user_id.compare(vec[1])){
            return_value = 1;
            return return_value;
        }
    }

    csv_data = readCSV(datafolder, "professor.csv");
    for(const vector<string> vec : csv_data){
        if(!user_name.compare(vec[0]) && !user_id.compare(vec[1])){
            return_value = 2;
            return return_value;
        }
    }

    return_value = 3;
    return return_value;
}

// Function to show available courses for a user
vector<string> showAvailableCourses(User* user, const string& datafolder, const string& filename) {
    vector<string> courses; // To store available course information
    bool is_new_record = true;

    // Read CSV data
    vector<vector<string>> student_data = readCSV(datafolder, "/student.csv");
    vector<vector<string>> available_courses = readCSV(datafolder, filename);

    // Check if the user exists in the student CSV
    string userId = user->getId();
    size_t row = 0;

    // Find the row for the given userId
    for (size_t i = 0; i < available_courses.size(); i++) {
        if (!available_courses[i].empty() && available_courses[i][1] == userId) {
            is_new_record = false;
            break;
        }
    }

    if (is_new_record) {
        // Open the file for appending (datafolder/filename)
        ofstream out_file(datafolder + '/' + filename, ios::app);

        if (out_file.is_open()) {
            out_file << user->getName() << "," << userId; // Write the userId
            for (string course : user->getInternalContent()) {
                out_file << ",[O] " << course; // Write each course with [O] to indicate availability
            }
            out_file << endl;
            out_file.close();
        } else {
            cerr << "Unable to open the file!" << endl;
        }
    }
    courses = fetchEnroledOrInstructing(user->getName(), user->getId(), datafolder, "courses_available.csv");
    return courses;
}


void updateAvailableState(User* user, const string& course, const string& datafolder, const string& filename) {
    // Read the CSV file into a 2D vector
    vector<vector<string>> available_courses = readCSV(datafolder, filename);
    string userId = user->getId();
    int row = 0, target_pos = -1;

    // Find the row for the given userId
    for (int i = 0; i < available_courses.size(); i++) {
        if (!available_courses[i].empty() && available_courses[i][1] == userId) {
            row = i; // Save the row position
            break;
        }
    }

    // Find the column for the given course name
    for (int j = 2; j < available_courses[row].size(); j++) {
        // Check if the course name matches, any problem?
        string cell = available_courses[row][j];
        if (cell == "[O] " + course || cell == "[X] " + course) {
            target_pos = j;
            break;
        }
    }

    // If the course was not found, exit
    if (target_pos == -1) {
        cout << "Course not found for the user.\n";
        return;
    }

    // Update the availability status
    if (available_courses[row][target_pos].substr(0, 3) == "[O]") {
        // Replace "[O]" with "[X]" but keep the course name
        available_courses[row][target_pos] = "[X] " + course;
    } else if (available_courses[row][target_pos].substr(0, 3) == "[X]") {
        cout << "You've already marked this course as completed.\n";
        return;
    } else {
        // If the course is not marked, assume it's available and mark it as completed
        available_courses[row][target_pos] = "[X] " + course;
    }

    // Open the file for writing (overwrite mode) to save updated data
    ofstream out_file(datafolder + '/' + filename, ios::trunc);
    if (out_file.is_open()) {
        for (const auto& course_row : available_courses) {
            for (size_t i = 0; i < course_row.size(); ++i) {
                out_file << course_row[i];
                if (i < course_row.size() - 1) {
                    out_file << ","; // delimiter for CSV
                }
            }
            out_file << "\n"; // new line for next row
        }
        out_file.close();
    } else {
        cerr << "Failed to open the file for writing.\n";
    }
}

