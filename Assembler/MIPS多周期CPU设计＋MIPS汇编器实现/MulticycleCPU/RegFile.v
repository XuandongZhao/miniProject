`timescale 1ns / 1ps
// 寄存器组
module RegFile (rs, rt, rd, i_data, we, clk, o_data_1, o_data_2);
  input [4:0] rs, rt, rd;
  input [31:0] i_data;
  input we, clk;
  output [31:0] o_data_1, o_data_2;
  reg [31:0] register [0:31];
  initial begin
	register[0] = 0; // 只需要确定零号寄存器的值就好，$0恒等于0
  end
  assign o_data_1 = register[rs];
  assign o_data_2 = register[rt];
  always @(i_data or rd) begin // 这里有更改，不用CLK上升沿信号触发，因为与CtrlUnit共享CLK会发生延迟，导致下一个时钟上升沿才做相应动作
    if ((rd != 0) && (we == 1)) begin // rd != 0 是确保零号寄存器不会改变的作用
      register[rd] = i_data;
    end
  end
endmodule