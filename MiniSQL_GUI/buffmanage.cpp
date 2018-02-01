#include "stdafx.h"
#include "buffmanage.h"
using namespace std;
BufferManager::BufferManager()
{
    //cout << "gouzao" << endl;
    cout << "enter buffer" << endl;
    head = new Block;
    head->next = NULL;
    tail = new Block;
    tail->next = head;
    fileHead = new File;
    fileHead->next = NULL;
    number = 0;
    std::string tpath = path + "//buffmanage//EmptyBlockRecord.txt";
    filePtr tmpFile = fileHead;
    FILE *fp;
    if (fp = fopen(tpath.c_str(), "rb+"))
    {
        char readChar;
        std::string totalRecord = "";
        vector<std::string> splitRecord;
        readChar = fgetc(fp);
        while (readChar != '$')
        {
            totalRecord += readChar;
            readChar = fgetc(fp);
        }
        std::string tmpRecord = "";
        for (int i = 0; i<totalRecord.size(); i++)
        {
            if (totalRecord[i] == ';')
            {
                splitRecord.push_back(tmpRecord);
                tmpRecord = "";
            }
            else tmpRecord += totalRecord[i];
        }
        for (auto &s : splitRecord)
        {
            tmpFile->next = new File;
            int tag = 0;
            std::string tmpRecord = "";
            for (int i = 0; i<s.size(); i++)
            {
                if (s[i] == '@')
                {
                    tmpFile->next->fileName = tmpRecord;
                    tmpRecord = "";
                    continue;
                }
                if (s[i] == '!')
                {
                    tmpFile->next->lastEmptyBlock = atoi(tmpRecord.c_str());
                    tmpRecord = "";
                    continue;
                }
                if (s[i] == '#')
                {
                    tmpFile->next->emptyBlocks.push_back(atoi(tmpRecord.c_str()));
                    tmpRecord = "";
                    continue;
                }
                tmpRecord += s[i];
            }
            tmpFile = tmpFile->next;
        }
        tmpFile->next = NULL;
    }
}

BufferManager::~BufferManager()
{
    deletebuff();
    std::string tpath = path + "//buffmanage//EmptyBlockRecord.txt";
    std::string output = "";
    vector<filePtr> outputRecords;
    ofstream ff(tpath);
    ff.close();
    filePtr tmp = fileHead;
    while (tmp->next)
    {
        outputRecords.push_back(tmp->next);
        tmp = tmp->next;
    }
    FILE *fp;
    if (fp = fopen(tpath.c_str(), "rb+"))
    {
        for (auto &i : outputRecords)
        {
            output += i->fileName + "@";
            stringstream tmpNum;
            std::string tmpStr;
            tmpNum << i->lastEmptyBlock;
            tmpNum >> tmpStr;
            output += tmpStr + "!";
            for (auto &j : i->emptyBlocks)
            {
                stringstream tmpf;
                tmpf << j;
                tmpf >> tmpStr;
                output += tmpStr + "#";
            }
            output += ";";
        }
    }
    output += "$";
    fwrite(output.c_str(), output.length(), 1, fp);
    fclose(fp);
}

void BufferManager::flushoneblock(Block* bufferBlock)
{
    if (bufferBlock->isdirty)
    {
        FILE *fp;
        if (fp = fopen(bufferBlock->filename.c_str(), "rb+"))
        {
            fseek(fp, BLOCK_SIZE * bufferBlock->blockoffset, SEEK_SET);
            fwrite(bufferBlock->cblock, BLOCK_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

void BufferManager::flush()
{
    Block* tmpHead = head;
    while (tmpHead->next)
    {
        flushoneblock(tmpHead->next);
        tmpHead = tmpHead->next;
    }
}

void BufferManager::deletebuff()
{
    flush();
    Block* tmpHead = head;
    while (tmpHead->next)
    {
        Block* delPointer = tmpHead;
        tmpHead = tmpHead->next;
        delete delPointer;
    }
}

Block* BufferManager::readnewblock(std::string FileName, int offset, Block* tmpTail)
{
    FILE *fp;
    if (fp = fopen(FileName.c_str(), "rb+"))
    {
        filePtr tmp = fileHead;
        while (tmp->next)
        {
            if (tmp->next->fileName == FileName)
            {
                if (offset >= tmp->next->lastEmptyBlock)
                {
                    fclose(fp);
                    return NULL;
                }
                for (auto &i : tmp->next->emptyBlocks)
                {
                    if (offset == i)
                    {
                        fclose(fp);
                        return NULL;
                    }
                }
                break;
            }
            tmp = tmp->next;
        }
        if (!isFull())
        {
            Block* newBlock = new Block;
            fseek(fp, BLOCK_SIZE * offset, SEEK_SET);
            fread(newBlock->cblock, BLOCK_SIZE, 1, fp);
            newBlock->setBlockLocation(FileName, offset);
            newBlock->charnum = (newBlock->isdirty) ? strlen(newBlock->cblock) : 0;
            if (!head->next)  tail->next = newBlock;
            newBlock->next = head->next;
            head->next = newBlock;
            number++;
        }
        else
        {
            pointer blockt;
            if (!tail->next->pin)
            {
                flushoneblock(tail->next);
                fseek(fp, BLOCK_SIZE * offset, SEEK_SET);
                fread(tail->next->cblock, BLOCK_SIZE, 1, fp);
                tail->next->setBlockLocation(FileName, offset);
                Block* tmp2 = tail->next;
                tail->next = tmpTail;
                tmp2->next = head->next;
                head->next = tmp2;
                tmpTail->next = NULL;
            }
            else {
                pointer btmp = head;
                while (btmp->next)
                {
                    if (btmp->next->pin)
                    {
                        ;
                    }
                    else {
                        blockt = btmp;
                    }
                    btmp = btmp->next;
                }
                flushoneblock(blockt->next);
                fseek(fp, BLOCK_SIZE * offset, SEEK_SET);
                fread(blockt->next->cblock, BLOCK_SIZE, 1, fp);
                blockt->next->setBlockLocation(FileName, offset);

                Block* tmp2 = blockt->next;

                blockt->next = tmp2->next;//delete from list

                //tail->next = tmpTail;
                tmp2->next = head->next;
                head->next = tmp2;
                //tmpTail->next = NULL;
            }

        }
        fclose(fp);
        return head->next;
    }
    return NULL;
}

Block* BufferManager::getblock(std::string FileName, int offset)
{
    Block* tmp = head;
    Block* tmpTail = head;
    while (tmp->next)
    {
        if (tmp->next->filename == FileName&&tmp->next->blockoffset == offset)
        {
            if (tmp != head)
            {
                if (tmp->next == tail->next) tail->next = tmp;
                Block* tmp2 = tmp->next->next;
                tmp->next->next = head->next;
                head->next = tmp->next;
                tmp->next = tmp2;
            }
            return head->next;
        }
        else
        {
            tmpTail = tmp;
            tmp = tmp->next;
        }
    }
    return readnewblock(FileName, offset, tmpTail);
}

bool BufferManager::isFull()
{
    if (number == MAXBLOCKNUM)
        return true;
    else return false;
}

pair<Block*, int> BufferManager::getnullblock(std::string filename)
{
    int offset;
    filePtr tmp = fileHead;
    Block* tmp2 = head;
    Block* tmpTail = head;
    while (tmp2->next)
    {
        tmpTail = tmp2;
        tmp2 = tmp2->next;
    }
    while (tmp->next)
    {
        if (tmp->next->fileName == filename)
        {
            if (tmp->next->emptyBlocks.size())
            {
                offset = tmp->next->emptyBlocks[tmp->next->emptyBlocks.size() - 1];
                tmp->next->emptyBlocks.pop_back();
            }
            else
            {
                offset = tmp->next->lastEmptyBlock;
                tmp->next->lastEmptyBlock++;
            }
            Block* res = readnewblock(filename, offset, tmpTail);
            res->isdirty = 1;
            res->charnum = 0;
            return make_pair(res, offset);
        }
        tmp = tmp->next;
    }
    tmp->next = new File(uncertain, filename);
    offset = tmp->next->lastEmptyBlock;
    tmp->next->lastEmptyBlock++;
    Block* res = readnewblock(filename, offset, tmpTail);
    res->isdirty = 1;
    res->charnum = 0;
    return make_pair(res, offset);
}

Block* BufferManager::createfile(std::string filename)
{
    ofstream f1(filename);
    f1.close();
    return getnullblock(filename).first;
}


void BufferManager::deleteBlock(std::string fileName, int offset)
{
    if (getblock(fileName, offset))
    {
        if (head->next->pin)
        {
            return;
        }
        Block* delBlock = head->next;
        head->next = head->next->next;
        delete delBlock;
        number--;
    }

    File *filetmp = fileHead;
    FILE *fp;
    if (fp = fopen(fileName.c_str(), "rb+"))
    {
        while (filetmp->next)
        {
            if (filetmp->next->fileName == fileName)
            {
                filetmp->next->emptyBlocks.push_back(offset);
                break;
            }
            filetmp = filetmp->next;
        }
        fclose(fp);
    }
}
void BufferManager::deletefileblock(std::string FileName)
{
    Block* tmp = head;
    while (tmp->next)
    {
        if (tmp->next->filename == FileName)
        {
            tmp->filename = "";
            tmp->isdirty = 0;
        }
        tmp = tmp->next;
    }
    filePtr fptr = fileHead;
    while (fptr->next)
    {
        if (fptr->next->fileName == FileName)
        {
            filePtr todelete = fptr->next;
            fptr->next = todelete->next;
            delete todelete;
            break;
        }
        fptr = fptr->next;
    }

}
