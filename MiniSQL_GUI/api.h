#pragma once
#ifndef API_H
#define API_H

#include <iostream>
#include <vector>
#include <string>
#include "AttriValue.h"
#include "CatalogManager.h"
#include "Condition.h"
#include "recordmanage.h"

class API {
public:
    bool createtable(const std::string&tablename, std::vector<AttriValue>*valuein);
    bool droptable(const std::string&tablename);
    bool createindex(const std::string&indexname, const std::string&tablename, const std::string&atrrubename);
    bool dropindex(const std::string&indexname);
    bool insertrecord(const std::string&tablename, std::vector<std::string>*info);
    bool deleterecord(const std::string&tablename,std::vector<Condition>*Conditions);
    bool selectrecord(const std::string&tablename,std::vector<std::string>*selectinfo, std::vector<Condition>*condition);
private:
    RecordManager mr;
    CatalogManager mc;

};

#endif // API_H
