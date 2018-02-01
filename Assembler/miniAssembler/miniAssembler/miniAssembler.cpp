#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;
map<string, int> unknowntable;
void Begin_transition(int Index, string Readin, string& Begining, ofstream& print_1, ofstream& print_2, int &i, int &NO_lines);
int HexadecimalOP(unsigned n, ofstream& out);
int HexadecimalOP1(unsigned n, ofstream& out);
int No_reg(string zhiling, int& Location);
int Search_real_num(string zhiling, int& Location);
int ifopreation(string name);
unsigned int MY_Rtype(int Index, string zhiling, int Location);
unsigned int Privilege(int Index, string zhiling, int Location);
unsigned int MY_Itype(int Index, string zhiling, int Location, int NO_lines);
unsigned int MY_Jtype(int Index, string zhiling, int Location);
string op_name[55] = {                                                                                 //Index sequence
    "lw", "lb", "lbu", "lh", "lhu", "sw", "sb", "sh", "add", "addu", "sub", "subu", "slt", "sltu",  //0-13
    "and", "or", "xor", "nor", "sll", "srl", "sra", "mult","multu", "div", "divu", "addi", "addiu", "andi", //14-27
    "ori", "xori", "lui", "slti", "sltiu", "beq", "bne", "blez", "bgtz", "bltz", "bgez","j","jal",  //28-40
    "jalr","jr", "mfhi", "mflo", "mthi", "mtlo", "eret", "mfc0", "mtc0", "break", "syscall", "la",  //41-52
    "move", "li"                                                                                    //53-54
};
string reg_name_1[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0",
    "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2",
    "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp",
    "sp", "fp", "ra"
};

string reg_name_2[32] = {
    "R0","R1","R2","R3", "R4", "R5", "R6", "R7", "R8","R9", "R10", "R11","R12","R13","R14","R15","R16","R17","R18","R19",
    "R20","R21","R22","R23","R24","R25","R26","R27","R28","R29","R30","R31"
};

string reg_name_3[32] = {
    "r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","r16","r17","r18","r19","r20",
    "r21","r22","r23","r24","r25","r26","r27","r28","r29","r30","r31"
};

unsigned int opvalue[52] = {
    0x23, 0x20, 0x24, 0x21, 0x25, 0x2B, 0x28, 0x29, 0x20, 0x21,//0-9
    0x22, 0x23, 0x2A, 0x2B, 0x24, 0x25, 0x26, 0x27, 0x00, 0x02,//10-19
    0x03, 0x18, 0x19, 0x1A, 0x1B, 0x08, 0x09, 0x0C, 0x0D, 0x0E,//20-29
    0x0F, 0x0A, 0x0B, 0x04, 0x05, 0x06, 0x07, 0x01, 0x01, 0x02,//30-39
    0x03, 0x09, 0x08, 0x10, 0x12, 0x11, 0x13, 0x18, 0x10, 0x10,//40-49
    0x0D, 0x0C                                                 //50-51
};



int main(int argc, const char * argv[])
{
    string Readin;
    string Begining;
    int i;
    int Index;
    int NO_lines = 0;
    ifstream scanin1("/Users/zhaoxuandong/Desktop/Project/Assembler/miniAssembler/miniAssembler/assembled.txt");
    ofstream print_1("/Users/zhaoxuandong/Desktop/Project/Assembler/miniAssembler/miniAssembler/machine.bin");
    ofstream print_2("/Users/zhaoxuandong/Desktop/Project/Assembler/miniAssembler/miniAssembler/machine.txt");
    if (!scanin1) {
        cout << "Unable to open the file" << endl;
        return 0;
    }
    while (getline(scanin1, Readin))
    {
        i = 0;
        while (Readin[i] == ' ' || Readin[i] == '\t' || Readin[i] == '\r' || Readin[i] == '\n')
            i++;
        if (Readin[i] == '#' || (Readin[i] == '/'&&Readin[i + 1] == '/'))
            continue;
        while ((Readin[i] >= 'a'&&Readin[i] <= 'z') || (Readin[i] >= 'A'&&Readin[i] <= 'Z') || Readin[i] == '.' || (Readin[i] >= '0'&&Readin[i] <= '9') || (Readin[i] == '_'))
        {
            Begining.append(&Readin[i], 1);
            i++;
        }
        if (ifopreation(Begining) == -1)
        {
            unknowntable[Begining] = NO_lines * 4;
            //NO_lines--;
        }
        Begining.clear();
        Readin.clear();
        NO_lines++;
    }
    scanin1.close();
    
    print_2 << "memory_initialization_radix=2;\nmemory_initialization_vector=\n";
    //	ifstream scanin2("/Users/apple/Desktop/assembler/assembled.txt");
    ifstream scanin2("/Users/zhaoxuandong/Desktop/Project/Assembler/miniAssembler/miniAssembler/assembled.txt");
    if (!scanin2) {
        cout << "Unable to open the file";
        exit(1);
    }
    Readin.clear();
    NO_lines = 0;
    while (getline(scanin2, Readin))
    {
        i = 0;
        while (Readin[i] == ' ' || Readin[i] == '\t')
            i++;
        if (Readin[i] == '#' || (Readin[i] == '/'&&Readin[i + 1] == '/'))
            continue;
        while ((Readin[i] >= 'a'&&Readin[i] <= 'z') || (Readin[i] >= 'A'&&Readin[i] <= 'Z') || Readin[i] == '.' || (Readin[i] >= '0'&&Readin[i] <= '9') || (Readin[i] == '_'))
        {
            Begining.append(&Readin[i], 1);
            i++;
        }
        if (ifopreation(Begining) == -1) {
            i++;
            //NO_lines--;
            Begining.clear();
            while ((Readin[i] == ' ') || (Readin[i] == '$') || (Readin[i] == ':'))
                i++;
            while ((Readin[i] >= 'a'&&Readin[i] <= 'z') || (Readin[i] >= 'A'&&Readin[i] <= 'Z') || Readin[i] == '.' || (Readin[i] >= '0'&&Readin[i] <= '9')) {
                Begining.append(&Readin[i], 1);
                i++;
            }
        }
        Index = ifopreation(Begining);
        Begin_transition(Index, Readin, Begining, print_1, print_2, i, NO_lines);
    }
    scanin2.close();
    print_1.close();
    print_2.close();
    return 0;
}

void Begin_transition(int Index, string Readin, string& Begining, ofstream& print_1, ofstream& print_2, int &i, int &NO_lines)
{
    Index = ifopreation(Begining);
    unsigned int instruction = 0, instruction1 = 0, instruction2 = 0, addr, opzhiling, imme;
    int rt;
    if ((Index >= 8 && Index <= 24) || (Index >= 41 && Index <= 46) || Index == 50 || Index == 51 || Index == 53) {
        instruction = MY_Rtype(Index, Readin, i);
        HexadecimalOP(instruction, print_1);
        HexadecimalOP1(instruction, print_2);
    }
    else if (Index >= 47 && Index <= 49) {
        instruction = Privilege(Index, Readin, i);
        HexadecimalOP(instruction, print_1);
        HexadecimalOP1(instruction, print_2);
    }
    else if ((Index >= 0 && Index <= 7) || (Index >= 25 && Index <= 38)) {
        instruction = MY_Itype(Index, Readin, i, NO_lines);
        HexadecimalOP(instruction, print_1);
        HexadecimalOP1(instruction, print_2);
    }
    else if (Index == 39 || Index == 40) {
        instruction = MY_Jtype(Index, Readin, i);
        HexadecimalOP(instruction, print_1);
        HexadecimalOP1(instruction, print_2);
    }
    else if (Index == 52) {//la
        rt = No_reg(Readin, i);
        string flag;
        while (Readin[i] == '\t' || Readin[i] == ' ')
            i++;
        while ((Readin[i] >= '0'&&Readin[i] <= '9') || (Readin[i] >= 'a'&&Readin[i] <= 'z') || (Readin[i] >= 'A'&&Readin[i] <= 'Z') || Readin[i] == '.') {
            flag.append(&Readin[i], 1);
            i++;
        }
        addr = unknowntable[flag];
        
        imme = addr >> 16;
        opzhiling = opvalue[30];
        instruction1 |= imme;
        instruction1 |= rt << 16;
        instruction1 |= opzhiling << 26;
        HexadecimalOP(instruction1, print_1);
        HexadecimalOP1(instruction1, print_2);
        
        opzhiling = opvalue[28];
        imme = addr & 0xFFFF;
        instruction2 |= imme;
        instruction2 |= rt << 16;
        instruction2 |= rt << 21;
        instruction2 |= opzhiling << 26;
        HexadecimalOP(instruction2, print_1);
        HexadecimalOP1(instruction2, print_2);
    }
    else if (Index == 54) {//li
        rt = No_reg(Readin, i);
        addr = Search_real_num(Readin, i);
        
        imme = addr >> 16;
        opzhiling = opvalue[30];
        instruction1 |= imme;
        instruction1 |= rt << 16;
        instruction1 |= opzhiling << 26;
        HexadecimalOP(instruction1, print_1);
        HexadecimalOP1(instruction1, print_2);
        
        opzhiling = opvalue[28];
        imme = addr & 0xFFFF;
        instruction2 |= imme;
        instruction2 |= rt << 16;
        instruction2 |= rt << 21;
        instruction2 |= opzhiling << 26;
        HexadecimalOP(instruction2, print_1);
        HexadecimalOP1(instruction2, print_2);
    }
    Begining.clear();
    NO_lines++;
}
int HexadecimalOP(unsigned n, ofstream& out)
{
    int a[100] = { 32 };
    int yushu, i = 0, m = 0;
    char hex[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
    while (n>0)
    {
        yushu = n % 16;
        a[i++] = yushu;
        n = n / 16;
    }
    for (i = 7; i >= 0; i--)
    {
        m = a[i];
        if (m == 32)
        {
            out << 0;
        }
        out << hex[m];
        
    }
    out << "," << endl;
    return 0;
}
int HexadecimalOP1(unsigned n, ofstream& out)
{
    int a[100] = { 32 };
    int yushu, i = 0, m = 0;
    char hex[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
    while (n>0)
    {
        yushu = n % 16;
        a[i++] = yushu;
        n = n / 16;
    }
    for (i = 7; i >= 0; i--)
    {
        m = a[i];
        if (m == 32)
            out << 0;
        out << hex[m];
        
    }
    out << "," << endl;
    return 0;
}
int ifopreation(string name)
{
    int i;
    for (i = 0; i<55; i++)
        if (name == op_name[i])
            return i;
    return -1;
}

int No_reg(string zhiling, int& Location)
{
    string reg;
    while (zhiling[Location] == '\t' || zhiling[Location] == ' ' || zhiling[Location] == '$' || zhiling[Location] == ',' || zhiling[Location] == '(' || zhiling[Location] == ')')
        Location++;
    while ((zhiling[Location] >= '0'&&zhiling[Location] <= '9') || (zhiling[Location] >= 'a'&&zhiling[Location] <= 'z') || (zhiling[Location] >= 'A'&&zhiling[Location] <= 'Z')) {
        reg.append(&zhiling[Location], 1);
        Location++;
    }
    for (int i = 0; i<32; i++)
    {
        if (reg == reg_name_1[i] || reg == reg_name_2[i] || reg == reg_name_3[i])
            return i;
    }
    return -1;
}

int Search_real_num(string zhiling, int& Location) {
    int num = 0;
    int flag = 0;//judge if it is negative
    while (zhiling[Location] == '\t' || zhiling[Location] == ' ' || zhiling[Location] == '$' || zhiling[Location] == ',' || zhiling[Location] == '(' || zhiling[Location] == ')')
        Location++;
    if (zhiling[Location] == '-') {
        flag = 1;
        Location++;
    }
    //if the input num is Hexadecimal.
    if (zhiling[Location] == '0'&&zhiling[Location + 1] == 'x')
    {
        Location += 2;
        int dangqian = 0;
        for (int i = 0; i<4; i++)
        {
            if (zhiling[Location] >= 'a'&&zhiling[Location] <= 'f')
                dangqian = 10 + zhiling[Location] - 'a';
            else dangqian = zhiling[Location] - '0';
            num = num * 16 + dangqian;
            Location++;
        }
        return num;
    }
    while (zhiling[Location] >= '0'&&zhiling[Location] <= '9') {
        num = num * 10 + zhiling[Location] - '0';
        Location++;
    }
    if (flag == 1)
        return (-1)*num;
    return num;
}

unsigned int MY_Rtype(int Index, string zhiling, int Location) {//all opzhiling is 0
    string operation = op_name[Index];
    unsigned int opzhiling, opfunc, instruction = 0;
    int rs, rd, rt, sa;
    opzhiling = 0;
    opfunc = opvalue[Index];
    instruction |= opfunc;
    if (Index >= 8 && Index <= 17) {
        rd = No_reg(zhiling, Location);
        rs = No_reg(zhiling, Location);
        rt = No_reg(zhiling, Location);
        instruction |= rd << 11;
        instruction |= rt << 16;
        instruction |= rs << 21;
    }
    else if (Index >= 18 && Index <= 20) {
        rd = No_reg(zhiling, Location);
        rt = No_reg(zhiling, Location);
        sa = Search_real_num(zhiling, Location);
        sa &= 0x0000FFFF;
        instruction |= sa << 6;
        instruction |= rd << 11;
        instruction |= rt << 16;
    }
    else if (Index >= 21 && Index <= 24) {
        rs = No_reg(zhiling, Location);
        rt = No_reg(zhiling, Location);
        instruction |= rt << 16;
        instruction |= rs << 21;
    }
    else if (Index == 41) {//jalr
        rd = No_reg(zhiling, Location);
        rs = No_reg(zhiling, Location);
        if (rs == -1) {
            rs = rd;
            rd = 31;
        }
        instruction |= rd << 11;
        instruction |= rs << 21;
    }
    else if (Index == 53) {//move
        rd = No_reg(zhiling, Location);
        rs = No_reg(zhiling, Location);
        cout << rd << endl;
        cout << rs << endl;
        opfunc = 0x20;
        instruction |= opfunc;
        instruction |= rd << 11;
        instruction |= rs << 21;
    }
    else if (Index == 42 || Index == 45 || Index == 46) {//jr,mthi,mtlo
        rs = No_reg(zhiling, Location);
        instruction |= rs << 21;
    }
    else if (Index == 43 || Index == 44) {
        rs = No_reg(zhiling, Location);
        instruction |= rs << 11;
    }
    else if (Index == 50 || Index == 51) {//break,syscall
    }
    return instruction;
}

unsigned int Privilege(int Index, string zhiling, int Location) {
    unsigned int opzhiling, opfunc, instruction = 0;
    int rd, rt;
    opzhiling = 0x10;
    if (Index == 47) {//eret
        opfunc = opvalue[Index];
        instruction |= opfunc;
        instruction |= 1 << 25;
        instruction |= opzhiling << 26;
    }
    else if (Index == 48) {//mfc0
        rt = No_reg(zhiling, Location);
        rd = No_reg(zhiling, Location);
        instruction |= rd << 11;
        instruction |= rt << 16;
        instruction |= opzhiling << 26;
    }
    else if (Index == 49) {//mtc0
        rt = No_reg(zhiling, Location);
        rd = No_reg(zhiling, Location);
        instruction |= rd << 11;
        instruction |= rt << 16;
        instruction |= 4 << 21;
        instruction |= opzhiling << 26;
    }
    return instruction;
}

unsigned int MY_Itype(int Index, string zhiling, int Location, int NO_lines) {
    unsigned int opzhiling, instruction = 0;
    string flag;
    opzhiling = opvalue[Index];
    int rt, rs, base, offset, imme;
    if (Index >= 0 && Index <= 7) {
        rt = No_reg(zhiling, Location);
        offset = Search_real_num(zhiling, Location);
        base = No_reg(zhiling, Location);
        offset &= 0x0000FFFF;
        instruction |= offset;
        instruction |= rt << 16;
        instruction |= base << 21;
        instruction |= opzhiling << 26;
    }
    else if (Index >= 25 && Index <= 32 && Index != 30) {
        rt = No_reg(zhiling, Location);
        rs = No_reg(zhiling, Location);
        imme = Search_real_num(zhiling, Location);
        imme &= 0x0000FFFF;
        instruction |= imme;
        instruction |= rt << 16;
        instruction |= rs << 21;
        instruction |= opzhiling << 26;
    }
    else if (Index == 30) {
        rt = No_reg(zhiling, Location);
        imme = Search_real_num(zhiling, Location);
        imme &= 0x0000FFFF;
        instruction |= imme;
        instruction |= rt << 16;
        instruction |= opzhiling << 26;
    }
    else if (Index >= 33 && Index <= 34) {
        //beq
        rs = No_reg(zhiling, Location);
        rt = No_reg(zhiling, Location);
        offset = Search_real_num(zhiling, Location);
        if (offset == 0) {
            while (zhiling[Location] == '\t' || zhiling[Location] == ' ')
                Location++;
            while ((zhiling[Location] >= '0'&&zhiling[Location] <= '9') || (zhiling[Location] >= 'a'&&zhiling[Location] <= 'z') || (zhiling[Location] >= 'A'&&zhiling[Location] <= 'Z') || zhiling[Location] == '.' || zhiling[Location] == '_')
            {
                flag.append(&zhiling[Location], 1);
                Location++;
            }
            offset = unknowntable[flag];
        }
        offset = offset - NO_lines * 4 - 4;
        offset = offset >> 2;
        offset &= 0x0000FFFF;
        instruction |= offset;
        instruction |= rt << 16;
        instruction |= rs << 21;
        instruction |= opzhiling << 26;
    }
    else if (Index >= 35 && Index <= 37) {
        rs = No_reg(zhiling, Location);
        offset = Search_real_num(zhiling, Location);
        if (offset == 0) {
            while (zhiling[Location] == '\t' || zhiling[Location] == ' ')
                Location++;
            while ((zhiling[Location] >= '0'&&zhiling[Location] <= '9') || (zhiling[Location] >= 'a'&&zhiling[Location] <= 'z') || (zhiling[Location] >= 'A'&&zhiling[Location] <= 'Z') || zhiling[Location] == '.' || zhiling[Location] == '_') {
                flag.append(&zhiling[Location], 1);
                Location++;
            }
            offset = unknowntable[flag];
        }
        offset = offset - NO_lines * 4;
        offset = offset >> 2;
        offset &= 0x0000FFFF;
        instruction |= offset;
        instruction |= rs << 21;
        instruction |= opzhiling << 26;
    }
    else if (Index == 38) {
        rs = No_reg(zhiling, Location);
        offset = Search_real_num(zhiling, Location);
        if (offset == 0) {
            while (zhiling[Location] == '\t' || zhiling[Location] == ' ')
                Location++;
            while ((zhiling[Location] >= '0'&&zhiling[Location] <= '9') || (zhiling[Location] >= 'a'&&zhiling[Location] <= 'z') || (zhiling[Location] >= 'A'&&zhiling[Location] <= 'Z') || zhiling[Location] == '.' || zhiling[Location] == '_')
            {
                flag.append(&zhiling[Location], 1);
                Location++;
            }
            offset = unknowntable[flag];
        }
        offset = offset - NO_lines * 4;
        offset = offset >> 2;
        offset &= 0x0000FFFF;
        instruction |= offset;
        instruction |= 1 << 16;
        instruction |= rs << 21;
        instruction |= opzhiling << 26;
    }
    return instruction;
}

unsigned int MY_Jtype(int Index, string zhiling, int Location) {
    unsigned int target, instruction = 0, opzhiling;
    string flag;
    opzhiling = opvalue[Index];
    target = Search_real_num(zhiling, Location);
    if (target == 0) {
        while (zhiling[Location] == '\t' || zhiling[Location] == ' ')
            Location++;
        while ((zhiling[Location] >= '0'&&zhiling[Location] <= '9') || (zhiling[Location] >= 'a'&&zhiling[Location] <= 'z') || (zhiling[Location] >= 'A'&&zhiling[Location] <= 'Z') || zhiling[Location] == '.' || zhiling[Location] == '_' || zhiling[Location] == ':')
        {
            flag.append(&zhiling[Location], 1);
            Location++;
        }
        target = unknowntable[flag];
    }
    target = target >> 2;
    instruction |= target;
    instruction |= opzhiling << 26;
    return instruction;
}

