`timescale 1ns / 1ps
// �ڴ�ģ��
module RAM (i_data, addr, rw, o_data);
    input [31:0] i_data;
    input [31:0] addr;
    input rw;
    output reg [31:0] o_data;
    reg [7:0] memory [0:63]; // ���16�����ݣ���Ϊ����ģ�������޺�����64���Ĵ���
	 initial begin
		o_data = 0;
	 end
    always @(addr or i_data or rw) begin // ʹ�ô�˷�ʽ����
      if (rw) begin // 1 Ϊ д
        memory[addr] = i_data[31:24];
		  memory[addr+1] = i_data[23:16];
		  memory[addr+2] = i_data[15:8];
		  memory[addr+3] = i_data[7:0];
      end else begin // 0 Ϊ ��
        o_data[31:24] = memory[addr];
		  o_data[23:16] = memory[addr+1];
		  o_data[15:8] = memory[addr+2];
		  o_data[7:0] = memory[addr+3];
      end
	end
endmodule 
