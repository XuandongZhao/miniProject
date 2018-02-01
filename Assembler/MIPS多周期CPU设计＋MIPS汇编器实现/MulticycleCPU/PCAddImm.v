`timescale 1ns / 1ps
// PC 加立即数模块
module PCAddImm(now_pc, addNum, o_pc);
  input [31:0] now_pc, addNum;
  output [31:0] o_pc;
  assign o_pc = now_pc + (addNum << 2);
endmodule
