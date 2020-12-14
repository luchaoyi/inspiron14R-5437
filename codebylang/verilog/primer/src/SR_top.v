module Top; //注意 ";"

parameter vcd="SR.vcd"; 

	wire q,qbar;
	reg set,reset;

	SR s0(.Q(q),.Qbar(qbar),.Sbar(~set),.Rbar(~reset));


	initial 
	begin 
		$monitor($time,"--%d -- %d -- %d",set,reset,q);
		set=0;reset=0;
		#5 reset=1;
		#5 reset=0;
		#5 set=1;
	end
	initial 
	begin
		$dumpfile(vcd);
		$dumpvars(0,Top);
	end
endmodule
