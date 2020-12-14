

`timescale 100ns/1ns


module Top;

parameter vcd="fso.vcd";


reg i0=1,i1=1,i2=1,i3=1,s0,s1;
wire out;
fso f0(out,i0,i1,i2,i3,s0,s1);


initial 
begin
	$monitor(out,i0,i1,i2,i3,s0,s1);
	#5
	s0=0;
	s1=0;
	#5
	s0=0;
	s1=1;
	#5
	s0=1;
	s1=0;
	#5
	s0=1;
	s1=1;

end

initial 
begin 
	$dumpfile(vcd);
	$dumpvars(0,Top);
end 
endmodule
