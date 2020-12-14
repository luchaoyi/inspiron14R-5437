module mult4_top;
reg [3:0] a;
reg [3:0] b;
wire[7:0] p;

parameter vcd="mult4.vcd";

mult4 m(a,b,p);

initial 
	$dumpfile(vcd); 
initial
	$dumpvars(0,mult4_top);

initial
begin
	a=2;
	b=3;
	#10
	a=3;
	b=4;
	#10
	a=9;
	b=9;
	#10
	a=1;
	b=2;
	#10
	$finish;
end 
endmodule
