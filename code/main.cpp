// #include "exam.cpp"
#include "questions.cpp"
#include "user.cpp"
#include "dynamic_difficulty_engine.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void assignUserToDatabase(string, string);
void displayMenu();
int verifyUser(const string&, const string&, const string&);
vector<string> fetchEnroled(const string&, const string&, const string&);
vector<string> fetchInstructing(const string&, const string&, const string&);
vector<string> getVector(string);

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
    Student user_s;
    Professor user_p;

    cout << "*** Welcome to Exam Management System ***";

    while(1){
        cout << "\nVerify yourself with your name and ID" << endl;
        cout << "Name >> ";
        cin >> user_name;
        cout << "ID >> ";
        cin >> user_id;

        cout << "Checking if your information is already in the database..." << endl;
        switch (verifyUser(datafolder, user_name, user_id)) {
            case 0: // can't open file
                return 0;

            case 1: { // student
                cout << "You are a student!!" << endl;
                Student user_s(user_name, user_id, fetchEnroled(user_name, user_id, datafolder));
                break;
            }

            case 2: { // professor
                cout << "You are a professor!!" << endl;
                Professor user_p(user_name, user_id, fetchInstructing(user_name, user_id, datafolder));
                break;
            }

            case 3: { // user name, ID not found in database
                char command;
                cout << "No matching found(type 1 to retry, type 2 to registrate) >> ";
                cin >> command;
                if (command == '2') {
                    assignUserToDatabase(user_name, user_id);
                }
                break;
            }

            default: // Optional default case handling
                // Handle other unexpected cases
                break;
        }

    }
    
    

    return 0;
}

void assignUserToDatabase(string name, string id){

}

vector<string> getVector(string input){
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = input.find(",");
    
    while (end != std::string::npos) {
        tokens.push_back(input.substr(start, end - start)); // Extract substring
        start = end + 1; // Move start position past the delimiter
        end = input.find(",", start); // Find next occurrence of the delimiter
    }
    
    // Add the last token (or the entire string if no delimiter was found)
    tokens.push_back(input.substr(start));
    return tokens;
}

vector<string> fetchEnroled(const string& name_s, const string& id_s, const string& datafolder){
    vector<string> ret_vec;
    string student_data = datafolder + "/student.txt";
    ifstream file_stream_student(student_data);
    string name, id;
    string line;
    while(getline(file_stream_student, line)){
        int pos = line.find('/');
        name = line.substr(0, pos);
        id = line.substr(pos + 1, 8);
        if(!name.compare(name_s) && !id.compare(id_s)){ // if the user_name, user_id has a matching pair inside the student.txt file
            int cur_pos = pos + 10;
            string list = line.substr(cur_pos);
            file_stream_student.close();
            return getVector(list);
        }
    }
    return ret_vec;
}

vector<string> fetchInstructing(const string& name_p, const string& id_p, const string& datafolder){
    vector<string> ret_vec;
    string student_data = datafolder + "/professor.txt";
    ifstream file_stream_student(student_data);
    string name, id;
    string line;
    while(getline(file_stream_student, line)){
        int pos = line.find('/');
        name = line.substr(0, pos);
        id = line.substr(pos + 1, 8);
        if(!name.compare(name_p) && !id.compare(id_p)){ // if the user_name, user_id has a matching pair inside the professor.txt file
            int cur_pos = pos + 10;
            string list = line.substr(cur_pos);
            file_stream_student.close();
            return getVector(list);
        }
    }
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
        id = line.substr(pos + 1, 8);
        if(!name.compare(user_name) && !id.compare(user_id)){ // if the user_name, user_id has a matching pair inside the student.txt file
            return_value = 1;
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
        id = line.substr(pos + 1, 8);
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