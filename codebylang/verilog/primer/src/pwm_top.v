`timescale 100ns/1ns
//pwm通过占空比来控制电机速度
//占空比,通过计数来控制
module Top; //注意 ";"
parameter vcd="pwm.vcd"; 

reg clk=0;
reg rst;
reg[7:0] duty;
reg[7:0] period; //控制周期,count计数到period-1计数器清0。 在0-period-1产生一个pwm波
wire  pwm;


pwm p(
 clk,
 rst,
 duty,
 period, //控制周期,count计数到period-1计数器清0。 在0-period-1产生一个pwm波
pwm
);
	
	
	always
		#5 clk=~clk;
	initial 
	begin
		rst=1;
		#10
		rst=0;
		#10
		duty=64;
		period=220;
	
		#10000
		duty=110;
		period=220;
		#10000
		$finish;
	end
	
	initial 
	begin
		$dumpfile(vcd);
		$dumpvars(0,Top);
	end
endmodule
