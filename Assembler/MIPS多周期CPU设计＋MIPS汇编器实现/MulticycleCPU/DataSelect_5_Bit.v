`timescale 1ns / 1ps
// ����ѡ���� ����λ����ѡ��
module DataSelect_5_Bit(A, B, C, Ctrl, S);
  input [4:0] A, B, C; // ��������
  input [1:0]Ctrl; //�����ź�
  output reg[4:0] S;
  always @(Ctrl or A or B or C) begin
    case(Ctrl)
	   2'b00: S = A;
		2'b01: S = B;
		2'b10: S = C;
		default: S = 0; // ����żĴ�����ֵ������Ӱ�죬��Ϊ�Ĵ���ģ�鲻���޸���żĴ�����ֵ
	 endcase
  end
endmodule
