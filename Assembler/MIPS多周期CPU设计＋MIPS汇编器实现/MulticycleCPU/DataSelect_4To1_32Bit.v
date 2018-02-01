`timescale 1ns / 1ps
module DataSelect_4To1_32Bit(A, B, C, D, Ctrl, S);
  input [31:0] A, B, C, D; // 四个数据
  input [1:0]Ctrl; //控制信号
  output reg[31:0] S;
  always @(Ctrl or A or B or C or D) begin
    case(Ctrl)
	   2'b00: S = A;
		2'b01: S = B;
		2'b10: S = C;
		2'b11: S = D;
		default: S = 0; // 给零号寄存器赋值不会有影响，因为寄存器模块不会修改零号寄存器的值
	 endcase
  end
endmodule
