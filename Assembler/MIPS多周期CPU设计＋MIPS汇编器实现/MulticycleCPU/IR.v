`timescale 1ns / 1ps
// IRָ��Ĵ�����Ŀ����ʹָ����뱣���ȶ�
module IR(i_data, clk, IRWre, o_data);
  input clk, IRWre;
  input [31:0] i_data;
  output reg[31:0] o_data;
  always @(negedge clk) begin // ��������о���ð������
    if (IRWre) begin
	    o_data = i_data;
	 end
  end
endmodule
