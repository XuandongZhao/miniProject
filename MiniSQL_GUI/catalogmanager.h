#pragma once
#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <string>
#include <list>
#include <iostream>
#include "bplus_tree.h"
#include "buffmanage.h"
#include "AttriValue.h"
#include <map>
#include <utility>
#include <vector>

extern BufferManager m;
class IndexNode
{
public:
    std::string  IndexName;
    bool valid;
    btree*tree;
    IndexNode():IndexName(""),valid(0),tree(nullptr){}

};

class TableNode
{
public:
    std::string TableName;
    std::list<AttriValue> AttributeList;
    std::vector<std::string> PrimaryKey;
    std::vector<std::string> Unique;
    //std::map<std::string, std::pair<btree*, bool>>bplustrees;
    std::map<std::string, IndexNode>bplustrees;
    int RecordNum;
    btree*gettree(const std::string&AttributeName)
    {
        if (bplustrees.find(AttributeName) != bplustrees.end())
        {
            return bplustrees[AttributeName].tree;
        }
        return nullptr;
    }
    btree*gettreebyname(const std::string&Indexname)
    {
        for (auto &i : bplustrees)
        {
            if (i.second.IndexName == Indexname&&i.second.valid)
            {
                return i.second.tree;
            }
        }
        return nullptr;
    }
    bool setIndexName(const std::string&Attributename,const std::string&Indexname)
    {
        if (bplustrees.find(Attributename) != bplustrees.end())
        {
            bplustrees[Attributename].IndexName = Indexname;
            bplustrees[Attributename].valid = 1;
            return true;
        }
        else {
            return false;
        }
    }
    bool setinvalid(const std::string&Attributename, const std::string&Indexname)
    {
        if (bplustrees.find(Attributename) != bplustrees.end())
        {
            bplustrees[Attributename].valid = 0;
            return true;
        }
        return false;
    }

    void inserttree(const std::string&AttributeName, btree* tree)
    {
        IndexNode a;
        a.IndexName = AttributeName;
        a.tree = tree;
        bplustrees[AttributeName] = a;
    }
    TableNode() :RecordNum(0) {}
    TableNode(std::string table_name, std::list<AttriValue> Attribute_list, int record_num) :
        TableName(table_name), AttributeList(Attribute_list), RecordNum(record_num) {

    }
};

class CatalogManager
{
private:
    std::list<TableNode> TableList;
public:
    CatalogManager();
    virtual ~CatalogManager();

    //1 for success, 0 for fail. -1 for not exist
    void ReadCatalog();
    void WriteCatalog();
    bool CreateTable(std::string table_name, std::list<AttriValue> Attributelist);
    bool CreateIndex(TableNode&a, std::string table_name, std::string attributename);//columns:which need index
    bool ifTableExist(std::string table_name);
    bool ifIndexExist(std::string index_name);
    int getRecordNum(std::string table_name);//return number of record
    bool deleteTable(std::string table_name);
    bool deleteIndex(std::string index_name);
    bool recordDelete(std::string table_name, int num);
    bool recordAdd(std::string table_name, int num);
    TableNode& getTableInfo(std::string table_name);
};

#endif // CATALOGMANAGER_H
