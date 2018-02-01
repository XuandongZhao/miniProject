`timescale 1ns / 1ps
// PCģ��
module PC(clk, i_pc, pcWre, reset, o_pc, outside_pc);
  input wire clk, pcWre, reset;
  input wire [31:0] i_pc, outside_pc;
  output reg [31:0] o_pc;
  always @(pcWre or reset) begin // ����͵����ڲ�̫һ�������ھ�����ð�յ����⣬ֻ�е�pcWre�ı��ʱ�����reset�ı��ʱ���ټ��
    if (reset) begin
      o_pc = outside_pc;
    end else if (pcWre) begin
      o_pc = i_pc;
    end else if (!pcWre) begin //ͣ��ʱ��ָ���
		o_pc = o_pc;
	 end
  end
endmodule
