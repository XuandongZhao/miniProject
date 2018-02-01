#include "stdafx.h"
#include "condition.h"
using namespace std;
bool Condition::check(int Int)
{
    /*char buf[6];
    int thisInt;
    strcpy(buf, value.c_str());
    thisInt = *reinterpret_cast<int*>(buf);*/
    stringstream ss;
    ss << value;
    int thisInt;
    ss >> thisInt;

    switch (OP)
    {
    case OPERATOR_EQUAL:
        return Int == thisInt;
    case OPERATOR_NOT_EQUAL:
        return Int != thisInt;
    case OPERATOR_LST:
        return Int < thisInt;
    case OPERATOR_MOT:
        return Int > thisInt;
    case OPERATOR_LESS_EQUAL:
        return Int <= thisInt;
    case OPERATOR_MORE_EQUAL:
        return Int >= thisInt;
    default:
        return true;
    }
}

bool Condition::check(float Float)
{

    float thisFloat;
    char buf[6];
    buf[0] = value[0];
    buf[1] = value[1];
    buf[2] = value[2];
    buf[3] = value[3];
    thisFloat = *reinterpret_cast<float*>(buf);
    //stringstream ss;
    //ss << value;
    //float thisFloat;
    //ss >> thisFloat;
    switch (OP)
    {
    case OPERATOR_EQUAL:
        return Float == thisFloat;
    case OPERATOR_NOT_EQUAL:
        return Float != thisFloat;
    case OPERATOR_LST:
        return Float < thisFloat;
    case OPERATOR_MOT:
        return Float > thisFloat;
    case OPERATOR_LESS_EQUAL:
        return Float <= thisFloat;
    case OPERATOR_MORE_EQUAL:
        return Float >= thisFloat;
    default:
        return true;
    }
}

bool Condition::check(std::string Str)
{
    std::string thisStr = value;

    switch (OP)
    {
    case OPERATOR_EQUAL:
        return Str == thisStr;
    case OPERATOR_NOT_EQUAL:
        return Str != thisStr;
    case OPERATOR_LST:
        return Str < thisStr;
    case OPERATOR_MOT:
        return Str > thisStr;
    case OPERATOR_LESS_EQUAL:
        return Str <= thisStr;
    case OPERATOR_MORE_EQUAL:
        return Str >= thisStr;
    default:
        return true;
    }
}

Condition::Condition(std::string attr, std::string val, int op)
{
    attriName = attr;
    value = val;
    OP = op;
}
Condition::Condition(void) :attriName(""), value(""), OP(0)
{

}
