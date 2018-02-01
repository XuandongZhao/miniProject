#pragma once
#ifndef BUFFMANAGE_H
#define BUFFMANAGE_H

#include <string>
#include <utility>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "basicdata.h"


class BufferManager
{
private:
    const int MAXBLOCKNUM = 1024;
    struct Block* head;
    Block* tail;
    struct File* fileHead;
    int number;
    Block* readnewblock(std::string FileName, int offset, Block* tmpTail);
public:

    BufferManager();

    ~BufferManager();

    void flushoneblock(Block* bufferBlock);

    void flush();

    void deletebuff();

    Block* getblock(std::string FileName, int offset);

    bool isFull();

    std::pair<Block*, int> getnullblock(std::string filename);

    Block* createfile(std::string filename);

    void deleteBlock(std::string fileName, int offset);
    void deletefileblock(std::string filename);
};

#endif // BUFFMANAGE_H
