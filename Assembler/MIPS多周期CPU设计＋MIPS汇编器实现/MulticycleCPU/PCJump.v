`timescale 1ns / 1ps
// 计算PC直接跳转位置模块
module PCJump(PC0, i_addr, o_addr);
  input [31:0] PC0;
  input [25:0] i_addr;
  output reg[31:0] o_addr;
  reg [27:0] mid;
  always @(i_addr) begin
	 mid = i_addr << 2;
	 o_addr <= {PC0[31:28], mid[27:0]};
  end
endmodule