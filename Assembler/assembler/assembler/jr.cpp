/*---------------------------------------------
功能：对jr指令进行汇编
included in label.h
author  chen
create time : 2010.4.4
update time : 2010.4.4
------------------------------------------------*/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string Get_reg_value(string reg);

void jalr(string ir,int ir_type){
	ofstream fout("instruct.txt",ios::app);
	string rs = "", rd = "";
	int choose = 0;
	for(int i = 0; i < ir.length(); i++){
		if(ir[i] == '$'){
			i++;
			choose++;
			while(ir[i] != ',' && ir[i] != ',' && i < ir.length()){
				if(choose == 1) { rs += ir[i]; }
				if(choose == 2) { rt += ir[i]; }
				i++;
			}
		}
	}
	
	case 85 : { fout<<"000000"<<Get_reg_value(rs)<<Get_reg_value(rt)<<"0000000000"<<"110110"<<endl;  break;}//tne
	
	fout.close();
}



void jalr(){
	ofstream fout("instruct.txt",ios::app);
	fout<<"00100011111000000000000000000000"<<endl;
	fout.close();
}