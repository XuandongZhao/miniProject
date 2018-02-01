`timescale 1ns / 1ps
// �Ĵ�����
module RegFile (rs, rt, rd, i_data, we, clk, o_data_1, o_data_2);
  input [4:0] rs, rt, rd;
  input [31:0] i_data;
  input we, clk;
  output [31:0] o_data_1, o_data_2;
  reg [31:0] register [0:31];
  initial begin
	register[0] = 0; // ֻ��Ҫȷ����żĴ�����ֵ�ͺã�$0�����0
  end
  assign o_data_1 = register[rs];
  assign o_data_2 = register[rt];
  always @(i_data or rd) begin // �����и��ģ�����CLK�������źŴ�������Ϊ��CtrlUnit����CLK�ᷢ���ӳ٣�������һ��ʱ�������ز�����Ӧ����
    if ((rd != 0) && (we == 1)) begin // rd != 0 ��ȷ����żĴ�������ı������
      register[rd] = i_data;
    end
  end
endmodule