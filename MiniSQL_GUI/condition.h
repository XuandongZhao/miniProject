#pragma once
#ifndef CONDITION_H
#define CONDITION_H
#include <string>
#include <sstream>


class Condition
{
public:
    enum Operator {
        OPERATOR_EQUAL, OPERATOR_NOT_EQUAL, OPERATOR_LST, OPERATOR_MOT,
        OPERATOR_LESS_EQUAL, OPERATOR_MORE_EQUAL
    };


    std::string attriName;
    std::string value;
    int OP;
    Condition(void);
    Condition(std::string attr, std::string val, int op);
    bool check(int Int);
    bool check(float Float);
    bool check(std::string Str);
};

#endif // CONDITION_H
