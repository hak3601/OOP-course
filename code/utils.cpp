#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include "questions.h"
/**/
#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#endif
/**/
using namespace std;
/*---------------------------------------------------------------------------------------------------------------------------------------*/

vector<string> listFilesInDirectory(const string& folderPath, vector<string>& additional_info, const string& version) {
    vector<string> lists;
    string parse = additional_info[0] + "-"+version+"-" + additional_info[1];

#ifdef _WIN32
    // Windows-specific code using FindFirstFile and FindNextFile
    WIN32_FIND_DATA fileData;
    HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &fileData); // Add wildcard to find all files

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error: Unable to open directory at " << folderPath << endl;
        return lists;
    }

    do {
        string fileName = fileData.cFileName;

        // Skip "." and ".."
        if (fileName == "." || fileName == "..") {
            continue;
        }

        // Check if it's a file
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (fileName.length() >= parse.length() &&
                fileName.substr(0, parse.length()).compare(parse) == 0) {
                lists.push_back(fileName);
            }
        }
    } while (FindNextFile(hFind, &fileData) != 0);

    FindClose(hFind);

#else
    // Linux/Unix-specific code using opendir and readdir
    DIR* dir = opendir(folderPath.c_str()); // Open the directory
    if (!dir) {
        cerr << "Error: Unable to open directory at " << folderPath << endl;
        return lists;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string fileName = entry->d_name;

        // Skip "." and ".."
        if (fileName == "." || fileName == "..") {
            continue;
        }

        // Check if it's a regular file (DT_REG)
#ifdef DT_REG
        if (entry->d_type == DT_REG) {
#endif
            if (fileName.length() >= parse.length() &&
                fileName.substr(0, parse.length()).compare(parse) == 0) {
                lists.push_back(fileName);
            }
#ifdef DT_REG
        }
#endif
    }
    closedir(dir); // Close the directory
#endif
    if(lists.empty()){
        cerr << "No such file found" << endl;
    }
    return lists;
}

string generateRandomCode() {
    // Create a random number generator
    random_device rd;   // Seed
    mt19937 gen(rd());  // Mersenne Twister random number generator

    // Define the range [1000, 9999] for a 4-digit code
    uniform_int_distribution<int> dist(1000, 9999);

    return to_string(dist(gen)); // Generate the random number
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
    string colors[] = {
        "\033[30m", // Black
        "\033[31m", // Red
        "\033[32m", // Green
        "\033[33m", // Yellow,3
        "\033[34m", // Blue
        "\033[35m", // Magenta
        "\033[36m", // Cyan
        "\033[37m", // White
        "\033[90m", // Bright Black (Gray)
        "\033[91m", // Bright Red
        "\033[92m", // Bright Green/10
        "\033[93m", // Bright Yellow
        "\033[94m", // Bright Blue/12
        "\033[95m", // Bright Magenta
        "\033[96m", // Bright Cyan
        "\033[97m"  // Bright White
    };
    // Background color codes (ANSI escape codes)
    string backgroundColors[] = {
        "\033[40m",  // Black
        "\033[41m",  // Red
        "\033[42m",  // Green
        "\033[43m",  // Yellow
        "\033[44m",  // Blue
        "\033[45m",  // Magenta
        "\033[46m",  // Cyan
        "\033[47m",  // White
        "\033[100m", // Bright Black (Gray)
        "\033[101m", // Bright Red
        "\033[102m", // Bright Green
        "\033[103m", // Bright Yellow
        "\033[104m", // Bright Blue
        "\033[105m", // Bright Magenta
        "\033[106m", // Bright Cyan
        "\033[107m"  // Bright White
    };

    if (foreground >= 0 && foreground < 16) {
        cout << colors[foreground];
    }

    // Background color handling (optional)
    if (background >= 0 && background < 16) {
        cout << backgroundColors[background];
    }
}
// 10, -1
void resetTextColor() {
    cout << "\033[0m"; // Reset to default color
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
    if (openParenPos != string::npos && closeParenPos != string::npos && closeParenPos > openParenPos) {
        // Extract the course part
        ret_vec[0] = course_prof.substr(0, openParenPos);
        // Extract the professor part
        ret_vec[1] = course_prof.substr(openParenPos + 1, closeParenPos - openParenPos - 1);
    } else {
        // Handle invalid format
        throw invalid_argument("Invalid input format. Expected: course(professor)");
    }
    return ret_vec;
}



bool checkCSVLineFormat(const string& line){
    vector<string> tokens;
    string token;
    char delimiter = ',';
    stringstream ss(line);

    while (getline(ss, token, delimiter)) { // Split by the delimiter
        tokens.push_back(token); // Add each token to the vector
    } // question format(0), question index(1), question text(2), question answer(3), question point(4), //question choices(5) 
    if((!tokens[0].compare("MC") && tokens.size() == 6) || ((!tokens[0].compare("TF") || !tokens[0].compare("CQ")) && tokens.size() == 5)){
        try{
            size_t is_integer;
            stoi(tokens[1], &is_integer);
            stoi(tokens[4], &is_integer);
            return true;
        } catch (invalid_argument&){
            cerr << "Question index or point is not an integer type. " << "Got " << tokens[1] << ", " << tokens[4] << " instead." << endl;
        }
    } else{
        cerr << "Question format(argument count) should be either TF(5), MC(6), CQ(5). " << "However " << tokens[0] << "(" << tokens.size() << ") was given." << endl;
        cerr << "error raised from -> " << line << endl;
    }
    return false;
}

void copyCSV(const string& sourceFilePath, const string& destFilePath) {
    ifstream inFile(sourceFilePath); // Open the source CSV file
    if (!inFile.is_open()) {
        cerr << "Error: Could not open the source file at " << sourceFilePath << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if(!checkCSVLineFormat(line)){
            inFile.close();
            return;
        }
    }
    inFile.clear();          // Clear EOF flag if end of file was reached
    inFile.seekg(0, ios::beg);

    ofstream outFile(destFilePath); // Open the destination CSV file
    if (!outFile.is_open()) {
        cerr << "Error: Could not create the destination file at " << destFilePath << endl;
        return;
    }

    while (getline(inFile, line)) {
        outFile << line << endl;
    }

    cout << "File copied successfully from " << sourceFilePath << " to " << destFilePath << endl;

    inFile.close();
    outFile.close();
}