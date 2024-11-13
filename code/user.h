#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;
class User{
private:
    string name;
    int id;
public:
    User(string);
    User(int );
    User(const User&);
    ~User();



};

#endif 