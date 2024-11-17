#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string value;

        // Split by comma
        while (std::getline(ss, value, ',')) {
            row.push_back(value);
        }

        // Add the row to the 2D vector
        data.push_back(row);
    }

    return data;
}

class Parent{
protected:
    int var1;
public:
    Parent(int a) : var1(a) {}
    virtual int f1() = 0; 
};

class Child : public Parent{
private:
    int var2;
public:
    Child(int a, int b) : Parent(a), var2(b) {}
    int f1(){return var2;}; 
};

int main() {
    
    Parent* p;
    if(1){
        Child c(1,2);
        p = &c;
    }
    cout<<typeid(*p).name()<<endl;
    cout << p->f1();
    exit(1);
    std::string filename = "data/Artificial_intelligence-TF-train.csv";
    filename = "data/professor.csv";
    std::vector<std::vector<std::string>> csvData = readCSV(filename);

    // Print the values (optional)
    for (const auto& row : csvData) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
