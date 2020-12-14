`timescale 100ns/1ns

module Top;

	parameter vcd="nf.vcd";
	

	reg [1:0] coinin=0; //01:5分 10:10分 
	reg outpaper=0;
	reg  rst=0;
	reg clk=0;
	wire newspaper;

	newspaper_fsm mf(coinin, outpaper, rst, clk, newspaper );

	always
		#5 clk=~clk;


	initial 
	begin
		rst=1;
		#10 
		rst=0;
		#5
		coinin=2'b10;
		#5
		coinin=2'b01;
		#10
		outpaper=1;
		
		
		#100
		
		$finish;
	end 


	initial
		$dumpfile(vcd);
	initial
		$dumpvars(0,Top);
	
	
endmodule
