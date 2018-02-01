#include "stdafx.h"
#include "recordmanage.h"
using namespace std;
const int valid = 1;
const int invalid = 0;

bool RecordManager::deletemap(TableNode&tablein)
{
    for (auto i = mymap.begin(); i != mymap.end();)
    {
        if (i->first == tablein.TableName)
        {
            mymap.erase(i++);
            return true;
        }
        else {
            i++;
        }
    }
    return false;
}

std::string RecordManager::getkey(char* record, int offset, int length)
{
    char *buf = new char[length + 1];
    for (int i = 0; i < length; i++)
    {
        buf[i] = record[i];
    }
    buf[length] = '\0';
    string ans(buf);
    delete[] buf;
    return ans;
}
std::string RecordManager::changekey(const std::string&keyin, int type)
{
    char buf[5] = { 0 };
    string ans;
    if (type == 0)
    {
        int val = stoi(keyin);
        *reinterpret_cast<int*>(buf) = val;
        ans.resize(4);
        ans[0] = buf[0];
        ans[1] = buf[1];
        ans[2] = buf[2];
        ans[3] = buf[3];
    }
    else if (type == 1)
    {
        float val = stof(keyin);
        *reinterpret_cast<float*>(buf) = val;
        ans.resize(4);
        ans[0] = buf[0];
        ans[1] = buf[1];
        ans[2] = buf[2];
        ans[3] = buf[3];
    }
    else {
        ans = keyin;
    }
    return ans;
}
bool RecordManager::selectop(TableNode& tablein, vector<AttriValue>*AttrSelected, vector<Condition>*ConditionAppied)
{
    vector<Condition>bytree;
    vector<Condition>byforce;
    map<std::string, int>checktree;
    map<pair<int, int>, int>checkvector;
    for (auto &i : tablein.AttributeList)
    {
        if (i.isPrimary || i.isUnique)
        {
            if(tablein.gettreebyname(i.AtrributeName)!=nullptr)
                checktree[i.AtrributeName] = 1;
        }
        for (auto &j : (*ConditionAppied))
        {
            if (i.AtrributeName == j.attriName)
            {
                //cout << "RRRRR:" << j.value << endl;
                j.value = changekey(j.value, i.type);
                //cout << "TTTTT:" << j.value << endl;
            }
        }
    }

    for (int i = 0; i < (*ConditionAppied).size(); ++i)
    {
        if ((*ConditionAppied)[i].OP == (*ConditionAppied)[i].OPERATOR_NOT_EQUAL)
        {
            byforce.push_back((*(ConditionAppied))[i]);
        }
        else {
            if (checktree.find((*ConditionAppied)[i].attriName) != checktree.end())
            {
                bytree.push_back((*ConditionAppied)[i]);
            }
            else {
                byforce.push_back((*ConditionAppied)[i]);
            }
        }
    }

    vector<pair<int, int>>ans, tmp, res;

    if ((*ConditionAppied).size() == 0)
    {
        btree* tree = tablein.gettree(tablein.PrimaryKey[0]);
        res = tree->searchall();
        std::string fileTableName = GetTableName(tablein.TableName);
        int recordSize = GetRecordSize(tablein);

        for (int i = 0; i < res.size(); i++)
        {
            Block*tmpb = m.getblock(fileTableName, res[i].first);
            char *record = tmpb->cblock + 4 + (4 + recordSize)*res[i].second;
            PrintARecord(tablein, record + 4, AttrSelected);
        }
        return true;
    }
    else {
        if (bytree.empty())
        {
            return Select(tablein, AttrSelected, ConditionAppied);
        }
        for (int i = 0; i < bytree.size(); i++)
        {
            tmp.clear();
            btree*tmptree = tablein.gettree(bytree[i].attriName);
            if (bytree[i].OP == bytree[i].OPERATOR_EQUAL)
            {
                tmp.push_back(tmptree->searchequal(bytree[i].value));
            }
            else if (bytree[i].OP == bytree[i].OPERATOR_LESS_EQUAL)//<=
            {
                tmp = tmptree->searchlessequalthan(bytree[i].value);
            }
            else if (bytree[i].OP == bytree[i].OPERATOR_LST)//<
            {
                tmp = tmptree->searchlessthan(bytree[i].value);
            }
            else if (bytree[i].OP == bytree[i].OPERATOR_MORE_EQUAL)//>=
            {
                tmp = tmptree->searchbiggerequalthan(bytree[i].value);
            }
            else if (bytree[i].OP == bytree[i].OPERATOR_MOT)//>
            {
                tmp = tmptree->searchbiggerthan(bytree[i].value);
            }
            else {
                std::cout << "ERROR" << std::endl;
            }
            //merge
            if (i == 0)
            {
                ans = tmp;
            }
            else {
                checkvector.clear();
                for (int j = 0; j < ans.size(); j++)
                {
                    checkvector[ans[j]] = 1;
                }
                ans.clear();
                for (int j = 0; j < tmp.size(); j++)
                {
                    if (checkvector.find(tmp[j]) != checkvector.end())
                    {
                        ans.push_back(tmp[j]);
                    }
                }
            }
        }
        //brute force
        std::string fileTableName = GetTableName(tablein.TableName);
        int recordSize = GetRecordSize(tablein);
        vector<int>findloc;
        vector<int>typevector;
        vector<int>keylength;
        for (int i = 0; i < byforce.size(); i++)
        {
            int loc = 0;
            for (auto &j : tablein.AttributeList)
            {
                if (j.AtrributeName == byforce[i].attriName)
                {
                    findloc.push_back(loc);
                    typevector.push_back(j.type);
                    keylength.push_back(j.length);
                    break;
                }
                else {
                    loc += j.length;
                }
            }
        }

        for (int i = 0; i < ans.size(); i++)
        {
            if (ans[i].first == -1 || ans[i].second == -1)
            {
                continue;
            }
            Block*tblock = m.getblock(fileTableName, ans[i].first);
            char *record = tblock->cblock + 4 + (ans[i].second)*(4 + recordSize);
            if (*reinterpret_cast<int*>(record) == invalid)
            {
                std::cerr << "Error in Select" << std::endl;
                exit(0);
            }
            record += 4;//skip
                        //cout << "IIIIIII" << *reinterpret_cast<float*>(record) << endl;
                        //system("pause");
            bool f = 1;
            for (int j = 0; j < byforce.size(); j++)
            {
                std::string subkey;
                char buf[6];
                if (typevector[j] == 0)//int
                {
                    int val = *reinterpret_cast<int*>(record + findloc[j]);
                    if (byforce[j].check(val))
                    {
                        continue;
                    }
                    else {
                        f = 0; break;
                    }
                }
                else if (typevector[j] == 1)//float
                {
                    float val = *reinterpret_cast<float*>(record + findloc[j]);
                    if (byforce[j].check(val))
                    {
                        continue;
                    }
                    else {
                        f = 0; break;
                    }
                }
                else
                {
                    std::string tmpkey = getkey(record, findloc[j], keylength[j]);
                    if (byforce[j].check(tmpkey))
                    {
                        continue;
                    }
                    else {
                        f = 0; break;
                    }
                }
            }
            if (f)
            {
                res.push_back(ans[i]);
            }
        }
        for (int i = 0; i < res.size(); i++)
        {
            Block*tmpb = m.getblock(fileTableName, res[i].first);
            char *record = tmpb->cblock + 4 + (4 + recordSize)*res[i].second;
            PrintARecord(tablein, record + 4, AttrSelected);
        }
        return true;
    }
}
std::string RecordManager::GetKeyString(vector<AttriValue>*ValueToInsert, int n)
{
    std::stringstream ss;
    std::string str;
    char buf[500];
    memset(buf, 0, sizeof(buf));
    fk f;
    switch ((*ValueToInsert)[n].type)
    {
    case 0:
        *reinterpret_cast<int*>(buf) = (*ValueToInsert)[n].intVal;
        str.resize(4);
        str[0] = buf[0];
        str[1] = buf[1];
        str[2] = buf[2];
        str[3] = buf[3];
        /// str = ((*ValueToInsert)[n].intVal),);
        break;
    case 1:
        *reinterpret_cast<float*>(buf) = (*ValueToInsert)[n].FloatVal;
        //ss << (*ValueToInsert)[n].FloatVal;
        str.resize(4);
        str[0] = buf[0];
        str[1] = buf[1];
        str[2] = buf[2];
        str[3] = buf[3];
        ///str = (*ValueToInsert)[n].FloatVal;
        break;
    case 2:
        str = (*ValueToInsert)[n].strVal;
        break;
    default:
        cout << "Unknown data type" << endl;
        exit(0);
    }

    return str;
}


RecordManager::RecordManager()
{
    std::string cpath = path + "//recordManage//notFullBlocksList.txt";
    ifstream fin(cpath, ios::in);
    std::string filename;
    int tmp_index;
    int tmp_num;
    //  cout << "recordManager constructor" << endl;
    while (!fin.eof()) {
        fin >> filename;
        fin >> tmp_num;
        for (int i = 0; i<tmp_num; i++) {
            fin >> tmp_index;
            mymap[filename].push(tmp_index);
        }
    }
    //  cout << "recordManager constructed" << endl;
}

RecordManager::~RecordManager()
{
    std::string cpath = path + "//recordManage//notFullBlocksList.txt";
    ofstream fout(cpath, ios::out);
    for (auto i = mymap.begin(); i != mymap.end(); i++) {
        fout << (*i).first << ' ' << (*i).second.size() << ' ';
        for (int j = 0; j<(*i).second.size(); j++) {
            int tmp_index = (*i).second.front();
            fout << tmp_index << ' ';
            (*i).second.pop();
        }
    }
}

int RecordManager::Delete(TableNode &tableIn, vector<Condition>*ConditionApplied)
{
    if (ConditionApplied == NULL)
    {
        return 2; ///ɾ�������������
    }

    string fileTableName = GetTableName(tableIn.TableName);
    pointer FileHead = m.getblock(fileTableName, 0);
    int totalRecordNum = *reinterpret_cast<int*>(FileHead->cblock);
    int offset = 1;
    pointer block = m.getblock(fileTableName, offset);
    while (totalRecordNum>0) {
        int RecordNumEachBlock = *reinterpret_cast<int*>(block->cblock);///��ͷ�������׿���Ϣ����ɾ����ʱ���޸�
        totalRecordNum -= RecordNumEachBlock;
        /// while (RecordNumEachBlock>0){
        SelectRecordEachBlock(tableIn, NULL, ConditionApplied, block, RecordNumEachBlock, enum_del);
        /// }
    }
    return 1;
}


bool RecordManager::Insert(TableNode &tableIn, vector<AttriValue>*ValueToInsert)
{
    btree*bt;

    //cout << "********************test valueToInsert.size: " << (*ValueToInsert).size() << endl;
    /*
    for (int i = 0; i < (*ValueToInsert).size(); i++)
    {
        cout << i << "***" << endl;
        cout << (*ValueToInsert)[i].AtrributeName << "***" << endl;
        cout << (*ValueToInsert)[i].isPrimary << "***" << endl;
    }*/

    for (int i = 0; i<(*ValueToInsert).size(); i++) {
        if ((*ValueToInsert)[i].isPrimary) {
            bt = tableIn.gettree((*ValueToInsert)[i].AtrributeName);
            string pKey;

            pKey = GetKeyString(ValueToInsert, i);
            pair<int, int>Pair = bt->searchequal(pKey);
            if (Pair.first != -1) {
                cout << "Duplicate entry for key 'PRIMARY'"<< endl;
                return false;
            }
        }
        else if ((*ValueToInsert)[i].isUnique) {
            bt = tableIn.gettree((*ValueToInsert)[i].AtrributeName);
            string uKey;
            uKey = GetKeyString(ValueToInsert, i);
            pair<int, int>Pair = bt->searchequal(uKey);
            if (Pair.first != -1) {
                cout << "Duplicate entry for key unique" << endl;
                return false;
            }
        }
    }

    int blockOffset;
    int recordSize = GetRecordSize(tableIn);
    int maxRecordABlock = (BLOCK_SIZE - 4) / (recordSize + 4);

    string fname = tableIn.TableName;
    string fileTableName = GetTableName(tableIn.TableName);
    while (mymap[fname].size()>0) {
        //cout << "map��δ������Ŀ��" << mymap[fname].size() << endl;
        blockOffset = mymap[fname].front();
        mymap[fname].pop();

        pointer block = m.getblock(fileTableName, blockOffset);
        int rNumThisBlock = *reinterpret_cast<int*>(block->cblock) += 1;

        int validBit;
        for (int i = 0; (4 + recordSize)*i<BLOCK_SIZE - 4; i++) {
            char *validBitAddr = block->cblock + 4 + (4 + recordSize)*i;///+numbit + (validbit+recordSize)*i
            validBit = *reinterpret_cast<int*>(validBitAddr);
            if (validBit != valid) {
                //cout << "PPPPPP" << endl;

                *reinterpret_cast<int*>(validBitAddr) = valid;
                char* attriAddress = validBitAddr + 4; ///+4 to skip the valid bit
                for (int j = 0; j<(*ValueToInsert).size(); j++) {
                    string valStr = GetKeyString(ValueToInsert, j);
                    if ((*ValueToInsert)[j].type == 2)
                    {
                        memcpy(attriAddress, valStr.c_str(), (*ValueToInsert)[j].length);
                    }
                    else if ((*ValueToInsert)[j].type == 0)
                    {
                        *reinterpret_cast<int*>(attriAddress) = (*ValueToInsert)[j].intVal;
                    }
                    else {
                        *reinterpret_cast<float*>(attriAddress) = (*ValueToInsert)[j].FloatVal;
                    }

                    if ((*ValueToInsert)[j].isPrimary || (*ValueToInsert)[j].isUnique) {
                        ///int innerOffset = GetInnerOffset(i,recordSize,ValueToInsert,j);
                        string update_attr_name = (*ValueToInsert)[j].AtrributeName;
                        string update_attr_value = GetKeyString(ValueToInsert, j);
                        UpdateBTree(tableIn, update_attr_name, update_attr_value, blockOffset, i);
                    }
                    attriAddress += (*ValueToInsert)[j].length;
                }
                ///update total record num in block 0
                pointer firstBlock = m.getblock(fileTableName, 0);
                *reinterpret_cast<int*>(firstBlock->cblock) += 1;
                break;
            }
        }
        block->isdirty = 1;
        if (rNumThisBlock < maxRecordABlock) {
            mymap[fname].push(blockOffset);
        }
        //cout << "Insert Done: Insert in an unfilled block" << endl;
        return true;
    }


    InsertInNullBlock(tableIn, ValueToInsert);

    return true;
}

/***
int RecordManager::GetInnerOffset(int i, int recordSize, vector<AttriValue>*ValueToInsert, int j)
{
int temp = 0;
for (int k=0; k<j; k++){
temp += (*ValueToInsert)[k].length;
}
return (4+(4+recordSize)*i+temp);
}
***/

void RecordManager::UpdateBTree(TableNode &tableIn, string attrName, string attrValue, int blockOffset, int innerOffset)
{
    btree *bt;
    //cout << "In updateBtree********************" << endl;
    bt = tableIn.gettree(attrName);
    bt->insert(attrValue, blockOffset, innerOffset);
}

bool RecordManager::InsertInNullBlock(TableNode &tableIn, vector<AttriValue>*ValueToInsert)
{
    string fileTableName = GetTableName(tableIn.TableName);
    pair<pointer, int>Pair = m.getnullblock(fileTableName);
    pointer block = Pair.first;
    memset(block->cblock, 0, 4096);
    int blockOffset = Pair.second;
    ///��Ҫȷ�Ϸ��ؿ��ǿգ�����
    *reinterpret_cast<int*>(block->cblock) = 1;

    /// int validBit;

    char *validBitAddr = block->cblock + 4;


    *reinterpret_cast<int*>(validBitAddr) = valid;
    char* attriAddress = validBitAddr + 4; ///+4 to skip the valid bit
    for (int j = 0; j<(*ValueToInsert).size(); j++) {
        string valStr = GetKeyString(ValueToInsert, j);
        //cout << "NULL: " << valStr << endl;
        if ((*ValueToInsert)[j].type == 2)
        {
            memcpy(attriAddress, valStr.c_str(), (*ValueToInsert)[j].length);
        }
        else if ((*ValueToInsert)[j].type == 0)
        {
            *reinterpret_cast<int*>(attriAddress) = (*ValueToInsert)[j].intVal;
        }
        else {
            *reinterpret_cast<float*>(attriAddress) = (*ValueToInsert)[j].FloatVal;
        }

        if ((*ValueToInsert)[j].isPrimary || (*ValueToInsert)[j].isUnique) {
            /// int innerOffset = GetInnerOffset(0,999/***whatever***/,ValueToInsert,j);
            string update_attr_name = (*ValueToInsert)[j].AtrributeName;
            string update_attr_value = GetKeyString(ValueToInsert, j);
            UpdateBTree(tableIn, update_attr_name, update_attr_value, blockOffset, 0);
        }
        attriAddress += (*ValueToInsert)[j].length;
    }
    block->isdirty = 1;
    ///update total record num in block 0 in the file
    pointer firstBlock = m.getblock(fileTableName, 0);
    *reinterpret_cast<int*>(firstBlock->cblock) += 1;

    //cout << "Insert Done: Insert in a new block" << endl;

    // }
    mymap[tableIn.TableName].push(blockOffset);
    return true;
}

bool RecordManager::Select(TableNode &tableIn, vector<AttriValue>*AttrSelected, vector<Condition>*ConditionApplied)
{

    /*
    * Attrselect->���� push vector
    *
    * btree search vector ans
    *
    * for each ans
    *
    */

    ///selectOrDelete op = enum_sel;
    string fileTableName = GetTableName(tableIn.TableName);
    pointer FileHead = m.getblock(fileTableName, 0);
    int totalRecordNum = *reinterpret_cast<int*>(FileHead->cblock);
    int offset = 1;
    pointer block = m.getblock(fileTableName, offset);
    while (totalRecordNum>0) {
        int RecordNumEachBlock = *reinterpret_cast<int*>(block->cblock);
        totalRecordNum -= RecordNumEachBlock;
        ///   while (RecordNumEachBlock>0){
        SelectRecordEachBlock(tableIn, AttrSelected, ConditionApplied, block, RecordNumEachBlock, enum_sel);
        ///  }
        block = m.getblock(fileTableName, ++offset);
    }
    return true;
}

bool RecordManager::DeleteARecord(TableNode &tableIn, char* validBit)
{
    if ((*reinterpret_cast<int*>(validBit)) == valid) {
        *reinterpret_cast<int*>(validBit) = invalid;
        return true;
    }
    else if ((*reinterpret_cast<int*>(validBit)) == invalid) {
        cout << "Error: Not exits the record to be deleted" << endl;
        exit(0);
    }
    cout << "valid bit error in DeleteARecord" << endl;
    exit(0);
}

bool RecordManager::SelectRecordEachBlock(TableNode &tableIn, vector<AttriValue>*AttrSelected, vector<Condition>*ConditionApplied, pointer block, int rnum, int op)
{
    if (block == NULL) {
        return false;
    }
    int delete_amount = 0;
    int recordSize = GetRecordSize(tableIn);

    char* recordBegin = block->cblock + 4; ///skip rnum
    int i = 0;
    while (i<rnum)
    { ///???????????????????????????????????????????????
        int recordValid = *reinterpret_cast<int*>(recordBegin);
        recordBegin += 4;  ///skip valid bit
        if (valid == recordValid) {
            i++;
            if (ConditionSatisfied(tableIn, recordBegin, ConditionApplied)) {
                switch (op)
                {
                case enum_sel:
                    PrintARecord(tableIn, recordBegin, AttrSelected);
                    break;
                case enum_del:
                    DeleteARecord(tableIn, recordBegin - 4);
                    DeleteInBTree(tableIn, recordBegin);
                    delete_amount++;
                    break;
                default:
                    cout << "enum value error" << endl;
                    exit(0);
                }
            }
        }
        recordBegin += recordSize;
    }

    if (op == enum_del) UpdateRecordNum(tableIn, block, delete_amount);
    return true;
}

void RecordManager::DeleteInBTree(TableNode &tableIn, char *attriValBegin)
{
    btree *bt;
    /***   for (int i=0; i<(*AttriSelected).size(); i++){
    if ((*AttriSelected)[i].isPrimary||(*AttriSelected)[i].isUnique){
    bt = tableIn.gettree((*AttriSelected)[i].AtrributeName);
    string key = GetKeyString(AttriSelected,i);
    bt->deleteonerecord(key);
    }
    }***/
    char content[4100];
    for (auto i = tableIn.AttributeList.begin(); i != tableIn.AttributeList.end(); i++) {
        if ((*i).isUnique || (*i).isPrimary) {
            bt = tableIn.gettree((*i).AtrributeName);
            //char content[(*i).length];
            memset(content, 0, (*i).length);
            memcpy(content, attriValBegin, (*i).length);
            ///cout << "delete in btree: " << content << endl; /*�鿴ɾ��������ֵ*/
            bt->deleteonerecord(content);
        }
        attriValBegin += (*i).length;
    }
}

bool RecordManager::UpdateRecordNum(TableNode &tableIn, pointer block, int delete_amount)
{
    string fileTableName = GetTableName(tableIn.TableName);
    pointer fileHead = m.getblock(fileTableName, 0);
    if ((*reinterpret_cast<int*>(block->cblock) -= delete_amount)<0) {
        return false;
    }
    if ((*reinterpret_cast<int*>(fileHead->cblock) -= delete_amount)<0) {
        return false;
    }
    return true;
}
/**
* return the length of a record
* @param tableIn
* @return
*/
int RecordManager::GetRecordSize(TableNode &tableIn)
{
    int size = 0;

    for (auto i = tableIn.AttributeList.begin(); i != tableIn.AttributeList.end(); i++)
    {
        size += (*i).length;
    }

    return size;
}

bool RecordManager::ConditionSatisfied(TableNode &tableIn, char* recordBegin, vector<Condition>* ConditionApplied)
{
    if (NULL == ConditionApplied) {
        return true;
    }

    int type;
    string attributeName;
    int typeSize;
    char content[4100];
    for (int i = 0; i<(*ConditionApplied).size(); i++) {
        char *contentAddress = recordBegin;
        for (auto j = tableIn.AttributeList.begin(); j != tableIn.AttributeList.end(); j++) {
            type = (*j).type;
            attributeName = (*j).AtrributeName;
            typeSize = (*j).length;
            //char content[typeSize];

            if ((*ConditionApplied)[i].attriName == attributeName) {
                memset(content, 0, 4100);
                memcpy(content, contentAddress, typeSize);
                if (!ContentSatisfied(content, type, &(*ConditionApplied)[i])) {
                    return false;
                }
            }
            contentAddress += typeSize;
        }
    }
    return true;
}

int RecordManager::GetTypeSize(int type)
{
    if (type == 1) {
        return sizeof(float);
    }
    else if (type == 0) {
        return sizeof(int);
    }
    else if (type == 2) {
        return (int)(sizeof(char)*type);
    }
}

bool RecordManager::ContentSatisfied(char* content, int type, Condition* condition)//////////�ĳ���string
{
    if (type == 0) {
        int temp = *((int*)content);
        return condition->check(temp);
    }
    else if (type == 1) {
        float temp = *((float*)content);
        return condition->check(temp);
    }
    else if (type == 2) {
        return condition->check(content);
    }
}

void RecordManager::PrintARecord(TableNode &tableIn, char* recordBegin, vector<AttriValue>* AttrSelected)
{
    int type;
    string attriName;
    int typeSize;
    ///char content[255];
    char content[4100];
    char *contentBegin = recordBegin;

    ///cout<< "test .size()" << (*AttrSelected).size() << endl;
    for (auto i = tableIn.AttributeList.begin(); i != tableIn.AttributeList.end(); i++) {
        type = (*i).type;
        typeSize = (*i).length;///GetTypeSize(type);
        //char content[typeSize];
        memset(content, 0, 4100);
        memcpy(content, contentBegin, typeSize);

        for (int j = 0; j<(*AttrSelected).size(); j++) {
            if ((*AttrSelected)[j].AtrributeName == (*i).AtrributeName) {
                PrintContent(content, type);
                break;
            }
        }
        contentBegin += typeSize;
    }
    cout << endl;
}

void RecordManager::PrintContent(char * content, int type)
{
    stringstream ss;
    ss << content;

    if (type == 0) {
        //cout << "int disp" << endl;
        cout <<((int) (*reinterpret_cast<int*>(content))) << '\t';
    }
    else if (type == 1) {
        cout << ((float)(*reinterpret_cast<float*>(content))) << '\t';
    }
    else if (type == 2) {
        string temp;
        ss >> temp;
        if (temp.length() <= 7) {
            printf("%s\t\t", temp.c_str());
        }
        else {
            printf("%s\t", temp.c_str());
        }
    }
}

string RecordManager::GetTableName(string tableName)
{
    return path + "//table//" + tableName + ".txt";
}
