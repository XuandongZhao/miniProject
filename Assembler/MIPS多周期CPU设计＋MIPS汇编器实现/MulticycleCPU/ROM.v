`timescale 1ns / 1ps
// �Ĵ���
module ROM (instruction, addr, read_en_, outside_pc);
    input read_en_;
    input [31:0] addr, outside_pc;
    output reg [31:0] instruction;
    reg [7:0] mem [0:127]; //����ȡ32��ָ��
	 initial begin
		#1; // �ӳ���Ϊ����outside_pc��ֵ�ܹ���ȫ�ؽ���
        $readmemb("my_rom_data.coe", mem, outside_pc);
		  instruction = 0;
	 end
    always @( addr or read_en_)
        if (read_en_) begin
          instruction[31:24] = mem[addr];
          instruction[23:16] = mem[addr+1];
          instruction[15:8] = mem[addr+2];
          instruction[7:0] = mem[addr+3];
        end
endmodule