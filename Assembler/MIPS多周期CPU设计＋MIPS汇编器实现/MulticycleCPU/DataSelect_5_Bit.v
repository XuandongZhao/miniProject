`timescale 1ns / 1ps
// 数据选择器 （五位数据选择）
module DataSelect_5_Bit(A, B, C, Ctrl, S);
  input [4:0] A, B, C; // 三个数据
  input [1:0]Ctrl; //控制信号
  output reg[4:0] S;
  always @(Ctrl or A or B or C) begin
    case(Ctrl)
	   2'b00: S = A;
		2'b01: S = B;
		2'b10: S = C;
		default: S = 0; // 给零号寄存器赋值不会有影响，因为寄存器模块不会修改零号寄存器的值
	 endcase
  end
endmodule
