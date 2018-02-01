`timescale 1ns / 1ps
// 输出函数模块
module OutputFunc(state, opcode, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg, ExtSel, RegOut, PCSrc, ALUOp);
	input [2:0]state;
	input [5:0]opcode;
	input zero;
	output reg PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg;
	output reg[1:0]ExtSel, RegOut, PCSrc;
	output reg[2:0]ALUOp;
	parameter [2:0] IF = 3'b000, // IF状态
						 ID = 3'b001, // ID状态
						 aEXE = 3'b110, // add等指令的EXE状态
						 bEXE = 3'b101, // beq指令的EXE状态
						 cEXE = 3'b010, // sw，lw指令的EXE状态
						 MEM = 3'b011, // MEM状态
						 aWB = 3'b111, //add等指令的WB状态
						 cWB = 3'b100; // lw指令的WB状态
	parameter [5:0] addi = 6'b000010,
						 ori = 6'b010010,
						 sll = 6'b011000,
						 add = 6'b000000,
						 sub = 6'b000001,
						 move = 6'b100000,
						 slt = 6'b100111,
						 sw = 6'b110000,
						 lw = 6'b110001,
						 beq = 6'b110100,
						 j = 6'b111000,
						 jr = 6'b111001,
						 Or = 6'b010000,
						 And = 6'b010001,
						 jal = 6'b111010,
						 halt = 6'b111111;
						 
	always @(state) begin
		// 对PCWre定值
		if (state == IF && opcode != halt) PCWre = 1;
		else PCWre = 0;
		// 对InsMemRW定值
		InsMemRW = 1;
		// 对IRWre定值
		if (state == IF) IRWre = 1;
		else IRWre = 0;
		// 对WrRegData定值
		if (state == aWB || state == cWB) WrRegData = 1;
		else WrRegData = 0;
		// 对RegWre定值
		if (state == aWB || state == cWB || opcode == jal) RegWre = 1;
		else RegWre = 0;
		// 对ALUSrcB定值
		if (opcode == addi || opcode == ori || opcode == sll || opcode == sw || opcode == lw) ALUSrcB = 1;
		else ALUSrcB = 0;
		// 对DataMemRW定值
		if (state == MEM && opcode == sw) DataMemRW = 1;
		else DataMemRW = 0;
		// 对ALUM2Reg定值
		if (state == cWB) ALUM2Reg = 1;
		else ALUM2Reg = 0;
		// 对ExtSel定值
		if (opcode == ori) ExtSel = 2'b01;
		else if (opcode == sll) ExtSel = 2'b00;
		else ExtSel = 2'b10;
		// 对RegOut定值
		if (opcode == jal) RegOut = 2'b00;
		else if (opcode == addi || opcode == ori || opcode == lw) RegOut = 2'b01;
		else RegOut = 2'b10;
		// 对PCSrc定值
		case(opcode)
			j: PCSrc = 2'b11;
			jal: PCSrc = 2'b11;
			jr: PCSrc = 2'b10;
			beq: begin
				if (zero) PCSrc = 2'b01;
				else PCSrc = 2'b00;
			end
			default: PCSrc = 2'b00;
		endcase
		// 对ALUOp定值
		case(opcode)
			sub: ALUOp = 3'b001;
			Or: ALUOp = 3'b101;
			And: ALUOp = 3'b110;
			ori: ALUOp = 3'b101;
			slt: ALUOp = 3'b010;
			sll: ALUOp = 3'b100;
			beq: ALUOp = 3'b001;
			default: ALUOp = 3'b000;
		endcase
		// 防止在IF阶段写数据
		if (state == IF) begin
			RegWre = 0;
			DataMemRW = 0;
		end
	end
	
endmodule
