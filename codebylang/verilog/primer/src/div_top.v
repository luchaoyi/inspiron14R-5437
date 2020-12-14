module div_top;
reg [7:0] n;
reg [3:0] d_in;
wire[7:0] q;
wire [3:0] r;

parameter vcd="div84.vcd";

div84 d(n,d_in,q,r);

initial 
	$dumpfile(vcd); 
initial
	$dumpvars(0,div_top);

initial
begin
	n=10;
	d_in=2;
	#10
	n=5;
	d_in=3;
	#10
	n=15;
	d_in=4;
	#10
	n=12;
	d_in=2;
	#10
	$finish;
end 
endmodule
