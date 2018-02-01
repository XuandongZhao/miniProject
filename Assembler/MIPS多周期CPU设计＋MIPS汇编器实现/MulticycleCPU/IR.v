`timescale 1ns / 1ps
// IR指令寄存器，目的是使指令代码保持稳定
module IR(i_data, clk, IRWre, o_data);
  input clk, IRWre;
  input [31:0] i_data;
  output reg[31:0] o_data;
  always @(negedge clk) begin // 这里可能有竞争冒险问题
    if (IRWre) begin
	    o_data = i_data;
	 end
  end
endmodule
