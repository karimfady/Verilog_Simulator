`timescale 1ns / 1ps

module Test_Cicuit_2(input (0:2)x,output reg f);
always @(*) begin

assign f = (~x[0]&&x[2])&&(x[0]|x[1]);
  
end  
endmodule