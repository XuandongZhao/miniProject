#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <cstdio>
#include <cstdlib>

class label{
public:
    std::string name;
    int addr;
};
class variable{
public:
    int *value;
    int len;
};

class assembler{
private:
    label globalLabel[1000];
    int labelNumber;
    variable globalVariable[1000];
    int variableNumber;
    int firstSearch(std::string);
    int finalAssmemble(std::string);
public:
    int *binaryProgram;
    int programLen;

    assembler();
    ~assembler();
    int run(int,char**);
    int assemble(std::string);
    std::string output();
};

#endif // ASSEMBLER_H
