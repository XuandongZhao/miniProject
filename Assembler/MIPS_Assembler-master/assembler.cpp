#include "assembler.h"

assembler::assembler()
{
    variableNumber=0;
    labelNumber=0;
    programLen=0;
}

assembler::~assembler()
{

}

int assembler::firstSearch(std::string file){
    for (int i=0;;i++){

    }
    return 0;
}

int assembler::finalAssmemble(std::string file){

    return 0;
}

int assembler::assemble(std::string file){

    return 0;
}

std::string assembler::output(){
    std::string temp("");
    for (int i=0;i<programLen;i++) temp.append(1,(char)(*(binaryProgram+i)));
    return temp;
}

int assembler::run(int argc,char **argv){
    return 0;
}
