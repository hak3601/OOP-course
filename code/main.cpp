// #include "exam.cpp"
#include "questions.cpp"
#include "user.cpp"
#include "dynamic_difficulty_engine.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void openUserFileForRead(ifstream&, const string&, const string&);
void openUserFileForWrite(ofstream&, const string&, const string&);
void assignUserToDatabase(const string&, const string&, const string&);
void displayMenu();
int verifyUser(const string&, const string&, const string&);
vector<string> fetchEnroled(const string&, const string&, const string&);
vector<string> fetchInstructing(const string&, const string&, const string&);
vector<string> parseString2Vec(string);

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
        int user_type = verifyUser(user_name, user_id, datafolder);
        cout << "Checking if your information is already in the database..." << endl;
        if (user_type == 0){ // can't open file
            return 0;
        }
        else if (user_type == 1){ // student
            cout << "You are a student!!" << endl;
            Student user_s(user_name, user_id, fetchEnroled(user_name, user_id, datafolder));
            break;
        }
        else if (user_type == 2){ // professor
            cout << "You are a professor!!" << endl;
            Professor user_p(user_name, user_id, fetchInstructing(user_name, user_id, datafolder));
            break;
        }
        else if (user_type == 3) { // user name, ID not found in database
            char command;
            cout << "No matching found(type 1 to retry, type 2 to registrate) >> ";
            cin >> command;
            if(command == '2'){
                assignUserToDatabase(user_name, user_id, datafolder);
                cout << "Know try verifying your self again." << endl;
            }
                
        }
    }
    
    while(1){
        
    }
    return 0;
}

void openUserFileForRead(ifstream& file_stream, const string& datafolder, const string& version) {
    /*
    Opens stream for reading
    */
    if (version == "s") {
        file_stream.open(datafolder + "/student.txt");
    } 
    else if (version == "p") {
        file_stream.open(datafolder + "/professor.txt");
    } 
    else {
        cerr << "Invalid openUserFileForRead version" << endl;
    }
}

void openUserFileForWrite(ofstream& file_stream, const string& datafolder, const string& version) {
    /*
    Opens stream for writing
    */
    if (version == "s") {
        file_stream.open(datafolder + "/student.txt", ios::app);
    } 
    else if (version == "p") {
        file_stream.open(datafolder + "/professor.txt", ios::app);
    } 
    else {
        cerr << "Invalid openUserFileForWrite version" << endl;
    }
}

void assignUserToDatabase(const string& name, const string& id, const string& datapath) {
    /*
    Assigning a new user(student or professor) to the DB.
    */
    string version;
    cout << "Which type of user do you want to registrate (type s for student, type p for professor)? >> ";
    cin >> version;

    ofstream file_stream;
    openUserFileForWrite(file_stream, datapath, version);

    if (!file_stream) {
        cerr << "Failed to open the file for writing." << endl;
        return;
    }

    file_stream << '\n' << name << "/" << id;
    cout << "User \'" << name << "\' with ID \'" << id << "\' has been registered successfully." << endl;

    file_stream.close();
}

vector<string> parseString2Vec(string input){
    /*
    return type -> a vector that parsed input string

    The input is either string of enroled_courses or instructing_courses.
    Thus this function converts the input string to a vector. 
    */
    vector<string> tokens;
    size_t start = 0;
    size_t end = input.find(",");
    
    while (end != string::npos) {
        tokens.push_back(input.substr(start, end - start)); // Extract substring
        start = end + 1; // Move start position past the delimiter
        end = input.find(",", start); // Find next occurrence of the delimiter
    }
    
    // Add the last token (or the entire string if no delimiter was found)
    tokens.push_back(input.substr(start));
    return tokens;
}

vector<string> fetchEnroled(const string& name_s, const string& id_s, const string& datafolder){
    /*
    return type -> a vector that contains 'enroled course' informations about a particular student
    */
    vector<string> ret_vec;
    ifstream file_stream_student;
    openUserFileForRead(file_stream_student, datafolder, "s");
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
            return parseString2Vec(list);
        }
    }
    file_stream_student.close();
    return ret_vec;
}

vector<string> fetchInstructing(const string& name_p, const string& id_p, const string& datafolder){
    /*
    return type -> a vector that contains 'instructing course' informations about a particular professor
    */
    vector<string> ret_vec;
    ifstream file_stream_professor;
    openUserFileForRead(file_stream_professor, datafolder, "p");
    string name, id;
    string line;
    while(getline(file_stream_professor, line)){
        int pos = line.find('/');
        name = line.substr(0, pos);
        id = line.substr(pos + 1, 8);
        if(!name.compare(name_p) && !id.compare(id_p)){ // if the user_name, user_id has a matching pair inside the professor.txt file
            int cur_pos = pos + 10;
            string list = line.substr(cur_pos);
            file_stream_professor.close();
            return parseString2Vec(list);
        }
    }
    return ret_vec;
}

void displayMenu(){
    /*
    
    */

}

int verifyUser(const string& user_name, const string& user_id, const string& datafolder){
    /*
    return types -> 0 = file open error
                    1 = user is student
                    2 = user is professor
                    3 = user doesn't exist, try again or registerate
    Verifies whether there is a user_name + user_id that matches in the DB
    */
    int return_value = 0;
    string name, id;
    string line;
    ifstream file_stream_student;
    openUserFileForRead(file_stream_student, datafolder, "s");
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

    ifstream file_stream_professor;
    openUserFileForRead(file_stream_professor, datafolder, "p");

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