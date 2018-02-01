`timescale 1ns / 1ps
// PC模块
module PC(clk, i_pc, pcWre, reset, o_pc, outside_pc);
  input wire clk, pcWre, reset;
  input wire [31:0] i_pc, outside_pc;
  output reg [31:0] o_pc;
  always @(pcWre or reset) begin // 这里和单周期不太一样，存在竞争与冒险的问题，只有当pcWre改变的时候或者reset改变的时候再检测
    if (reset) begin
      o_pc = outside_pc;
    end else if (pcWre) begin
      o_pc = i_pc;
    end else if (!pcWre) begin //停机时候指令不变
		o_pc = o_pc;
	 end
  end
endmodule
