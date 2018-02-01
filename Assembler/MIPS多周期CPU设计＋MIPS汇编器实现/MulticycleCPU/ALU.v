`timescale 1ns / 1ps
// ALU模块 ，算术逻辑单元
module ALU(A, B, ALUOp, zero, result);
  input [31:0] A, B;
  input [2:0] ALUOp;
  output zero;
  output reg [31:0] result;
  initial begin
		result = 0;
  end
  assign zero = (result? 0 : 1);
  always @(A or B or ALUOp) begin
    case(ALUOp)
      3'b000: result = A + B;
      3'b001: result = A - B;
      3'b010: result = (A < B ? 1 : 0);
      3'b011: result = A >> B;
      3'b100: result = A << B;
      3'b101: result = A | B;
      3'b110: result = A & B;
      3'b111: result = (~A & B) | (A & ~B);
      default: result = 0;
    endcase
  end
endmodule
