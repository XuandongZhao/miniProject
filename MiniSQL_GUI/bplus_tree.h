#pragma once
#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H
#define _mydug

#include "buffmanage.h"
#include <string>
#include <iostream>
#include <utility>
#include <cassert>
#include <utility>

extern BufferManager m;
class indexinfo {
public:
    std::string filename;
    keytype type;
    int length;
    indexinfo(std::string fname, keytype ktype, int keylen) :filename(fname), type(ktype), length(keylen) {}
    ~indexinfo() = default;
};



class btree {
public:
    typedef std::pair<int, int>PII;
    int leaf_least;
    int leaf_most;
    int order_least;
    int nonleaf_most;
    int leafnodesize;
    int nonleafnodesize;
    int order;
    int proot;
    //BufferManager m;
    indexinfo index;

    bool compless(const std::string& x, const std::string& y);
    bool complessequal(const std::string& x, const std::string& y);
    bool compbig(const std::string& x, const std::string& y);
    bool compbigequal(const std::string& x, const std::string& y);
    char* fkey(const std::string&);

    int getrootoffset();
    void updateroot(int ff);
    void add_block(const std::string & filename);
    void sub_block(const std::string & filename);
    std::string getsmallestkey(Block*);
    void resetfather(Block*, int fa);
    void updatefather(int fa, const std::string&key, const std::string& rep);
    bool deleteinparent(int, const std::string&);
    void insertinparentc(Block*, int pos, int pointer, const std::string &key);
public:
    btree(const indexinfo&, int);

    ~btree()=default;
    void insert(std::string key, int blockoffset, int offset);
    void insertinleaf(int, Block*, const std::string&key, int blocknum, int offset);
    void insertinparent(int, std::string, int);
    void deleteonerecord(std::string key);
    std::pair<int, int> bsearch(std::string key, Block*);//return blocknum offset
    std::pair<int, int>searchequal(const std::string& key);
    std::vector<std::pair<int, int>>searchbetween(const std::string& key1, const std::string &key2);
    std::vector<std::pair<int, int>>searchlessthan(const std::string&key);
    std::vector<std::pair<int, int>>searchlessequalthan(const std::string&key);
    std::vector<std::pair<int, int>>searchbiggerthan(const std::string&key);
    std::vector<std::pair<int, int>>searchbiggerequalthan(const std::string&key);
    std::vector<std::pair<int, int>>searchall();
};
//info xxxx   xxxx  xxxx
//     type   root  cnt
//255/
// xxxx +  xxxx  + xxxx +                 xxxx + ....
// isleaf  count   father  + left   right  pointer key
// xxxx  + xxxx  + xxxx    + xxxx +  xxxx + blocknum+ blockoffset +key
//isleaf   count +  father + left   right + 8 + len
//4*5=20

#endif // BPLUS_TREE_H
