#pragma once
#ifndef ATTRIVALUE_H
#define ATTRIVALUE_H
#include <iostream>

struct AttriValue
{
    bool isPrimary = 0, isUnique = 0, isNull = 0;
    int cntintable;
    int length, type;
    std::string AtrributeName;
    std::string strVal;
    int intVal;
    float FloatVal;
    bool operator ==(const AttriValue &f)
    {
        if (isPrimary != f.isPrimary || isUnique != f.isUnique || isNull != f.isNull || AtrributeName != f.AtrributeName)
        {
            return false;
        }
        if (isNull)
        {
            return true;
        }
        if (type == 0)
        {
            return intVal == f.intVal;
        }
        if (type == 1)
        {
            return FloatVal == f.FloatVal;
        }
        if (type == 2)
        {
            return strVal == f.strVal;
        }
    }
};

#endif // ATTRIVALUE_H
