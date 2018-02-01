#include <stdio.h>
#include <string.h>

#define MAXM 50
#define MAXP 1000
typedef unsigned int DWORD;
int lablef[MAXP] = { 0 };
int lines = 0;
//---------------------寄存器名字-----------------//
char registername[50][50] = {
    "$zero",//0
    "$at",//1
    "$v0",//2-3
    "$v1",
    "$a0",//4-7
    "$a1",
    "$a2",
    "$a3",
    "$t0",//8-15
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$s0",//16-23
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t8",//24-25
    "$t9",
    "$k0",//26-27
    "$k1",
    "$gp",//28
    "$sp",//29
    "$fp",//30
    "$ra"	//31
};
//-----------------------寄存器查询--------------//
int referregister(char * name) {
    int i;
    int flag = 0;
    for (i = 0; i<32; i++) {
        if (!strcmp(registername[i], name)) {
            return i;
        }
    }
    if (!flag) {
        return -1;
    }
    return 0;
}

//--------------------指令结构定义----------------//
struct operation {
    int operationtype;//1-R ; 2-I ; 3-J ; 4 - C
    char operationname[MAXM];
    int opcode;
    int functioncode;
    int shamt;
    int ID;
};
typedef struct operation OPA;
OPA operationList[MAXM];
int OPAlen = 0;
struct realoperation {
    int realtype;//operation type 对应的下标
    int rd;
    int rs;
    int rt;
    int imme;
    int adr;
};
typedef struct realoperation ROP;
ROP ERRORROP;
OPA ERROROPA;
//-------------------增加一条指令-------------------//
void addoneOPA(int operationtype, char * operationname, int opcode, int functioncode, int shamt) {
    operationList[OPAlen].operationtype = operationtype;
    operationList[OPAlen].opcode = opcode;
    operationList[OPAlen].functioncode = functioncode;
    operationList[OPAlen].shamt = shamt;
    operationList[OPAlen].ID = OPAlen;
    strcpy(operationList[OPAlen].operationname, operationname);
    OPAlen += 1;
}
OPA getoneOPA(int ID) {
    if (ID >= 0 && ID<OPAlen) {
        return operationList[ID];
    }
    else {
        return ERROROPA;
    }
    
}
//-------------------初始化MIPS指令集数据----------------//

void initOPA() {
    OPAlen = 0;
    ERRORROP.realtype = -1;
    ERROROPA.operationtype = -1;
    //1-R ; 2-I ; 3-J ; 4 - C
    //Type,Name,OPCODE ,FCODE,SHAMT
    
    addoneOPA(2, "lw", 35, 0, 0);  //1-------8
    addoneOPA(2, "lb", 32, 0, 0);
    addoneOPA(2, "lbu", 36, 0, 0);
    addoneOPA(2, "lh", 33, 0, 0);
    addoneOPA(2, "lhu", 37, 0, 0);
    addoneOPA(2, "sw", 43, 0, 0);
    addoneOPA(2, "sb", 40, 0, 0);
    addoneOPA(2, "sh", 41, 0, 0);
    
    addoneOPA(1, "add", 0, 32, 0);   //9-----18
    addoneOPA(1, "addu", 0, 33, 0);
    addoneOPA(1, "sub", 0, 34, 0);
    addoneOPA(1, "subu", 0, 35, 0);
    addoneOPA(1, "and", 0, 36, 0);
    addoneOPA(1, "or", 0, 37, 0);
    addoneOPA(1, "xor", 0, 38, 0);
    addoneOPA(1, "nor", 0, 39, 0);
    addoneOPA(1, "slt", 0, 42, 0);
    addoneOPA(1, "sltu", 0, 43, 0);
    
    addoneOPA(1, "sll", 0, 0, 0);   //19----21
    addoneOPA(1, "srl", 0, 2, 0);
    addoneOPA(1, "sra", 0, 3, 0);
    
    addoneOPA(2, "addi", 8, 0, 0);   // 26------33
    addoneOPA(2, "addiu", 9, 0, 0);
    addoneOPA(2, "andi", 12, 0, 0);
    addoneOPA(2, "ori", 13, 0, 0);
    addoneOPA(2, "xori", 14, 0, 0);
    addoneOPA(2, "lui", 15, 0, 0);
    addoneOPA(2, "slti", 10, 0, 0);
    addoneOPA(2, "sltiu", 11, 0, 0);
    
    addoneOPA(2, "beq", 4, 0, 0);  //34
    addoneOPA(2, "bne", 5, 0, 0);  //35
    
    addoneOPA(2, "blez", 6, 0, 0);//36-----39
    addoneOPA(2, "bgtz", 7, 0, 0);
    addoneOPA(2, "bltz", 1, 0, 0);
    addoneOPA(2, "bgez", 1, 0, 0);
    
    addoneOPA(3, "j", 2, 0, 0);    //40
    addoneOPA(3, "jal", 3, 0, 0);   //41
    
    addoneOPA(1, "jalr", 0, 9, 0);   //42
    
    addoneOPA(1, "jr", 0, 8, 0);    //43
}
//-----------------解析R型32位机器码----------------------//
ROP parseR_DWORD(DWORD a)
{
    int opcode = (a >> 26) & 0x3F;  // 0
    int shamt = (a >> 6) & 0x1F;	   // 0
    int functioncode = a & 0x3F;
    ROP resultROP;
    resultROP.rs = (a >> 21) & 0x1F;
    resultROP.rt = (a >> 16) & 0x1F;
    resultROP.rd = (a >> 11) & 0x1F;
    resultROP.imme = 0;
    resultROP.adr = 0;
    resultROP.realtype = -1;
    if (opcode == 0 && shamt == 0)
    {
        //确定realtype;
        for (int i = 0; i<OPAlen; i++)
        {
            if ((operationList[i].operationtype == 1) && (operationList[i].functioncode == functioncode))
            {
                resultROP.realtype = i;
                break;
            }
        }
        if (resultROP.realtype == -1)
        {
            //未找到指令
            return ERRORROP;
        }
        else
        {
            return resultROP;
        }
    }
    else
    {
        //不是R型指令
        return ERRORROP;
    }
}
//-----------------解析R型32位机器码----------------------//
ROP parseI_DWORD(DWORD a)
{
    int opcode = (a >> 26) & 0x3F;  // 0
    ROP resultROP;
    resultROP.rs = (a >> 21) & 0x1F;
    resultROP.rt = (a >> 16) & 0x1F;
    resultROP.rd = 0;
    resultROP.imme = a & 0xFFFF;
    resultROP.adr = 0;
    resultROP.realtype = -1;
    //确定realtype;
    for (int i = 0; i<OPAlen; i++)
    {
        if ((operationList[i].operationtype == 2) && (operationList[i].opcode == opcode))
        {
            if (operationList[i].opcode == 1)
            {
                if (resultROP.rt == 1)
                {
                    resultROP.realtype = 38;
                    break;
                }
                if (resultROP.rt == 0)
                {
                    resultROP.realtype = 37;
                    break;
                }
            }
            resultROP.realtype = i;
            break;
        }
    }
    if (resultROP.realtype == -1) {
        //未找到指令
        return ERRORROP;
    }
    else {
        return resultROP;
    }
    
}
//-----------------解析R型32位机器码----------------------//
ROP parseJ_DWORD(DWORD a)
{
    int opcode = (a >> 26) & 0x3F;  // 0
    ROP resultROP;
    resultROP.rs = 0;
    resultROP.rt = 0;
    resultROP.rd = 0;
    resultROP.imme = 0;
    resultROP.adr = a & 0x3FFFFFF;
    resultROP.realtype = -1;
    //确定realtype;
    for (int i = 0; i<OPAlen; i++)
    {
        if ((operationList[i].operationtype == 3) && (operationList[i].opcode == opcode)) {
            resultROP.realtype = i;
            break;
        }
    }
    if (resultROP.realtype == -1) {
        //未找到指令
        return ERRORROP;
    }
    else {
        return resultROP;
    }
}
//-----------------解析R型32位机器码----------------------//
ROP parseC_DWORD(DWORD a)
{
    
    return ERRORROP;
}
//-----------------解析32位机器码----主分配函数----------------------//
ROP parseDWORD(DWORD a) {
    ROP resultROP[4];
    resultROP[0] = parseR_DWORD(a);
    resultROP[1] = parseI_DWORD(a);
    resultROP[2] = parseJ_DWORD(a);
    resultROP[3] = parseC_DWORD(a);
    for (int i = 0; i <= 3; i++) {
        if (resultROP[i].realtype != -1) {
            return resultROP[i];
        }
    }
    return ERRORROP;
    
}
//---------------字符串转Dword-----------------//
DWORD str2dword(char *str) {
    int mode = 1;//0 为 二进制模式，1 为十六进制模式。
    int len = strlen(str);
    DWORD result;
    if (mode) {
        sscanf(str, "%X", &result);
    }
    else {
        result = 0;
        for (int i = 0; i<len; i++) {
            result = (result << 1) | (str[i] - '0');
            if (i >= 31) {
                break;
            }
        }
    }
    return result;
}
//---------------二进制打印--------------------//
void printDWORD(DWORD a)
{
    int mode = 0;//十六进制打印为1，二进制打印为0.
    if (mode) {
        for (int i = 7; i >= 0; i--) {
            printf("%X", (a >> i * 4) & 0xF);
        }
    }
    else {
        for (int i = 31; i >= 0; i--) {
            printf("%d", (a >> i) & 1);
        }
        
    }
    printf("\n");
}
void printOP(ROP a)
{
    int dizhi;
    if (a.realtype == -1)
    {
        printf("ERRORROP\n");
        return;
    }
    if (lablef[lines]!=0)
        printf("Lable_%d :", lines);
    OPA thisOPA = getoneOPA(a.realtype);
    printf("%s ", thisOPA.operationname);
    switch (thisOPA.operationtype)
    {
        case 1:
            if ((!strcmp(thisOPA.operationname, "jr")))
            {
                printf("%s", registername[a.rs]);
            }
            else { printf("%s,%s,%s", registername[a.rd], registername[a.rs], registername[a.rt]); }
            break;
        case 2:
            if ((!strcmp(thisOPA.operationname, "beq")) || (!strcmp(thisOPA.operationname, "bne")))
            {
                //如果是BEQ
                dizhi = lines + 1 + a.imme;
                printf("%s,%s,Lable_%d", registername[a.rs], registername[a.rt], dizhi);
                lablef[dizhi] = 1;
            }
            else if(!strcmp(thisOPA.operationname, "lui"))
            {
                printf("%s,%d", registername[a.rt], a.imme);
            }
            else if((!strcmp(thisOPA.operationname, "addi"))||(!strcmp(thisOPA.operationname, "ori")))
            {
                printf("%s,%s,%d", registername[a.rt], registername[a.rs], a.imme);
            }
            else
            {   if(a.imme == 0)
                printf("%s,(%s)", registername[a.rt], registername[a.rs]);
            else printf("%s,%d(%s)", registername[a.rt], a.imme, registername[a.rs]);
            }
            break;
        case 3:
            printf("Lable_%d", a.adr);
            lablef[a.adr] = 1;
            break;
        case 4:
            
            break;
    }
    printf(";\n");
    
}
void printOP1(ROP a)
{
    int dizhi;
    if (a.realtype == -1)
    {
        printf("ERRORROP\n");
        return;
    }
    OPA thisOPA = getoneOPA(a.realtype);
    switch (thisOPA.operationtype)
    {
        case 1:
            break;
        case 2:
            if ((!strcmp(thisOPA.operationname, "beq")) || (!strcmp(thisOPA.operationname, "bne")))
            {
                //如果是BEQ
                dizhi = lines + 1 + a.imme;
                lablef[dizhi] = 1;
            }
            
            break;
        case 3:
            lablef[a.adr] = 1;
            break;
        case 4:
            
            break;
    }
    
}
void printINFO(ROP a) {
    if (a.realtype == -1) {
        printf("ERRORROP\n");
        return;
    }
    OPA thisOPA = getoneOPA(a.realtype);
    printf("\n------INFO------\n");
    printf("Name:%s\n", thisOPA.operationname);
    printf("FunctionCode:%d\n", thisOPA.functioncode);
    printf("opcode:%d\n", thisOPA.opcode);
    printf("operationtype:%d\n", thisOPA.operationtype);
    printf("shamt:%d\n", thisOPA.shamt);
    printf("rd:%d\t Regname:%s\n", a.rd, registername[a.rd]);
    printf("rs:%d\t Regname:%s\n", a.rs, registername[a.rs]);
    printf("rt:%d\t Regname:%s\n", a.rt, registername[a.rt]);
    printf("imme:%d\n", a.imme);
    printf("adr:%d\n", a.adr);
    
    printf("\n----END--INFO------\n");
    
    
}
int main() {
    initOPA();
    char operationline[MAXM];
    int filemode = 1;
    int maxOperation = 1000;
    int now = 0;
    freopen("/Users/zhaoxuandong/Desktop/Project/Assembler/miniDisAssembler/miniDisAssembler/machine.txt", "r", stdin);
    while (1) 
    {
        now++;
        if (now >= maxOperation) {
            break;
        }
        gets(operationline);
        if (!strcmp(operationline, "###")) {
            break;
        }
        
        ROP myROP;
        DWORD myword;
        myword = str2dword(operationline);
        
        myROP = parseDWORD(myword);
        if (myROP.realtype == -1) {
            printf("This operation is not valid.\n");
        }
        else {
            printOP1(myROP);
            lines++;
            
        }
        
        
    }
    lines = 0;
    filemode = 0;
    maxOperation = 1000;
    now = 0;
   	freopen("/Users/zhaoxuandong/Desktop/Project/Assembler/miniDisAssembler/miniDisAssembler/machine.txt", "r", stdin);
    freopen("/Users/zhaoxuandong/Desktop/Project/Assembler/miniDisAssembler/miniDisAssembler/assembled.txt", "w", stdout);
    filemode = 1;
    while (1)
    {
        now++;
        if (now >= maxOperation) {
            break;
        }
        gets(operationline);
        if (!strcmp(operationline, "###")) {
            break;
        }
        ROP myROP;
        DWORD myword;
        myword = str2dword(operationline);
        
        myROP = parseDWORD(myword);
        if (myROP.realtype == -1) {
            printf("This operation is not valid.\n");
        }
        else {
            
            if (!filemode)printINFO(myROP);
            //myword=ROP2DWORD(myROP);
            
            if (!filemode)printf("Operation:\n");
            //printDWORD(myword);
            printOP(myROP);
            lines++;
            
        }
        
        
    }
    
}
