#pragma once
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include "AttriValue.h"
#include "API.h"
#include "Condition.h"
#include <vector>
#include <string>

class Interpreter {
public:
    std::string filename;
    std::string word;
    int interpreter(std::string s);
    std::string getword(std::string s, int &num);
    bool exec_create(std::string s, int &num);
    bool exec_select(std::string s, int &num);
    bool exec_drop(std::string s, int &num);
    bool exec_delete(std::string s, int &num);
    bool exec_insert(std::string s, int &num);
    //string normolize(string s);
    Interpreter() {}
    ~Interpreter() {}
    API myapi;
};
class SyntaxException {};


#endif // INTERPRETER_H
