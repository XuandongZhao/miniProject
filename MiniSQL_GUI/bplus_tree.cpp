#include "stdafx.h"
#include "bplus_tree.h"
using namespace std;
//BufferManager m;
char* btree::fkey(const std::string&a)
{
    static char buf[1000];
    if (index.type == 2)
    {
        memcpy(buf, a.c_str(), index.length);
        return buf;
    }
    else {
        buf[0] = a[0];
        buf[1] = a[1];
        buf[2] = a[2];
        buf[3] = a[3];
        return buf;
    }
}
btree::btree(const indexinfo& x, int isin) :index(x)
{
    order = (BLOCK_SIZE - nonleafoff) / (x.length + 4) + 1;
    order_least = ceil(order / 2.0);
    nonleaf_most = order - 1;
    leaf_most = (BLOCK_SIZE - leafoff) / (x.length + 8);
    leaf_least = ceil(leaf_most / 2.0);

#ifdef _mydug
    cout << "order" << order << ' ' << "order_least" << order_least << ' ' << "nonleafmost" << nonleaf_most << ' ' << "leafmost" << leaf_most << ' ' << "leafleast" << leaf_least << endl;

#endif // DEBUG


    leafnodesize = 8 + x.length;
    nonleafnodesize = 4 + x.length;
    Block*info = nullptr;
    if (isin == 0)
    {
        info = m.createfile(index.filename);
        *reinterpret_cast<int*>(info->cblock) = x.type;

        *reinterpret_cast<int*>(info->cblock + 8) = 0;

        info->isdirty = 1;
        pair<Block*, int>res = m.getnullblock(index.filename);
        proot = res.second;
        *reinterpret_cast<int*>(info->cblock + 4) = proot;

        *reinterpret_cast<int*>(res.first->cblock) = 1;
        *reinterpret_cast<int*>(res.first->cblock + 4) = 0;
        *reinterpret_cast<int*>(res.first->cblock + 8) = 0x7FFFFFFF;
        *reinterpret_cast<int*>(res.first->cblock + 12) = 0x7FFFFFFF;
        *reinterpret_cast<int*>(res.first->cblock + 16) = 0x7FFFFFFF;
        res.first->isdirty = 1;
    }
    else {
        Block*tmp = m.getblock(index.filename, 0);
        proot = *reinterpret_cast<int*>(tmp->cblock + 4);
        index.type = keytype(*reinterpret_cast<int*>(tmp->cblock));
    }
}
void btree::insert(std::string key, int blockoffset, int offset)
{
    //cout << "insert in tree" << endl;
    std::string tmp;
    char*tmpc = new char[BLOCK_SIZE];

    Block*root = m.getblock(index.filename, proot);//read block
    if (root == NULL)
    {
        //cout << "&&&&&&&&" << endl;
        pair<pointer, int>res = m.getnullblock(index.filename);
        root = res.first;
        updateroot(res.second);
    }
    if (root->isnull())
    {
        //cout << "^^^^^^" << endl;
        *reinterpret_cast<int*>(root->cblock) = 1;
        *reinterpret_cast<int*>(root->cblock + 4) = 0;
        *reinterpret_cast<int*>(root->cblock + 8) = 0x7FFFFFFF;
        *reinterpret_cast<int*>(root->cblock + 12) = 0x7FFFFFFF;
        *reinterpret_cast<int*>(root->cblock + 16) = 0x7FFFFFFF;
        root->isdirty = 1;
        insertinleaf(0, root, key, blockoffset, offset);
        delete[]tmpc;
        return;
    }
    PII res = bsearch(key, root);
    //cout << res.first << "%%%%%%" << res.second << endl;
    Block*beforeinsert = m.getblock(index.filename, res.first);
    int cntblock = beforeinsert->getsize();
    if (cntblock < leaf_most)
    {
        insertinleaf(res.second + 1, beforeinsert, key, blockoffset, offset);
        delete[]tmpc;
        return;
    }
    else {
        int halfn = ceil((cntblock + 1)*1.0 / 2);
        int leftn = cntblock + 1 - halfn;
        char*buf = new char[BLOCK_SIZE * 2];
        memcpy(buf, beforeinsert->cblock + leafoff, leafnodesize*(res.second + 1));

        *reinterpret_cast<int*>(buf + leafnodesize*(res.second + 1)) = blockoffset;
        *reinterpret_cast<int*>(buf + leafnodesize*(res.second + 1) + 4) = offset;
        char hp[6];
        if (index.type == 2)
        {
            memcpy(buf + leafnodesize*(res.second + 1) + 8, key.c_str(), index.length);
        }
        else {
            hp[0] = key[0];
            hp[1] = key[1];
            hp[2] = key[2];
            hp[3] = key[3];
            memcpy(buf + leafnodesize*(res.second + 1) + 8, hp, index.length);
        }
        if (cntblock - res.second - 1>0)
            memcpy(buf + leafnodesize*(res.second + 2), beforeinsert->cblock + leafoff + leafnodesize*(res.second + 1), leafnodesize*(cntblock - res.second - 1));
        //insert object
        memcpy(beforeinsert->cblock + leafoff, buf, leafnodesize*(halfn));
        beforeinsert->isdirty = 1;
        std::pair<Block*, int>nblock = m.getnullblock(index.filename);
        memcpy(nblock.first->cblock + leafoff, buf + leafnodesize*halfn, leftn*leafnodesize);
        nblock.first->isdirty = 1;
        //update attrubes
        //is leaf
        nblock.first->setleaf(1);
        //set cnt
        beforeinsert->update_record(halfn);
        nblock.first->update_record(leftn);
        //xiong di
        int rightsb = beforeinsert->getright();
        nblock.first->setleft(res.first);
        beforeinsert->setright(nblock.second);
        nblock.first->setright(rightsb);
        if (rightsb != 0x7FFFFFFF)
        {
            Block*tmpblock = m.getblock(index.filename, rightsb);
            tmpblock->setleft(nblock.second);
            tmpblock->isdirty = 1;
        }
        //charnum
        beforeinsert->update_charnum(leafnodesize);
        nblock.first->update_charnum(leafnodesize);
        //father
        int fa = beforeinsert->getfather();
        nblock.first->setfather(fa);
        std::string keyinsert = nblock.first->getkey(leafoff, leafnodesize, index.length, 0,index.type);
        if (fa == 0x7FFFFFFF)//root
        {
            //cout << "FUCK" << endl;
            std::pair<Block*, int>nfather = m.getnullblock(index.filename);
            nfather.first->isdirty = 1;
            updateroot(nfather.second);
            nfather.first->setleaf(0);
            nfather.first->update_record(1);
            nfather.first->setfather(0x7FFFFFFF);//father
            *reinterpret_cast<int*>(nfather.first->cblock + nonleafoff) = res.first;
            insertinparentc(nfather.first, 0, nblock.second, keyinsert);
            //update
            nfather.first->update_record(2);//cnt
            beforeinsert->setfather(nfather.second);
            nblock.first->setfather(nfather.second);
            nfather.first->setleft(0x7FFFFFFF);
            nfather.first->setright(0x7FFFFFFF);//sibling
            delete[]tmpc;
            return;
        }
        delete[]tmpc;
        insertinparent(fa, keyinsert, nblock.second);
    }

}
void btree::insertinleaf(int pos, Block *block, const std::string & key, int blocknum, int offset)
{
    block->isdirty = 1;
    int cnt = *reinterpret_cast<int*>((block->cblock) + 4);
    //cout << "cnt" << cnt << endl;
    int loc = leafoff + cnt*leafnodesize;

    int insertloc = leafoff + pos*leafnodesize;

    char*buf = new char[BLOCK_SIZE];
    int savesize = loc - insertloc;
    int bufsize = savesize + leafnodesize;
    *reinterpret_cast<int*>(buf) = blocknum;
    *reinterpret_cast<int*>(buf + 4) = offset;
    if (index.type == 2)
    {
        memcpy(buf + 8, key.c_str(), index.length);
    }
    else {
        char hp[6];
        hp[0] = key[0]; hp[1] = key[1]; hp[2] = key[2]; hp[3] = key[3]; hp[4] = '\0';
        memcpy(buf + 8, hp, index.length);
    }

    //off   0 1 2  cnt=3
    //      1     save 1-2
    memcpy(buf + leafnodesize, block->cblock + insertloc, savesize);
    memcpy(block->cblock + insertloc, buf, bufsize);
    block->set_add_one_record();
    block->update_charnum(leafnodesize);
    delete[]buf;
}
void btree::insertinparentc(Block* pblock, int pos, int pointer, const std::string &key)
{
    pblock->isdirty = 1;
    char *buf = new char[BLOCK_SIZE];
    if (index.type == 2)
    {
        memcpy(buf, key.c_str(), index.length);
    }
    else {
        char hp[6];
        hp[0] = key[0]; hp[1] = key[1]; hp[2] = key[2]; hp[3] = key[3]; hp[4] = '\0';
        memcpy(buf, hp, index.length);
    }
    *reinterpret_cast<int*>(buf + index.length) = pointer;
    int cntb = pblock->getsize();
    memcpy(buf + nonleafnodesize, pblock->cblock + nonleafoff + 4 + pos*nonleafnodesize, (cntb - pos)*nonleafnodesize);
    memcpy(pblock->cblock + nonleafoff + 4 + pos*nonleafnodesize, buf, (cntb - pos + 1)*nonleafnodesize);
    pblock->set_add_one_record();
    pblock->update_charnum(nonleafnodesize);
    delete[]buf;
}
void btree::insertinparent(int fa, std::string key, int sunoff)
{
    Block*beforeinsert = m.getblock(index.filename, fa);
    int cnt_record = beforeinsert->getsize();
    int loc = -1;
    std::string tmpkey;
    for (int i = 0; i < cnt_record; i++)
    {
        tmpkey = beforeinsert->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
        if (compless(tmpkey,key))//tmpkey < key)
        {
            loc = i;
        }
        else
        {
            break;
        }
    }
    if (cnt_record < nonleaf_most)
    {
        insertinparentc(beforeinsert, loc + 1, sunoff, key);
        return;
    }
    else {//split
          //merge
        char *buf = new char[BLOCK_SIZE * 2];
        tmpkey = getsmallestkey(beforeinsert);
        if (loc == -1 && compbig(tmpkey,key))//tmpkey > key)
        {
            if (index.type == 2)
            {
                memcpy(buf, key.c_str(), index.length);
            }
            else {
                char hp[6];
                hp[0] = key[0]; hp[1] = key[1]; hp[2] = key[2]; hp[3] = key[3]; hp[4] = '\0';
                memcpy(buf, hp, index.length);
            }
            *reinterpret_cast<int*>(buf + index.length) = sunoff;
            memcpy(buf + nonleafnodesize, fkey(tmpkey), index.length);
            memcpy(buf + nonleafnodesize + index.length, beforeinsert->cblock + nonleafoff, 4 + cnt_record*nonleafnodesize);
        }
        else {
            loc += 1;
            memcpy(buf, fkey(tmpkey), index.length);
            memcpy(buf + index.length, beforeinsert->cblock + nonleafoff, 4 + loc*nonleafnodesize);
            memcpy(buf + (loc + 1)*nonleafnodesize, fkey(key), index.length);
            *reinterpret_cast<int*>(buf + (loc + 1)*nonleafnodesize + index.length) = sunoff;
            memcpy(buf + (loc + 2)*nonleafnodesize, beforeinsert->cblock + nonleafoff + 4 + loc*nonleafnodesize, (cnt_record - loc)*nonleafnodesize);
        }
        //split
        int halfn = ceil((cnt_record + 2) / 2.0);
        int resn = cnt_record + 2 - halfn;
        pair<Block*, int>nblock = m.getnullblock(index.filename);
        memcpy(beforeinsert->cblock + nonleafoff, buf + index.length, 4 + (halfn - 1)*nonleafnodesize);
        memcpy(nblock.first->cblock + nonleafoff, buf + halfn*nonleafnodesize + index.length, 4 + (resn - 1)*nonleafnodesize);

        //dirty
        beforeinsert->isdirty = 1;
        nblock.first->isdirty = 1;
        //update
        beforeinsert->setleaf(0);//isleaf
        nblock.first->setleaf(0);
        beforeinsert->update_record(halfn);//cnt
        nblock.first->update_record(resn);
        int rightsib = beforeinsert->getright();//sibling
        beforeinsert->setright(nblock.second);
        nblock.first->setleft(fa);
        nblock.first->setright(rightsib);
        if (rightsib != 0x7FFFFFFF)
        {
            Block*tmpblock = m.getblock(index.filename, rightsib);
            tmpblock->setleft(nblock.second);
            tmpblock->isdirty = 1;
        }
        resetfather(beforeinsert, fa);//father
        resetfather(nblock.first, nblock.second);
        beforeinsert->update_charnum(nonleafnodesize);
        nblock.first->update_charnum(nonleafnodesize);
        int bfa = beforeinsert->getfather();
        std::string keyinsert = getsmallestkey(nblock.first);
        if (bfa == 0x7FFFFFFF)//root
        {
            std::pair<Block*, int>nfather = m.getnullblock(index.filename);
            updateroot(nfather.second);
            *reinterpret_cast<int*>(nfather.first->cblock + nonleafoff) = fa;
            nfather.first->setleaf(0);//isleaf
            nfather.first->update_record(1);//cnt
            nfather.first->setfather(0x7FFFFFFF);//father

            insertinparentc(nfather.first, 0, nblock.second, keyinsert);
            //update
            nfather.first->update_record(2);//cnt
            beforeinsert->setfather(nfather.second);
            nblock.first->setfather(nfather.second);
            nfather.first->setleft(0x7FFFFFFF);
            nfather.first->setright(0x7FFFFFFF);//sibling
            nfather.first->update_charnum(nonleafnodesize);
            delete[]buf;
            return;
        }
        else {
            nblock.first->setfather(bfa);
            delete[]buf;
            insertinparent(bfa, keyinsert, nblock.second);
            return;
        }
    }
}

void btree::deleteonerecord(std::string key)
{
    proot = getrootoffset();
    PII td = bsearch(key, m.getblock(index.filename, proot));
    if (td.second == -1)
    {
        return;
    }
    Block*beforedelete = m.getblock(index.filename, td.first);
    std::string keydelete = beforedelete->getkey(leafoff, leafnodesize, index.length, td.second,index.type);
    if (keydelete != key)
    {
        return;
    }
    else {
        char*buf = new char[BLOCK_SIZE];
        int cnt_record = beforedelete->getsize();
        memcpy(buf, beforedelete->cblock + leafoff + (td.second + 1)*leafnodesize, (cnt_record - td.second - 1)*leafnodesize);
        memcpy(beforedelete->cblock + leafoff + (td.second)*leafnodesize, buf, (cnt_record - td.second - 1)*leafnodesize);
        beforedelete->isdirty = 1;
        cnt_record -= 1;
        beforedelete->update_record(cnt_record);
        if (td.second == 0)
        {
            updatefather(beforedelete->getfather(), keydelete, getsmallestkey(beforedelete));

        }
        if (cnt_record < leaf_least)//merge
        {
            if (beforedelete->getfather() == 0x7FFFFFFF)//is root
            {
                return;
            }
            else {//merge
                bool toright = 1;
                if (beforedelete->getright() != 0x7FFFFFFF)
                {
                    Block*tright = m.getblock(index.filename, beforedelete->getright());
                    if (tright->getfather() == beforedelete->getfather())
                    {
                        toright = 1;
                    }
                    else {
                        toright = 0;
                    }
                }
                else {
                    toright = 0;
                }
                if (toright)
                {
                    int pright = beforedelete->getright();
                    Block*nright = m.getblock(index.filename, pright);
                    int right_record = nright->getsize();
                    if (cnt_record + right_record <= leaf_most)
                    {
                        memcpy(beforedelete->cblock + leafoff + cnt_record*leafnodesize, nright->cblock + leafoff, right_record*leafnodesize);
                        if (deleteinparent(beforedelete->getfather(), getsmallestkey(nright)))
                        {
                            updateroot(td.first);
                            beforedelete->setfather(0x7FFFFFFF);
                            beforedelete->setleaf(1);
                        }
                        //update
                        beforedelete->setright(nright->getright());
                        beforedelete->update_record(cnt_record + right_record);
                        beforedelete->update_charnum(leafnodesize);
                        int rright = nright->getright();
                        if (rright != 0x7FFFFFFF)
                        {
                            Block*nrright = m.getblock(index.filename, rright);
                            nrright->setleft(td.first);
                            nrright->isdirty = 1;
                        }
                        beforedelete->isdirty = 1;
                        m.deleteBlock(index.filename, pright);
                        return;
                    }
                    else {
                        nright->isdirty = 1;
                        beforedelete->isdirty = 1;
                        std::string rsmall = getsmallestkey(nright);
                        int leftn = ceil((cnt_record + right_record) / 2.0);
                        int rightn = cnt_record + right_record - leftn;
                        int borrow = right_record - rightn;
                        memcpy(beforedelete->cblock + leafoff + cnt_record*leafnodesize, nright->cblock + leafoff, borrow*leafnodesize);
                        char * buf = new char[BLOCK_SIZE];
                        memcpy(buf, nright->cblock + leafoff + borrow*leafnodesize, rightn*leafnodesize);
                        memcpy(nright->cblock + leafoff, buf, rightn*leafnodesize);
                        delete[]buf;
                        //update
                        beforedelete->update_record(leftn);
                        nright->update_record(rightn);
                        beforedelete->update_charnum(leafnodesize);
                        nright->update_charnum(leafnodesize);
                        std::string rsmallnow = getsmallestkey(nright);
                        updatefather(beforedelete->getfather(), rsmall, rsmallnow);
                        return;
                    }
                }
                else {//left
                    int pleft = beforedelete->getleft();
                    Block*nleft = m.getblock(index.filename, pleft);
                    int left_record = nleft->getsize();
                    if (cnt_record + left_record <= leaf_most)
                    {
                        memcpy(nleft->cblock + leafoff + left_record*leafnodesize, beforedelete->cblock + leafoff, cnt_record*leafnodesize);
                        if (deleteinparent(beforedelete->getfather(), getsmallestkey(beforedelete)))
                        {
                            updateroot(pleft);
                            nleft->setfather(0x7FFFFFFF);
                            nleft->setleaf(1);
                        }
                        //update
                        int rightc = beforedelete->getright();
                        nleft->setright(rightc);
                        nleft->update_record(cnt_record + left_record);
                        nleft->update_charnum(leafnodesize);
                        if (rightc != 0x7FFFFFFF)
                        {
                            Block *nrightc = m.getblock(index.filename, rightc);
                            nrightc->setleft(pleft);
                            nrightc->isdirty = 1;
                        }
                        nleft->isdirty = 1;
                        m.deleteBlock(index.filename, td.first);
                        return;
                    }
                    else {
                        std::string deletekey = getsmallestkey(beforedelete);
                        int leftn = ceil((cnt_record + left_record) / 2.0);
                        int rightn = cnt_record + left_record - leftn;
                        int borrow = cnt_record - rightn;
                        memcpy(nleft + leafoff + left_record*leafnodesize, beforedelete + leafoff, borrow*leafnodesize);
                        char*buf = new char[BLOCK_SIZE];
                        memcpy(buf, beforedelete->cblock + leafoff + borrow*leafnodesize, rightn*leafnodesize);
                        memcpy(beforedelete->cblock + leafoff, buf, rightn*leafnodesize);
                        delete[]buf;
                        //update
                        nleft->update_record(leftn);
                        beforedelete->update_record(rightn);
                        nleft->update_charnum(leafnodesize);
                        beforedelete->update_charnum(leafnodesize);
                        std::string keynow = getsmallestkey(beforedelete);
                        updatefather(beforedelete->getfather(), deletekey, keynow);
                        beforedelete->isdirty = 1;
                        nleft->isdirty = 1;
                        return;
                    }
                }
            }
        }
    }
}
bool btree::deleteinparent(int fa, const std::string &key)
{
    Block*beforedelete = m.getblock(index.filename, fa);
    char*buf = new char[BLOCK_SIZE];
    int loc = -1;
    int deletesize = beforedelete->getsize();
    std::string tmpkey;
    for (int i = 0; i < deletesize; i++)
    {
        tmpkey = beforedelete->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
        if (tmpkey == key)
        {
            loc = i;
            break;
        }
    }
    deletesize -= 1;
    if (loc < 0)
    {
        static_assert(1, "deletefail");
        return 0;
    }
    if (loc == deletesize)
    {
        beforedelete->update_record(deletesize + 1);// 0 1
    }
    else {
        memcpy(buf, beforedelete->cblock + 4 + nonleafoff + (loc + 1)*nonleafnodesize, (deletesize - loc)*nonleafnodesize);
        memcpy(beforedelete->cblock + nonleafoff + 4 + loc*nonleafnodesize, buf, (deletesize - loc)*nonleafnodesize);
        beforedelete->update_record(deletesize + 1);
    }
    beforedelete->update_charnum(nonleafnodesize);
    beforedelete->isdirty = 1;
    if (beforedelete->getfather() == 0x7FFFFFFF)//is rooot
    {
        if (deletesize != 0)
        {
            return 0;
        }
        else {
            m.deleteBlock(index.filename, fa);
            return 1;
        }
    }
    else {
        if (deletesize + 1 >= order_least)
        {
            return 0;
        }
        else {//merge
            bool toright = 1;
            Block*nborrow = nullptr;
            int pright = beforedelete->getright();
            if (pright != 0x7FFFFFFF)
            {
                nborrow = m.getblock(index.filename, pright);
                if (nborrow->getfather() == beforedelete->getfather())
                {
                    toright == 1;
                }
                else {
                    toright = 0;
                }
            }
            else {
                toright = 0;
            }
            if (toright)
            {
                int deleteorder = deletesize + 1;
                int rightsize = nborrow->getsize();
                int rightorder = rightsize + 1;
                tmpkey = getsmallestkey(nborrow);
                if (deleteorder + rightorder <= order)//merge
                {
                    resetfather(nborrow, fa);
                    memcpy(beforedelete->cblock + nonleafoff + 4 + deletesize*nonleafnodesize, tmpkey.c_str(), index.length);
                    memcpy(beforedelete->cblock + nonleafoff + (deletesize + 1)*nonleafnodesize, nborrow->cblock + nonleafoff, 4 + rightsize*nonleafnodesize);
                    beforedelete->update_record(deleteorder + rightorder);
                    beforedelete->update_charnum(nonleafnodesize);
                    int tright = nborrow->getright();
                    beforedelete->setright(tright);
                    if (tright != 0x7FFFFFFF)
                    {
                        Block*tmpblock = m.getblock(index.filename, tright);
                        tmpblock->setleft(fa);
                        tmpblock->isdirty = 1;
                    }
                    nborrow->isdirty = 1;
                    m.deleteBlock(index.filename, pright);

                    if (deleteinparent(beforedelete->getfather(), tmpkey))
                    {
                        updateroot(fa);
                        beforedelete->setfather(0x7FFFFFFF);
                    }
                    return 0;
                }
                else {//borrow
                    int leftn = ceil((deleteorder + rightorder) / 2.0);
                    int rightn = deleteorder + rightorder - leftn;
                    int borrow = (rightorder - rightn);
                    memcpy(beforedelete->cblock + nonleafoff + 4 + deletesize*nonleafnodesize, tmpkey.c_str(), index.length);
                    memcpy(beforedelete->cblock + nonleafoff + (deletesize + 1)*nonleafnodesize, nborrow->cblock + nonleafoff, borrow*nonleafnodesize - index.length);
                    memcpy(buf, nborrow->cblock + nonleafoff + borrow*nonleafnodesize, (rightn)*nonleafnodesize - index.length);
                    memcpy(nborrow->cblock + nonleafoff, buf, rightn*nonleafnodesize - index.length);
                    beforedelete->update_record(leftn);
                    nborrow->update_record(rightn);
                    beforedelete->update_charnum(nonleafnodesize);
                    nborrow->update_charnum(nonleafnodesize);
                    updatefather(beforedelete->getfather(), tmpkey, getsmallestkey(nborrow));
                    resetfather(beforedelete, fa);
                    nborrow->isdirty = 1;
                    return 0;
                }
            }
            else {
                int leftblock = beforedelete->getleft();
                nborrow = m.getblock(index.filename, leftblock);
                int deleteorder = deletesize + 1;
                int leftsize = nborrow->getsize();
                int leftorder = leftsize + 1;
                tmpkey = getsmallestkey(beforedelete);
                if (leftorder + deleteorder <= order)//merge
                {
                    resetfather(beforedelete, leftblock);
                    memcpy(nborrow->cblock + nonleafoff + 4 + leftsize*nonleafnodesize, tmpkey.c_str(), index.length);
                    memcpy(nborrow->cblock + nonleafoff + (leftsize + 1)*nonleafnodesize, beforedelete->cblock + nonleafoff, deletesize*nonleafnodesize + 4);
                    nborrow->update_record(leftorder + deleteorder);
                    nborrow->update_charnum(nonleafnodesize);
                    int pright = beforedelete->getright();
                    nborrow->setright(pright);
                    if (pright != 0x7FFFFFFF)
                    {
                        Block*tmpblock = m.getblock(index.filename, pright);
                        tmpblock->setleft(leftblock);
                        tmpblock->isdirty = 1;
                    }
                    nborrow->isdirty = 1;
                    m.deleteBlock(index.filename, fa);
                    if (deleteinparent(nborrow->getfather(), tmpkey))
                    {
                        updateroot(leftblock);
                        nborrow->setfather(0x7FFFFFFF);
                    }
                    return 0;
                }
                else {
                    int leftn = ceil((leftorder + deleteorder) / 2.0);
                    int rightn = leftorder + deleteorder - leftn;
                    int borrow = deleteorder - rightn;
                    memcpy(nborrow->cblock + nonleafoff + 4 + leftsize*nonleafnodesize, tmpkey.c_str(), index.length);
                    memcpy(nborrow->cblock + nonleafoff + (leftsize + 1)*nonleafnodesize, beforedelete->cblock + nonleafoff, borrow*nonleafnodesize - index.length);
                    memcpy(buf, beforedelete->cblock + nonleafoff + borrow*nonleafnodesize - index.length, rightn*nonleafnodesize - index.length);
                    memcpy(beforedelete->cblock + nonleafoff, buf, rightn*nonleafnodesize - index.length);
                    nborrow->update_record(leftn);
                    beforedelete->update_record(rightn);
                    nborrow->update_charnum(nonleafnodesize);
                    beforedelete->update_charnum(nonleafnodesize);
                    updatefather(nborrow->getfather(), tmpkey, getsmallestkey(beforedelete));
                    resetfather(nborrow, leftblock);
                    nborrow->isdirty = 1;
                    beforedelete->isdirty = 1;
                    return 0;
                }
            }
        }
    }
}

void btree::updatefather(int fa, const std::string & key, const std::string & rep)
{
    if (fa == 0x7FFFFFFF)
    {
        return;
    }
    Block*beforeupdate = m.getblock(index.filename, fa);
    int cnt_record = beforeupdate->getsize();
    int loc = -1;
    std::string tmpkey;
    for (int i = 0; i < cnt_record; i++)
    {
        tmpkey = beforeupdate->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
        if (tmpkey == key)
        {
            loc = i;
            beforeupdate->setkey(nonleafoff, nonleafnodesize, index.length, i, rep,index.type);
            if (i == 0)
            {
                updatefather(beforeupdate->getfather(), tmpkey, rep);
            }
            return;
        }
        else if (compbig(tmpkey,key))//tmpkey > key)
        {
            break;
        }
    }
    updatefather(beforeupdate->getfather(), key, rep);
}
bool btree::compless(const std::string& x, const std::string& y)
{
    char buf1[5] = { 0 }, buf2[5] = { 0 };
    if (index.type == 0)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return (*reinterpret_cast<int*>(buf1) < (*reinterpret_cast<int*>(buf2)));
    }
    else if (index.type == 1)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return  (*reinterpret_cast<float*>(buf1)) < (*reinterpret_cast<float*>(buf2));
    }
    else if (index.type == 2)
    {
        return x < y;
    }
    else {
        cerr << "type error" << endl;
        exit(0);
    }
}
bool btree::complessequal(const std::string& x, const std::string& y)
{
    char buf1[5] = { 0 }, buf2[5] = { 0 };
    if (index.type == 0)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return (*reinterpret_cast<int*>(buf1)) <= (*reinterpret_cast<int*>(buf2));
    }
    else if (index.type == 1)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return  (*reinterpret_cast<float*>(buf1)) <= (*reinterpret_cast<float*>(buf2));
    }
    else if (index.type == 2)
    {
        return x <= y;
    }
    else {
        cerr << "type error" << endl;
        exit(0);
    }
}
bool btree::compbig(const std::string& x, const std::string& y)
{
    char buf1[5] = { 0 }, buf2[5] = { 0 };
    if (index.type == 0)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return (*reinterpret_cast<int*>(buf1)) > (*reinterpret_cast<int*>(buf2));
    }
    else if (index.type == 1)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return  (*reinterpret_cast<float*>(buf1)) > (*reinterpret_cast<float*>(buf2));
    }
    else if (index.type == 2)
    {
        return x > y;
    }
    else {
        cerr << "type error" << endl;
        exit(0);
    }
}
bool btree::compbigequal(const std::string& x, const std::string& y)
{
    char buf1[5] = { 0 }, buf2[5] = { 0 };
    if (index.type == 0)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return (*reinterpret_cast<int*>(buf1)) >= (*reinterpret_cast<int*>(buf2));
    }
    else if (index.type == 1)
    {
        memcpy(buf1, fkey(x), 4);
        memcpy(buf2, fkey(y), 4);
        return  (*reinterpret_cast<float*>(buf1)) >= (*reinterpret_cast<float*>(buf2));
    }
    else if (index.type == 2)
    {
        return x >= y;
    }
    else {
        cerr << "type error" << endl;
        exit(0);
    }
}


//binary search
pair<int, int> btree::bsearch(std::string key, Block *root)
{
    Block* tmp = root;
    bool end_while = 0;
    std::string tkey;
    pair<int, int>ans(proot, -1);
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            int blocksize = tmp->getsize();
            int bstart = 0;
            int bend = blocksize - 1;
            int bmid;
            bool judge = 0;
            ans.second = bstart;
            while (bstart < bend)
            {
                if (judge)	break;
                if (bend - bstart == 1)	judge = 1;
                bmid = (bstart + bend) >> 1;
                tkey = tmp->getkey(leafoff, leafnodesize, leafnodesize - 8, bmid,index.type);
                //1 2 3 4 5 6 7
                if (compless(tkey,key))//tkey < key)
                {
                    bstart = bmid + 1;
                    ans.second = bstart;
                }
                else {
                    bend = bmid;
                    ans.second = bend;
                }
            }
            if (ans.second >= 0)
            {
                tkey = tmp->getkey(leafoff, leafnodesize, index.length, ans.second,index.type);
                if (compbig(tkey,key))//tkey > key)
                {
                    ans.second--;
                }
            }
            return ans;
        }
        else {
            int blocksize = tmp->getsize();
            int loc = -1;
            for (int i = 0; i < blocksize; i++)
            {
                tkey = tmp->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
                if ( compbig(tkey,key)    )//tkey > key)
                {
                    break;
                }
                else {
                    loc = i;
                }
            }
            if (loc == -1)
            {
                ans.first = tmp->getpointer(0, nonleafnodesize);
                tmp = m.getblock(index.filename, ans.first);
            }
            else {
                ans.first = tmp->getpointer(loc + 1, nonleafnodesize);
                tmp = m.getblock(index.filename, ans.first);
            }
        }
    }
}
pair<int, int> btree::searchequal(const std::string & key)
{
    Block* tmp = m.getblock(index.filename, proot);
    bool end_while = 0;
    std::string tkey;
    pair<int, int>ans(-1, -1);
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            int blocksize = tmp->getsize();
            for (int i = 0; i < blocksize; i++)
            {
                tkey = tmp->getkey(leafoff, leafnodesize, index.length, i,index.type);
                if (tkey == key)
                {

                    ans.first = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i);
                    ans.second = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i + 4);
                    return ans;

                }
            }
            return ans;
        }
        else {
            int blocksize = tmp->getsize();
            int loc = -1;
            for (int i = 0; i < blocksize; i++)
            {
                tkey = tmp->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
                if (compbig(tkey,key))//tkey > key)
                {
                    break;
                }
                else {
                    loc = i;
                }
            }
            if (loc == -1)
            {
                tmp = m.getblock(index.filename, tmp->getpointer(0, nonleafnodesize));
            }
            else {

                tmp = m.getblock(index.filename, tmp->getpointer(loc + 1, nonleafnodesize));
            }
        }
    }
    return ans;
}
vector<pair<int, int>>btree::searchbetween(const std::string& key1, const std::string& key2)
{
    vector<pair<int, int>>ans;
    Block* tmp = m.getblock(index.filename, proot);
    bool end_while = 0;
    std::string tkey;
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            while (1)
            {
                int blocksz = tmp->getsize();
                for (int i = 0; i < blocksz; i++)
                {
                    tkey = tmp->getkey(leafoff, leafnodesize, index.length, i,index.type);
                    if (compless(tkey,key1))//tkey < key1)
                    {
                        continue;
                    }
                    else if (compbigequal(tkey,key1)&&complessequal(tkey,key2))//tkey >= key1&&tkey <= key2)
                    {
                        int f1 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i);
                        int f2 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i + 4);
                        ans.push_back(make_pair(f1, f2));
                    }
                    else {
                        return ans;
                    }
                    int nextb = tmp->getright();
                    if (nextb == 0x7FFFFFFF)
                    {
                        return ans;
                    }
                    else {
                        tmp = m.getblock(index.filename, nextb);
                    }
                }
            }
        }
        else {
            int blocksize = tmp->getsize();
            int loc = -1;
            for (int i = 0; i < blocksize; i++)
            {
                tkey = tmp->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
                if (compbig(tkey,key1))//tkey > key1)
                {
                    break;
                }
                else {
                    loc = i;
                }
            }
            if (loc == -1)
            {
                tmp = m.getblock(index.filename, tmp->getpointer(0, nonleafnodesize));
            }
            else {
                tmp = m.getblock(index.filename, tmp->getpointer(loc + 1, nonleafnodesize));
            }
        }
    }

}

vector<pair<int, int>>btree::searchbiggerthan(const std::string&key)
{
    vector<pair<int, int>>ans;
    Block* tmp = m.getblock(index.filename, proot);
    bool end_while = 0;
    std::string tkey;
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            while (1)
            {
                int blocksz = tmp->getsize();
                for (int i = 0; i < blocksz; i++)
                {
                    tkey = tmp->getkey(leafoff, leafnodesize, index.length, i,index.type);
                    if (complessequal(tkey,key))//tkey <= key)
                    {
                        continue;
                    }
                    else
                    {
                        int f1 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i);
                        int f2 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i + 4);
                        ans.push_back(make_pair(f1, f2));
                    }

                }
                int nextb = tmp->getright();
                if (nextb == 0x7FFFFFFF)
                {
                    return ans;
                }
                else {
                    tmp = m.getblock(index.filename, nextb);
                }
            }
        }
        else {
            int blocksize = tmp->getsize();
            int loc = -1;
            for (int i = 0; i < blocksize; i++)
            {
                tkey = tmp->getkey(nonleafoff, nonleafnodesize, index.length, i,index.type);
                if (compbig(tkey,key))//tkey > key)
                {
                    break;
                }
                else {
                    loc = i;
                }
            }
            if (loc == -1)
            {
                tmp = m.getblock(index.filename, tmp->getpointer(0, nonleafnodesize));
            }
            else {
                tmp = m.getblock(index.filename, tmp->getpointer(loc + 1, nonleafnodesize));
            }
        }
    }
}

vector<pair<int, int>>btree::searchbiggerequalthan(const std::string&key)
{
    vector<pair<int, int>>ans;
    Block* tmp = m.getblock(index.filename, proot);
    bool end_while = 0;
    std::string tkey;
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            while (1)
            {
                int blocksz = tmp->getsize();
                for (int i = 0; i < blocksz; i++)
                {
                    tkey = tmp->getkey(leafoff, leafnodesize, index.length, i,index.type);
                    if (compless(tkey,key))//tkey < key)
                    {
                        continue;
                    }
                    else
                    {
                        int f1 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i);
                        int f2 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i + 4);
                        ans.push_back(make_pair(f1, f2));
                    }

                }
                int nextb = tmp->getright();
                if (nextb == 0x7FFFFFFF)
                {
                    return ans;
                }
                else {
                    tmp = m.getblock(index.filename, nextb);
                }
            }
        }
        else {
            int blocksize = tmp->getsize();
            int loc = -1;
            for (int i = 0; i < blocksize; i++)
            {
                tkey = tmp->getkey(nonleafoff, nonleafnodesize, index.length, i ,index.type);
                if (compbig(tkey,key))//tkey > key)
                {
                    break;
                }
                else {
                    loc = i;
                }
            }
            if (loc == -1)
            {
                tmp = m.getblock(index.filename, tmp->getpointer(0, nonleafnodesize));
            }
            else {
                tmp = m.getblock(index.filename, tmp->getpointer(loc + 1, nonleafnodesize));
            }
        }
    }
}

vector<pair<int, int>>btree::searchlessthan(const std::string&key)
{
    vector<pair<int, int>>ans;
    Block* tmp = m.getblock(index.filename, proot);
    bool end_while = 0;
    std::string tkey;
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            while (1)
            {
                int blocksz = tmp->getsize();
                for (int i = 0; i < blocksz; i++)
                {
                    tkey = tmp->getkey(leafoff, leafnodesize, index.length, i ,index.type);
                    if (compbigequal(tkey,key))//tkey >= key)
                    {
                        return ans;
                    }
                    else
                    {
                        int f1 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i);
                        int f2 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i + 4);
                        ans.push_back(make_pair(f1, f2));
                    }

                }
                int nextb = tmp->getright();
                if (nextb == 0x7FFFFFFF)
                {
                    return ans;
                }
                else {
                    tmp = m.getblock(index.filename, nextb);
                }
            }
        }
        else {

            tmp = m.getblock(index.filename, tmp->getpointer(0, nonleafnodesize));
        }
    }
}

vector<pair<int, int>>btree::searchlessequalthan(const std::string&key)
{
    vector<pair<int, int>>ans;
    Block* tmp = m.getblock(index.filename, proot);
    bool end_while = 0;
    std::string tkey;
    while (!end_while)
    {
        if (tmp->isleaf())
        {
            end_while = 1;
            while (1)
            {
                int blocksz = tmp->getsize();
                for (int i = 0; i < blocksz; i++)
                {
                    tkey = tmp->getkey(leafoff, leafnodesize, index.length, i, index.type);
                    if (compbig(tkey, key))//tkey > key)
                    {
                        return ans;
                    }
                    else
                    {
                        int f1 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i);
                        int f2 = *reinterpret_cast<int*>(tmp->cblock + leafoff + leafnodesize*i + 4);
                        ans.push_back(make_pair(f1, f2));
                    }

                }
                int nextb = tmp->getright();
                if (nextb == 0x7FFFFFFF)
                {
                    return ans;
                }
                else {
                    tmp = m.getblock(index.filename, nextb);
                }
            }
        }
        else {

            tmp = m.getblock(index.filename, tmp->getpointer(0, nonleafnodesize));
        }
    }
}

vector<pair<int, int>>btree::searchall()
{
    pointer root = m.getblock(index.filename, proot);
    std::string skey = getsmallestkey(root);
    return searchbiggerequalthan(skey);
}

void btree::add_block(const std::string &filename)
{
    Block*t = m.getblock(filename, 0);
    (*reinterpret_cast<int*>(t->cblock + 8))++;
}
void btree::sub_block(const std::string &filename)
{
    Block*t = m.getblock(filename, 0);
    (*reinterpret_cast<int*>(t->cblock + 8))--;
}
std::string btree::getsmallestkey(Block*block)
{
    Block*pc = block;
    while (!pc->isleaf())
    {
        int pnext = *reinterpret_cast<int*>(pc->cblock + nonleafoff);
        pc = m.getblock(index.filename, pnext);
    }
    char *buf = new char[leafnodesize];
    memcpy(buf, pc->cblock + leafoff + 8, index.length);
    buf[index.length] = '\0';

    if (index.type == 2)
    {
        std::string ans(buf);
        delete buf;
        return ans;
    }
    else {
        string ans;
        ans.resize(4);
        ans[0] = buf[0];
        ans[1] = buf[1];
        ans[2] = buf[2];
        ans[3] = buf[3];
        delete buf;
        return ans;
    }
}

void btree::resetfather(Block*block, int fa)
{
    int cntp = block->get_record();//all ptr
    Block*tmp;
    for (int i = 0; i < cntp; i++)
    {
        int pointer = nonleafoff + i*nonleafnodesize;
        int blockoffset = *reinterpret_cast<int*>(block->cblock + pointer);
        tmp = m.getblock(index.filename, blockoffset);
        tmp->setfather(fa);
        tmp->isdirty = 1;
    }
}

int btree::getrootoffset()
{
    return proot;
}
void btree::updateroot(int ff)
{
    Block*info = m.getblock(index.filename, 0);
    *reinterpret_cast<int*>((info->cblock) + 4) = ff;
    info->isdirty = 1;
    proot = ff;
}

