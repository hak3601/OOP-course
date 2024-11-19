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
    for(const auto& v : q_vec){
        string q_version = v[0];
        
        cout<<""<<endl;
    }
    exit(1);
}