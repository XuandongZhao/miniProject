#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

map<string, int> labels;
const int LineLength = 256;

int getLabelI(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ':') {
            return i + 1;
        }
    }
    return 0;
}

string getInstruction(char *str, int start) {
    string re = "";
    int len = strlen(str);
    bool first = true;
    for (int i = start; i < len; i++) {
        if (str[i] == ';') break;
        if (!first || str[i] != ' ') {
            re += str[i];
            first = false;
        }
    }
    return re;
}

string getLabel(char *str, int end) {
    string re = "";
    for (int i = 0; i < end; i++) {
        if (str[i] == ':') break;
        if (str[i] != ' ') re += str[i];
    }
    return re;
}

string tenToTwo(int num, int size) {
    string result = "";
    for (int i = size - 1; i >= 0; i--) {
        result += (num >> i & 1 ? '1' : '0');
    }
    return result;
}

string typeR(const string & str, int start) {
    string num[3];
    int k = start;
    for (int i = 0; i < 3; i++) {
        num[i] = "";
        while (str[k++] != '$') ; // do nothing
        while (str[k] >= '0' && str[k] <= '9') num[i] += str[k++];
        num[i] = tenToTwo(atoi(num[i].c_str()), 5);
    }
    return num[1] + num[2] + num[0] + "00000000000";
}

string typeI(const string & str, int start, bool normal) {
    string num[3];
    int k = start, i = 0;
    for (i = 0; i < 2; i++) {
        num[i] = "";
        while (str[k++] != '$') ; // do nothing
        while (str[k] >= '0' && str[k] <= '9') num[i] += str[k++];
        num[i] = tenToTwo(atoi(num[i].c_str()), 5);
    }
    while (!(str[k] >= '0' && str[k] <= '9') && str[k] != '-') k++;
    while ((str[k] >= '0' && str[k] <= '9') || str[k] == '-') num[2] += str[k++];
    num[2] = tenToTwo(atoi(num[2].c_str()), 16);
    if (normal) return num[1] + num[0] + num[2];
    else return num[0] + num[1] + num[2];
}

string typeJ(const string & str, int start) {
    string thisLabel = "";
    for (int i = start; i < str.size(); i++) {
        if (str[i] != ' ') thisLabel += str[i];
    }
    return tenToTwo(labels.find(thisLabel)->second, 26);
}

string jrInst(const string & str, int start) {
    int k = start;
    while (str[k++] != '$') ; // do nothing
    string num = "";
    while (str[k] >= '0' && str[k] <= '9') num += str[k++];
    return tenToTwo(atoi(num.c_str()), 5) + "000000000000000000000";
}

string sllInst(const string & str, int start) {
    string num[3];
    int k = start, i = 0;
    for (i = 0; i < 2; i++) {
        num[i] = "";
        while (str[k++] != '$') ; // do nothing
        while (str[k] >= '0' && str[k] <= '9') num[i] += str[k++];
        num[i] = tenToTwo(atoi(num[i].c_str()), 5);
    }
    while (!(str[k] >= '0' && str[k] <= '9')) k++;
    while (str[k] >= '0' && str[k] <= '9') num[2] += str[k++];
    num[2] = tenToTwo(atoi(num[2].c_str()), 5);
    return num[1] + "00000" + num[0] + num[2] + "000000";
}

string lswInst(const string & str, int start) {
    string num[3];
    int k = start;
    while (str[k++] != '$') ; // do nothing
    while (str[k] >= '0' && str[k] <= '9') num[0] += str[k++];
    
    while (!(str[k] >= '0' && str[k] <= '9') && str[k] != '-') k++;
    while ((str[k] >= '0' && str[k] <= '9') || str[k] == '-') num[1] += str[k++];
    
    while (str[k++] != '$') ; // do nothing
    while (str[k] >= '0' && str[k] <= '9') num[2] += str[k++];
    
    return tenToTwo(atoi(num[2].c_str()), 5) + tenToTwo(atoi(num[0].c_str()), 5) + tenToTwo(atoi(num[1].c_str()), 16);
}

int main() {
    char buffer[LineLength];

    string inputFileName, outputFileName;
    cout << "==>Please input the input file name: ";
    cin >> inputFileName;
    cout << "==>Please input the output file name: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName.c_str());
    ofstream outputFile(outputFileName.c_str());
    if (!inputFile) {
        cout << "Can't open " + inputFileName + "." << endl;
        getchar(); getchar();
        return -1;
    }
    if (!outputFile) {
        cout << "Can't find " + outputFileName + "." << endl;
        getchar(); getchar();
        return -1;
    }
    
    int pc = 0;
    cout << "==>Please enter the start PC value, if not four integer times will be automatically converted into four integer times: ";
    cin >> pc;
    pc /= 4;
    
    int instruction_i = 0; // 确定当前指令是第几条
    int label_i; // 纪录label的: 在第几个位置 + 1
    vector<string> instructions;
    // 读取所有的指令并且确定指令以及label(使用一个map确定)加入到一个vector中
    while (!inputFile.eof()) {
        inputFile.getline(buffer, LineLength);
        label_i = getLabelI(buffer);
        string inst = getInstruction(buffer, label_i);
        if (inst != "") instructions.push_back(inst);
        else continue;
        string label = getLabel(buffer, label_i);
        if (label != "") labels.insert(pair<string, int>(label, instruction_i + pc));
        instruction_i++;
    }
    
    // 分情况解析指令
    string inst;
    int end;
    string rs, rt, rd, immediate, sa, addr;
    for (int i = 0; i < instructions.size(); i++) {
        inst = instructions[i].substr(0, instructions[i].find(' '));
        if (inst == "add") {
            outputFile << "000000" + typeR(instructions[i], 4);
        } else if (inst == "sub") {
            outputFile << "000001" + typeR(instructions[i], 4);
        } else if (inst == "addi") {
            outputFile << "000010" + typeI(instructions[i], 5, true);
        } else if (inst == "or") {
            outputFile << "010000" + typeR(instructions[i], 3);
        } else if (inst == "and") {
            outputFile << "010001" + typeR(instructions[i], 4);
        } else if (inst == "ori") {
            outputFile << "010010" + typeI(instructions[i], 4, true);
        } else if (inst == "sll") {
            outputFile << "011000" + sllInst(instructions[i], 4);
        } else if (inst == "move") {
            instructions[i] += ",$0";
            outputFile << "100000" + typeR(instructions[i], 5);
        } else if (inst == "slt") {
            outputFile << "100111" + typeR(instructions[i], 4);
        } else if (inst == "sw") {
            outputFile << "110000" + lswInst(instructions[i], 3);
        } else if (inst == "lw") {
            outputFile << "110001" + lswInst(instructions[i], 3);
        } else if (inst == "beq") {
            outputFile << "110100" + typeI(instructions[i], 4, false);
        } else if (inst == "j") {
            outputFile << "111000" + typeJ(instructions[i], 2);
        } else if (inst == "jr") {
            outputFile << "111001" + jrInst(instructions[i], 3);
        } else if (inst == "jal") {
            outputFile << "111010" + typeJ(instructions[i], 4);
        } else if (inst == "halt") {
            outputFile << "11111100000000000000000000000000";
        }
        if (i != instructions.size() - 1) outputFile << endl;
    }
    
    inputFile.close();
    outputFile.close();
    
    cout << "Now the machine code have outputed to " + outputFileName + " file, please check!" << endl;
    
    int cut;
    cout << "==>Do you want to truncate as 8 bit per line? If you don't want that please enter 0: ";
    cin >> cut;
    
    if (cut != 0) {

        cout << "==>Please input the output file name: ";
        cin >> inputFileName;

        ifstream inputFile(outputFileName.c_str());
        ofstream outputFile(inputFileName.c_str());

        if (!inputFile) {
            cout << "Can't open " + outputFileName + "." << endl;
            getchar(); getchar();
            return -1;
        }
        if (!outputFile) {
            cout << "Can't find " + inputFileName + "." << endl;
            getchar(); getchar();
            return -1;
        }
        
        bool first = true;

        while (!inputFile.eof()) {
            inputFile.getline(buffer, LineLength);
            if (strlen(buffer) != 32) break;
            for (int i = 0; i < 4; i++) {
                if (first) {
                  first = false;
                } else {
                  outputFile << endl;
                }
                for (int j = 0; j < 8; j++) {
                    outputFile << buffer[i * 8 + j];
                }
                
            }
        }
        
        cout << "Now the machine code have outputed to " + inputFileName + " file, please check!!" << endl;
        
        inputFile.close();
        outputFile.close();
    }
    getchar(); getchar();
    return 0;
}
