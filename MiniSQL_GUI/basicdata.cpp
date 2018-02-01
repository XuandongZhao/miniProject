#include "stdafx.h"
#include "basicdata.h"
using namespace std;
keytype changetype(int type)
{
    if (type == 0)	return isint;
    if (type == 1)	return isfloat;
    if (type == 2)	return ischar;
    else {
        std::cerr << "UNKNOW TYPE IN CHANGETYPE" << '\n';
    }
}

std::string intdata::tostring()
{
    sprintf(buf, "%04x", data);
    return std::string(buf);
}
std::string floatdata::tostring()
{
    b.data = data;
    sprintf(buf, "%04x", b.fint);
    return std::string(buf);
}
std::string stringdata::tostring()
{
    return data;
}
const std::string path = "C://zxd_CS//file";
