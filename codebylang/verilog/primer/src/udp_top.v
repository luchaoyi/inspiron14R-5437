module Top;
parameter vcd="ux.vcd";

	reg a,b;
	wire out;
	udp_or o(out,a,b);

	initial
	begin
		a=0;
		b=0;
		#5
		a=1;
		b=0;
		#5
		a=1;
		b=1;
	end 

	initial
		$dumpfile(vcd);
	initial
		$dumpvars(0,Top);
endmodule
