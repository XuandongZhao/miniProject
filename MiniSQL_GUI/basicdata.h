#pragma once
#ifndef BASICDATA_H
#define BASICDATA_H

#include <string>
#include "buffmanage.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <queue>
#include <list>
#include <iterator>
#include <utility>
#include <fstream>
#include <sstream>
const int BLOCK_SIZE = 4096;//total blocks

enum { leafoff = 20, nonleafoff = 20 };
enum type { Index, record, uncertain };
enum keytype { isint, isfloat, ischar };
typedef enum type fileType;
typedef enum type blocktype;

keytype changetype(int type);


union fk {
    unsigned int intv;
    float fv;
};

class base {
public:
    int type;
    int keylen;
    virtual std::string tostring() = 0;
};
class intdata :public base {
public:
    int data;
    char buf[6];
    virtual std::string tostring() override;

};
class floatdata :public base {
public:
    float data;
    union {
        float data;
        unsigned int fint;
    }b;
    char buf[6];
    virtual std::string tostring()override;

};
class stringdata :public base {
public:
    std::string data;
    virtual std::string tostring()override;
};

struct Block {
    std::string filename;//block's filename in buff
    int type;//0 int 1 float 2 char 3 unknown
    int blockoffset;//the location of block in filename
    char*cblock;//the massage in Block
    bool isdirty;//if it is changed or not
    bool pin;
    int charnum;
    Block*next;
    Block() :filename(""), type(3), blockoffset(0), isdirty(0), charnum(0), next(nullptr),pin(false)
    {
        cblock = new char[BLOCK_SIZE];
    }
    Block(const std::string& x, int offset) :filename(x), blockoffset(offset), type(3), isdirty(0), charnum(0), next(nullptr),pin(false)
    {
        cblock = new char[BLOCK_SIZE];
    }
    void setpin()
    {
        pin = true;
    }
    inline bool isnull()
    {
        return !charnum;
    }
    inline bool isleaf()
    {
        return *reinterpret_cast<int*>(cblock);
    }
    inline int getsize()
    {
        int tp = *reinterpret_cast<int*>(cblock + 4);
        if (!isleaf())
        {
            tp--;
        }
        return tp;
    }
    inline void update_charnum(int blocksize)//only record
    {
        int off = 0;
        if (!isleaf())
        {
            off = 4;
        }
        off += blocksize*getsize();
        charnum = off;
    }
    inline int getfather()
    {
        return *reinterpret_cast<int*>(cblock + 8);
    }
    inline void setfather(int x)
    {
        isdirty = 1;
        *reinterpret_cast<int*>(cblock + 8) = x;
    }
    inline int getleft()
    {
        return *reinterpret_cast<int*>(cblock + 12);
    }
    inline void setleft(int x)
    {
        isdirty = 1;
        *reinterpret_cast<int*>(cblock + 12) = x;
    }
    inline int getright()
    {
        return *reinterpret_cast<int*>(cblock + 16);
    }
    inline void setright(int x)
    {
        isdirty = 1;
        *reinterpret_cast<int*>(cblock + 16) = x;
    }
    inline void setleaf(int isleaf)
    {
        isdirty = 1;
        *reinterpret_cast<int*>(cblock) = isleaf;
    }
    inline std::string getkey(int off, int blocksz, int keysize, int pos,int type)
    {
        char *buf = new char[blocksz + 10];
        memcpy(buf, cblock + off + (blocksz)*pos + blocksz - keysize, keysize);
        buf[keysize] = '\0';
        if (type == 2)
        {
            delete buf;
            return std::string(buf);
        }
        else {
            std::string res;
            res.resize(4);
            res[0] = buf[0];
            res[1] = buf[1];
            res[2] = buf[2];
            res[3] = buf[3];
            delete buf;
            return res;
        }
    }
    inline void setkey(int off, int blocksz, int keysize, int pos, const std::string& rep,int type)
    {
        isdirty = 1;
        if (type == 2)
        {
            memcpy(cblock + off + pos*blocksz + blocksz - keysize, rep.c_str(), keysize);
        }
        else {
            if (rep.size() != 4)
            {
                assert("Key size error in B tree\n");
            }
            char buf[6];
            buf[0] = rep[0];
            buf[1] = rep[1];
            buf[2] = rep[2];
            buf[3] = rep[3];
            buf[4] = '\0';
            memcpy(cblock + off + pos*blocksz + blocksz - keysize,buf , 4);

        }
    }
    inline int getpointer(int cnt, int blocksz)
    {
        return *reinterpret_cast<int*>(cblock + nonleafoff + cnt*blocksz);
    }
    void setBlockLocation(std::string x, int offset)
    {
        filename = x;
        blockoffset = offset;
        isdirty = 1;
    }
    void setblockvalue(char* value, int cnt)//I will promise that value is the complete information
    {
        type = *reinterpret_cast<int*>(value);
        charnum = cnt;
        memcpy(cblock, value, sizeof(char)*charnum);
        isdirty = true;
    }
    int get_record()
    {
        std::string tmp = cblock;
        return *reinterpret_cast<int*>(cblock + 4);
    }
    void update_record(int cnt)
    {
        *reinterpret_cast<int*>(cblock + 4) = cnt;
        isdirty = 1;
    }
    void set_add_one_record()
    {
        int tmp = get_record();
        update_record(tmp + 1);
    }
    void set_sub_one_record()
    {
        int tmp = get_record();
        update_record(tmp - 1);
    }


};

typedef Block* pointer;
class File
{
public:
    std::vector<int> emptyBlocks;
    int lastEmptyBlock;
    std::string fileName;
    fileType type;
    File* next;

    File()
    {
        lastEmptyBlock = 0;
        type = uncertain;
        next = NULL;
        fileName = "";
    }
    File(fileType Type, std::string name)
    {
        type = Type;
        fileName = name;
        lastEmptyBlock = 0;
        next = NULL;
    }
    //~File() { ; }
};

typedef File*filePtr;
extern const std::string path;

#endif // BASICDATA_H
