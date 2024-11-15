#include "exam.h"
#include "questions.h"
#include "user.h"
#include "dynamic_difficulty_engine.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void displayMenu();
int verifyUser(const string&, const string&, const string&);
vector<string> fetchEnroled(const string&, const string&, const string&);
vector<string> fetchInstructing(const string&, const string&, const string&);

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

    cout << "*** Welcome to Exam Management System ***";
    cout << "Verify yourself with your name and ID" << endl;
    cout << "Name : ";
    cin >> user_name;
    cout << "ID : ";
    cin >> user_id;

    cout << "Checking if your information is already in the database..." << endl;
    int userType = verifyUser(datafolder, user_name, user_id);

    Student user_s;
    Professor user_p();
    if (userType == 0) // can't open file
    {
        return 0;
    }
    else if (userType == 1) // student
    {
        Student user_s(user_name, user_id, fetchEnroled(user_name, user_id, datafolder));
    }
    else if (userType == 2) // professor
    {
        Student user_p(user_name, user_id, fetchInstructing(user_name, user_id, datafolder));
    }
    else if (userType == 3) // user name, ID not found in database
    {
    // Sign the new user to student or professor
    }
    else
    {
    // Optional default case handling
    }
    

    return 0;
}

vector<string> fetchEnroled(const string& name_s, const string& id_s, const string& datafolder){
    vector<string> ret_vec;
    string student_data = datafolder + "/student.txt";
    ifstream file_stream_student(student_data);

    if(!file_stream_student){
        cerr << "Can't open student.txt file";
        return;
    }

    string line;/*
    while(getline(file_stream_student, line)){
        int pos = line.find('/');
        name = line.substr(0, pos);
        id = line.substr(pos + 1, line.length());
        if(!name.compare(user_name) && !id.compare(user_id)){ // if the user_name, user_id has a matching pair inside the student.txt file
            file_stream_student.close();
            return return_value;
        }
    }
    */
    return ret_vec;
}

vector<string> fetchInstructing(const string& name_p, const string& id_p, const string& datafolder){
    vector<string> ret_vec;
    return ret_vec;
}

void displayMenu(){

}

int verifyUser(const string& datafolder, const string& user_name, const string& user_id){
    int return_value = 0;
    string name, id;
    string line;
    string student_data = datafolder + "/student.txt";
    ifstream file_stream_student(student_data);

    if(!file_stream_student){
        cerr << "Can't open student.txt file";
        return return_value;
    }

    while(getline(file_stream_student, line)){
        int pos = line.find('/');
        name = line.substr(0, pos);
        id = line.substr(pos + 1, line.length());
        if(!name.compare(user_name) && !id.compare(user_id)){ // if the user_name, user_id has a matching pair inside the student.txt file
            file_stream_student.close();
            return return_value;
        }
    }

    string professor_data = datafolder + "/professor.txt";
    ifstream file_stream_professor(professor_data);

    if(!file_stream_professor){
        cerr << "Can't open professor.txt file";
        return 0;
    }

    while(getline(file_stream_professor, line)){
        int pos = line.find('/');
        name = line.substr(0, pos);
        id = line.substr(pos + 1, line.length());
        if(!name.compare(user_name) && !id.compare(user_id)){ // if the user_name, user_id has a matching pair inside the professor.txt file
            return_value = 2;
            file_stream_professor.close();
            return return_value;
        }
    }

    return_value = 3;

    file_stream_student.close();
    file_stream_professor.close();
    return return_value;
}