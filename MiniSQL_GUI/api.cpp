#include "stdafx.h"
#include "api.h"
using namespace std;
bool API::selectrecord(const std::string&tablename, std::vector<std::string>*selectinfo, vector<Condition>*condition)
{
    /*
    cout << "api debug" << endl;
    for (int i = 0; i < (*selectinfo).size(); i++)
    {
        cout << "select " << (*selectinfo)[i] << endl;
    }
    for (int i = 0; i < (*condition).size(); i++)
    {
        cout << "cond " << (*condition)[i].attriName<<' '<<(*condition)[i].value << endl;
    }*/

    TableNode&table = mc.getTableInfo(tablename);
    vector<AttriValue>attrsele;
    for (auto &i : table.AttributeList)
    {
        for (int j = 0; j < (*selectinfo).size(); ++j)
        {
            if ((*selectinfo)[j] == i.AtrributeName)
            {
                attrsele.push_back(i);
            }
        }
    }
    if ((*selectinfo).size() == 0)
    {
        for (auto &j : table.AttributeList)
        {
            (attrsele).push_back(j);
        }
    }
    return mr.selectop(table, &attrsele, condition);
    //return mr.Select(table, &attrsele, condition);
}
bool API::deleterecord(const std::string&tablename, vector<Condition>*condition)
{
    TableNode&table = mc.getTableInfo(tablename);
    vector<AttriValue>attrwithtree;
    for (auto &i : table.AttributeList)
    {
        if (i.isPrimary || i.isUnique)
        {
            for (int j = 0; j < (*condition).size(); ++j)
            {
                if (i.AtrributeName == (*condition)[j].attriName)
                {
                    attrwithtree.push_back(i);
                }
            }
        }
    }

    int state = mr.Delete(table,condition);
    if (state == 2)
    {
        return droptable(tablename);
    }
    else {
        if (state == 1)
        {
            mc.recordDelete(tablename, 1);
        }
        return state;
    }
}
bool API::createtable(const std::string&tablename, vector<AttriValue>*valuein)
{
    list<AttriValue>in;
    for (auto &i : *valuein)
    {
        in.push_back(i);
    }
    return mc.CreateTable(tablename, in);

}
bool API::droptable(const std::string&tablename)
{
    TableNode m = mc.getTableInfo(tablename);
    return mr.deletemap(m)&& mc.deleteTable(tablename);
}
bool API::createindex(const std::string&indexname, const std::string&tablename, const std::string&atrrubename)
{
    return mc.CreateIndex(mc.getTableInfo(tablename), indexname, atrrubename);
}
bool API::dropindex(const std::string&indexname)
{
    return mc.deleteIndex(indexname);
}
bool API::insertrecord(const std::string&tablename, vector<std::string>*info)
{
    TableNode a = mc.getTableInfo(tablename);
    vector<AttriValue>infoinsert;
    int tablesz = a.AttributeList.size();
    int loc = -1;
    for (auto &i : a.AttributeList)
    {
        loc++;
        infoinsert.push_back(i);
        if (i.isPrimary && (*info)[loc].size() == 0)
        {
            return false;
        }
        if (i.type == 0)
        {
            infoinsert[loc].intVal = atoi((*info)[loc].c_str());
            //cout << "Int insert" << infoinsert[loc].intVal << endl;
            //system("pause");
        }
        else if (i.type == 1)
        {
            infoinsert[loc].FloatVal = atof((*info)[loc].c_str());
            //cout << "Float insert" << infoinsert[loc].FloatVal << endl;
            //system("pause");
        }
        else {
            infoinsert[loc].strVal = (*info)[loc];
        }
    }

    if (mr.Insert(a, &infoinsert))
    {
        mc.recordAdd(tablename, 1);
        return true;
    }
    else {
        return false;
    }
}
