`timescale 1ns / 1ps
// 符号扩展、zero扩展模块
module SignExtend(i_num, ExtSel, o_num);
  input [15:0] i_num;
  input [1:0] ExtSel;
  output reg[31:0] o_num;
  initial begin
	o_num = 0;
  end
  always @(i_num or ExtSel) begin
	 case(ExtSel)
		2'b00: o_num <= {{27{0}}, i_num[10:6]}; // 扩充 sa
		2'b01: o_num <= {{16{0}}, i_num[15:0]}; // 扩充立即数， 如 ori指令
		2'b10: o_num <= {{16{i_num[15]}}, i_num[15:0]}; // 符号扩充立即数，如addi、lw、sw、beq指令
		default: o_num <= {{16{i_num[15]}}, i_num[15:0]}; // 默认符号扩展
    endcase
  end
endmodule
