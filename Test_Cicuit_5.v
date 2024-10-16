`timescale 1ns / 1ps

module Test_Cicuit_5(input (0:2)x,output f);
always @(*) begin

assign f = ((x[0]&&x[1])|~(~x[0]&&x[2]))&&(~x[0]|x[2]);
end  
endmodule
