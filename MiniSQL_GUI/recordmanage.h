#pragma once
#ifndef RECORDMANAGE_H
#define RECORDMANAGE_H

#include <string>
#include <iostream>
#include "buffmanage.h"
#include "CatalogManager.h"
#include "Condition.h"
#include "AttriValue.h"
#include "bplus_tree.h"
#include <queue>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include "recordmanage.h"
#include <stdlib.h>
#include <stdio.h>


enum selectOrDelete {enum_sel, enum_del};

class position
{
public:
    int blocknum;
    int offset;
};

extern BufferManager m;

class RecordManager
{
public:
    typedef Block*pointer;
    RecordManager();
    ~RecordManager();
    bool deletemap(TableNode &tablein);
    bool Select(TableNode &tableIn, std::vector<AttriValue>*AttrSelected, std::vector<Condition>*ConditionApplied);
    bool Insert(TableNode &tableIn, std::vector<AttriValue>*ValueToInsert);
    bool selectop(TableNode& tablein, std::vector<AttriValue>*AttrSelected, std::vector<Condition>*ConditionAppied);
    ///private
    std::string changekey(const std::string&keyin, int type);
    std::string getkey(char*record, int offset, int length);
    int Delete(TableNode &tableIn, std::vector<Condition>*ConditionApplied);
    bool ConditionSatisfied(TableNode &tableIn, char* recordBegin, std::vector<Condition>* ConditionApplied);
    void DeleteInBTree(TableNode &tableIn, char* attriValBegin);


    bool SelectRecordEachBlock(TableNode &tableIn, std::vector<AttriValue>*AttrSelected, std::vector<Condition>*ConditionApplied, pointer block, int rnum, int op);
    int GetRecordSize(TableNode &tableIn);
    int GetTypeSize(int type);
    bool ContentSatisfied(char* content,int type,Condition* condition);
    void PrintARecord(TableNode &tableIn, char* recordBegin, std::vector<AttriValue>* AttrSelected);
    void PrintContent(char * content, int type);
    std::string GetKeyString(std::vector<AttriValue>*ValueToInsert, int n);
    bool DeleteARecord(TableNode &tableIn, char* validBit);
    bool UpdateRecordNum(TableNode &tableIn, pointer block, int delete_amount);
    bool InsertInNullBlock(TableNode &tableIn, std::vector<AttriValue>*ValueToInsert);
    void UpdateBTree(TableNode &tableIn, std::string attrName, std::string attrValue, int blockOffset, int innerOffset);
 ///   int GetInnerOffset(int i, int recordSize, std::vector<AttriValue>*ValueToInsert, int j);
    std::string GetTableName(std::string tableName);
private:
    typedef std::map<std::string,std::queue<int> >Mymap;
    Mymap mymap;
};

#endif // RECORDMANAGE_H
