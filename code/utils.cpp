#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "questions.h"
using namespace std;

/*---------------------------------------------------------------------------------------------------------------------------------------*/

vector<vector<string>> readCSV(const string& datafolder, const string& filename) {
    vector<vector<string>> data;
    string f_name = datafolder + "/" + filename;
    ifstream file(f_name);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string value;

        // Split by comma
        while (getline(ss, value, ',')) {
            row.push_back(value);
        }

        // Add the row to the 2D vector
        data.push_back(row);
    }
    file.close();
    return data;
}

vector<string> parseString2Vec(string input){
    /*
    return type -> a vector that parsed input string

    The input is either string of enroled_courses or instructing_courses.
    Thus this function converts the input string to a vector.
    user's course (csv_data) to vector (string)? readCSV already has done 
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

vector<string> fetchEnroledOrInstructing(const string& user_name, const string& user_id, const string& datafolder, const string& filename){
    /*
    return type -> a vector that contains 'enroled course' informations about a particular student
    */
    vector<string> ret_vec;
    vector<vector<string>> csv_data = readCSV(datafolder, filename);
    for(const vector<string> vec : csv_data){
        if(!user_name.compare(vec[0]) && !user_id.compare(vec[1])){
            for (size_t i = 2; i < vec.size(); i++){
                ret_vec.push_back(vec[i]);
            }
            break;
        }
    }
    return ret_vec;
}

vector<Question*> vec2Questions(vector<vector<string>> q_vec){
    // just to show whether the questions are read properly
    vector<Question*> ret_qvec;

    for(const auto& v : q_vec){
        Question* q;
        string q_version = v[0];
        if (q_version == "TF"){
            q = new TrueFalseQuestion((v[0]),stoi(v[1]),v[2],stoi(v[4]),v[3]); //string q_ver ,int idx, const string &text, int point, const string& correct_answer
        } else if(q_version == "MC"){
            q = new MultipleChoiceQuestion(v[0],stoi(v[1]),v[2],stoi(v[4]),v[5],v[3]);
        } else if(q_version == "CQ"){
            q = new CompletionQuestion(v[0],stoi(v[1]),v[2],stoi(v[4]),v[3]);
        }
        ret_qvec.push_back(q);
    }
    return ret_qvec;
}


void setTextColor(int foreground, int background = -1) {
    // Foreground color codes (ANSI escape codes)
    std::string colors[] = {
        "\033[30m", // Black
        "\033[31m", // Red
        "\033[32m", // Green
        "\033[33m", // Yellow
        "\033[34m", // Blue
        "\033[35m", // Magenta
        "\033[36m", // Cyan
        "\033[37m", // White
        "\033[90m", // Bright Black (Gray)
        "\033[91m", // Bright Red
        "\033[92m", // Bright Green
        "\033[93m", // Bright Yellow
        "\033[94m", // Bright Blue
        "\033[95m", // Bright Magenta
        "\033[96m", // Bright Cyan
        "\033[97m"  // Bright White
    };

    if (foreground >= 0 && foreground < 16) {
        std::cout << colors[foreground];
    }

    // Background color handling (optional)
    if (background >= 0 && background < 16) {
        std::cout << "\033[" << (background + 40) << "m"; // Background color codes start from 40
    }
}
// 10, -1
void resetTextColor() {
    std::cout << "\033[0m"; // Reset to default color
}

// Clear the console screen
void clearConsole() {


    #if defined(_WIN32)
    system("cls");
    #else
    cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    #endif
}

vector<string> splitString2CourseAndProf(string course_prof){
    size_t openParenPos = course_prof.find('(');
    // Find the position of the closing parenthesis
    size_t closeParenPos = course_prof.find(')');
    vector<string> ret_vec = {"",""};
    // Validate the input format
    if (openParenPos != std::string::npos && closeParenPos != std::string::npos && closeParenPos > openParenPos) {
        // Extract the course part
        ret_vec[0] = course_prof.substr(0, openParenPos);
        // Extract the professor part
        ret_vec[1] = course_prof.substr(openParenPos + 1, closeParenPos - openParenPos - 1);
    } else {
        // Handle invalid format
        throw std::invalid_argument("Invalid input format. Expected: course(professor)");
    }
    return ret_vec;
}