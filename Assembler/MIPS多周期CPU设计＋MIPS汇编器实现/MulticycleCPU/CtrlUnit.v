`timescale 1ns / 1ps
// 控制模块，包含了D触发器，状态转移，输出函数；
module CtrlUnit(opcode, clk, reset, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg, ExtSel, RegOut, PCSrc, ALUOp);
	input [5:0]opcode;
	input zero, clk, reset;
	output PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg;
	output [1:0]ExtSel, RegOut, PCSrc;
	output [2:0]ALUOp;
	
	wire [2:0]i_state, o_state;
	
	DFilpFlop DFilpFlop(i_state, reset, clk, o_state);
	NextState NextState(o_state, opcode, i_state);
	OutputFunc OutputFunc(o_state, opcode, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg, ExtSel, RegOut, PCSrc, ALUOp);

endmodule
