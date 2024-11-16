// #include "exam.cpp"
#include "questions.cpp"
#include "user.cpp"
#include "dynamic_difficulty_engine.cpp"
#include "utils.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void assignUserToDatabase(const string&, const string&, const string&);
void printButton(const vector<string>&);
void displayMainMenu();
int verifyUser(const string&, const string&, const string&);

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
            Student user_s(user_name, user_id, fetchEnroledOrInstructing(user_name, user_id, datafolder, "student.csv"));
            user = &user_s;
            break;
        }
        else if (user_type == 2){ // professor
            cout << "You are a professor!!" << endl;
            Professor user_p(user_name, user_id, fetchEnroledOrInstructing(user_name, user_id, datafolder, "professor.csv"));
            user = &user_p;
            
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

    int user_command;

    while(1){
        displayMainMenu();
        cout << "Enter your command >> ";
        cin >> user_command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(user_command == 1){ // Take exam

        } else if (user_command == 2){ // Train for test

        } else if (user_command == 3){ // Create test
            
        } else if (user_command == 4){ // Create train test
            
        } else if (user_command == 5){ // Exit
            break;
        } else{
            cout << "Invalid input, please try again" << endl;
        }
    }
    cout << "Program terminated" << endl;
    return 0;
}

void printButton(const vector<string>& labels) {
    string interval = "   ";
    for (const string& label : labels){
        string border(label.size() + 2, '-');
        cout << "+-" << border << "-+" << interval;
    }
    cout<<"\n";
    for (const string& label : labels){
        cout << "|  " << label << "  |" << interval;
    }
    cout<<"\n";
    for (const string& label : labels){
        string border(label.size() + 2, '-');
        cout << "+-" << border << "-+" << interval;
    }
    cout<<"\n";
}

void displayMainMenu() {
    cout << "Main Menu" << endl;
    cout << "==========" << endl;

    vector<string> ls = {"1. Take Exam","2. Train for Test","3. Create Test","4. Create Train Test","5. Exit"};
    printButton(ls);
}

// Do not use this yet
// void assignUserToDatabase(const string& name, const string& id, const string& datapath) {
//     /*
//     Assigning a new user(student or professor) to the DB.
//     */
//     string version;
//     cout << "Which type of user do you want to registrate (type s for student, type p for professor)? >> ";
//     cin >> version;

//     ofstream file_stream;
//     openUserFileForWrite(file_stream, datapath, version);

//     if (!file_stream) {
//         cerr << "Failed to open the file for writing." << endl;
//         return;
//     }

//     file_stream << '\n' << name << "/" << id;
//     cout << "User \'" << name << "\' with ID \'" << id << "\' has been registered successfully." << endl;

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
    vector<vector<string>> csvData = readCSV(datafolder, "student.csv");

    if(csvData.empty()){return return_value;}

    for(const vector<string> vec : csvData){
        if(!user_name.compare(vec[0]) && !user_id.compare(vec[1])){
            return_value = 1;
            return return_value;
        }
    }

    csvData = readCSV(datafolder, "professor.csv");
    for(const vector<string> vec : csvData){
        if(!user_name.compare(vec[0]) && !user_id.compare(vec[1])){
            return_value = 2;
            return return_value;
        }
    }

    return_value = 3;
    return return_value;
}