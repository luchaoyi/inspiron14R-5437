`timescale 100ns/1ns
module counter_top;
reg clk=0;
reg rst;
wire[3:0] out;

parameter vcd="counter.vcd";

counter c(out,clk,rst);

initial 
	$dumpfile(vcd); 
initial
	$dumpvars(0,counter_top);

always
	#5 clk=~clk;


initial 
begin
	rst=1;
	#10 
	rst=0;



	#1000 
	$finish;
end 
endmodule
