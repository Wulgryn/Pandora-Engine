#include "string.hpp"

#include <iostream>
using namespace std;
using namespace utils;

string strings::replace(string& str, string what, string to)
{
    size_t pos = 0;
    while ((pos = str.find(what.c_str())) != string::npos){
        str.replace(pos, what.size(), to);
    }
    return str;
}