#include "stdafx.h"
#include "catalogmanager.h"
using namespace std;
CatalogManager::CatalogManager()
{
    ReadCatalog();
}

CatalogManager::~CatalogManager()
{
    WriteCatalog();
    for (auto &i : this->TableList)
    {
        for (auto &j : i.bplustrees)
        {
            delete j.second.tree;
        }
    }
}

std::string CreateIndexName(std::string table_name, std::string index_name)
{
    return table_name + "-" + index_name + "_index.txt";
}
std::string CreateConfigName(std::string table_name, std::string index_name)
{
    return table_name + "��" + index_name + "_config.txt";
}
std::string CreateTableName(std::string table_name)
{
    return table_name;
}
std::string CreateBareIndexName(std::string table_name, std::string index_name)
{
    return table_name + "-" + index_name;
}

void CatalogManager::ReadCatalog()
{
    //fstream logfile;
    std::string tmppath = path + "//catlog//TableLog.txt";
    ifstream fin(tmppath, ios::in);
    if (fin.is_open())
    {
        int tablesz;
        fin >> tablesz;
        for (int i = 0; i < tablesz; i++)
        {
            TableNode tablem;
            fin >> tablem.TableName;
            int attrsz;
            fin >> attrsz;
            for (int j = 0; j < attrsz; j++)
            {
                AttriValue attrm;
                fin >> attrm.isPrimary >> attrm.isUnique >> attrm.isNull;
                fin >> attrm.cntintable >> attrm.AtrributeName;
                fin >> attrm.length >> attrm.type;
                if (attrm.isPrimary || attrm.isUnique)
                {
                    std::string cpath = path + "//index//" + CreateIndexName(tablem.TableName, attrm.AtrributeName);
                    indexinfo my(cpath, changetype(attrm.type), attrm.length);
                    btree*tree = new btree(my, 1);
                    tablem.inserttree(attrm.AtrributeName, tree);
                }

                tablem.AttributeList.push_back(attrm);
            }
            int prisz;
            fin >> prisz;
            for (int j = 0; j < prisz; j++)
            {
                std::string prikey;
                fin >> prikey;
                tablem.PrimaryKey.push_back(prikey);
            }
            int unisz;
            fin >> unisz;
            for (int j = 0; j < unisz; j++)
            {
                std::string unikey;
                fin >> unikey;
                tablem.Unique.push_back(unikey);
            }
            int indexsize, isvalid;
            fin >> indexsize;
            string attname;
            string indexname;
            for (int i = 0; i < indexsize; i++)
            {
                fin >> attname;
                fin >> isvalid;
                if (isvalid)
                {
                    fin >> indexname;
                    tablem.setIndexName(attname, indexname);
                }
            }


            TableList.push_back(tablem);
        }
    }

}

void CatalogManager::WriteCatalog()
{
    std::string tmppath = path + "//catlog//TableLog.txt";
    ofstream fout(tmppath, ios::out);
    fout << TableList.size() << std::endl;//table cnt
    for (auto &i : TableList)//each table
    {
        fout << i.TableName << ' ';//name
        fout << i.AttributeList.size() << ' ';//attribute
        for (auto &j : i.AttributeList)
        {
            fout << j.isPrimary << ' ' << j.isUnique << ' ' << j.isNull << ' ';
            fout << j.cntintable << ' ';
            fout << j.AtrributeName << ' ';
            fout << j.length << ' ' << j.type << ' ';
        }
        fout << i.PrimaryKey.size() << ' ';
        for (int j = 0; j < i.PrimaryKey.size(); j++)
        {
            fout << i.PrimaryKey[j] << ' ';
        }
        fout << i.Unique.size() << ' ';
        for (int j = 0; j < i.Unique.size(); j++)
        {
            fout << i.Unique[j] << ' ';
        }
        //tree
        fout << i.bplustrees.size() << std::endl;
        for (auto &j : i.bplustrees)
        {
            fout << j.first << ' ';
            if (j.second.valid)
            {
                fout << 1 << ' ' << j.second.IndexName << std::endl;
            }
            else {
                fout << 0 << std::endl;
            }
        }
    }
}

bool CatalogManager::CreateTable(std::string table_name, list<AttriValue> AttributeList)
{

    std::string tpath = path + CreateTableName(table_name);
    ofstream tablefile(tpath, ios::in);

        std::string cpath = path + "//table//" + table_name + ".txt";
        Block*tmpblock = m.createfile(cpath);
        *reinterpret_cast<int*>(tmpblock->cblock) = 0;
        tmpblock->isdirty = 1;
        TableNode node(table_name, AttributeList, 0);
        for (auto &i : AttributeList)
        {
            if (i.isPrimary || i.isUnique)
            {

                std::string cpath = path + "//index//" + CreateIndexName(table_name, i.AtrributeName);
                indexinfo my(cpath, changetype(i.type), i.length);
                btree*tree = new btree(my, 0);
                node.inserttree(i.AtrributeName, tree);
                if (i.isPrimary)
                {
                    node.setIndexName(i.AtrributeName, i.AtrributeName);
                }
            }
            if (i.isPrimary)
            {
                node.PrimaryKey.push_back(i.AtrributeName);
            }
            if (i.isUnique)
            {
                node.Unique.push_back(i.AtrributeName);
            }
        }


        this->TableList.push_back(node);
        return true;
}

bool CatalogManager::CreateIndex(TableNode&tablein, std::string indexname, std::string attributename)
{
    if (tablein.setIndexName(attributename, indexname))
    {
        return true;
    }
    return false;
}

bool CatalogManager::ifTableExist(std::string table_name)
{
    list<TableNode>::iterator tite;
    for (tite = this->TableList.begin(); tite != this->TableList.end(); ++tite)
    {
        if (tite->TableName == table_name)
            return true;
    }
    return false;
}

bool CatalogManager::ifIndexExist(std::string index_name)
{
    for (auto &i : TableList)
    {
        for (auto&j : i.bplustrees)
        {
            if (j.second.IndexName == index_name)
            {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

TableNode& CatalogManager::getTableInfo(std::string table_name)
{
    list<TableNode>::iterator tite;
    for (tite = this->TableList.begin(); tite != this->TableList.end(); ++tite) {
        if (tite->TableName == table_name)
            return *tite;
        else {

        }
    }
    return *tite;
}


int CatalogManager::getRecordNum(std::string tablename)
{
    list<TableNode>::iterator tite;
    for (tite = this->TableList.begin(); tite != this->TableList.end(); ++tite)
    {
        if (tite->TableName == tablename)
        {
            return tite->RecordNum;
        }
    }
    return -1;
}

bool CatalogManager::deleteIndex(std::string indexname)
{
    for (auto&i : TableList)
    {
        for (auto &j : i.bplustrees)
        {
            if (j.second.IndexName==indexname&&j.second.valid)
            {
                for (int k = 0; k < i.PrimaryKey.size(); k++)
                {
                    if (i.PrimaryKey[k] == j.first)
                    {
                        return false;
                    }
                }
                j.second.IndexName = "";
                j.second.valid = 0;
                return true;
            }
        }
    }
    return false;
}


bool CatalogManager::deleteTable(std::string tablename)
{
    list<TableNode>::iterator tite;
    for (tite = this->TableList.begin(); tite != this->TableList.end();)
    {
        if (tite->TableName == tablename)
        {

            for (auto &j : tite->bplustrees)
            {
                std::string tpath = path + "//index//" + CreateIndexName(tablename, j.first);
                m.deletefileblock(tpath);
                delete j.second.tree;
            }
            std::string cpath = path + "//table//" + CreateTableName(tablename) + ".txt";
            m.deletefileblock(cpath);
            tite = this->TableList.erase(tite++);
        }
        else
        {
            ++tite;
        }
    }
    return true;
}

bool CatalogManager::recordDelete(std::string tablename, int num)
{
    list<TableNode>::iterator tite;
    for (tite = this->TableList.begin(); tite != this->TableList.end(); ++tite)
    {
        if (tite->TableName == tablename)
        {
            tite->RecordNum -= num;
            return true;
        }
    }
    return -1;//not found;
}

bool CatalogManager::recordAdd(std::string tablename, int num)
{
    list<TableNode>::iterator tite;
    for (tite = this->TableList.begin(); tite != this->TableList.end(); ++tite)
    {
        if (tite->TableName == tablename)
        {
            tite->RecordNum += num;
            return true;
        }
    }
    return -1;//not found;
}

std::string isTrue(bool x) {
    if (x)
        return "true";
    else return "false";
}
