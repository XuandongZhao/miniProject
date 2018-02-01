`timescale 1ns / 1ps
//主模块，用于小模块连线作用
module Main(CLK, RST, outside_pc, ins, now_pc);
  input CLK, RST;
  input [31:0] outside_pc;
  
  output [31:0] ins, now_pc;
  
  parameter endReg = 5'b11111;
  
  // 数据通路
  wire [31:0] pc, pc0, pc4, i_IR, instruction, pcChoose3, pcChoose1, extendData, ALUResult, WirteData, ReadData1, ReadData2, DataOut;
  wire [31:0] o_ADR, o_BDR, o_ALUout, i_ALUM2DR, i_ALUData2;
  wire zero;
  // 控制信号
  wire [2:0] ALUOp;
  wire [1:0] ExtSel, RegOut, PCSrc;
  wire PCWre, IRWre, InsMemRW, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg;
  
  // 数据选择输出
  wire [4:0] fiveChooseData;
  wire [31:0] InputWriteData1;
  
  
  // 引脚输出
  assign ins = instruction;
  assign now_pc = pc0;
  
  PC PC(CLK, pc, PCWre, RST, pc0, outside_pc); // 添加了外部pc
  PCAddFour PCAddFour(pc0, pc4);
  ROM ROM(i_IR, pc0, InsMemRW, outside_pc); // 添加了外部pc
  IR IR(i_IR, CLK, IRWre, instruction);
  PCJump PCJump(pc0, instruction[25:0], pcChoose3);
  DataSelect_5_Bit DataSelect_5_Bit(endReg, instruction[20:16], instruction[15:11], RegOut, fiveChooseData);
  RegFile RegFile(instruction[25:21], instruction[20:16], fiveChooseData, WirteData, RegWre, CLK, ReadData1, ReadData2);
  DataReg ADR(ReadData1, CLK, o_ADR);
  DataReg BDR(ReadData2, CLK, o_BDR);
  SignExtend SignExtend(instruction[15:0], ExtSel, extendData);
  DataSelect_2To1_32Bit ALU_DATA2(o_BDR, extendData, ALUSrcB, i_ALUData2);
  ALU ALU(o_ADR, i_ALUData2, ALUOp, zero, ALUResult);
  DataReg ALUout(ALUResult, CLK, o_ALUout);
  RAM RAM(o_BDR, o_ALUout, DataMemRW, DataOut);
  DataSelect_2To1_32Bit Write_Data(ALUResult, DataOut, ALUM2Reg, i_ALUM2DR);
  DataReg ALUM2DR(i_ALUM2DR, CLK, InputWriteData1);
  DataSelect_2To1_32Bit WrRegDataChoose(pc4, InputWriteData1, WrRegData, WirteData);
  PCAddImm PCAddImm(pc4, extendData, pcChoose1);
  DataSelect_4To1_32Bit PCSelect(pc4, pcChoose1, ReadData1, pcChoose3, PCSrc, pc);
  CtrlUnit CtrlUnit(instruction[31:26], CLK, RST, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg, ExtSel, RegOut, PCSrc, ALUOp);
endmodule