//pwm通过占空比来控制电机速度
//占空比,通过计数来控制
module pwm(
input wire clk,
input wire rst,
input wire[7:0] duty,
input wire[7:0] period, //控制周期,count计数到period-1计数器清0。 在0-period-1产生一个pwm波
output reg pwm
);

reg[7:0] count;

always@(posedge clk)
begin
	if(rst)
	begin
		count<=0;
	end 
	else if(count>=period-1)
		count<=0;
	else
		count<=count+1;
end 

always@(posedge clk)
begin
	if(count<duty)
		pwm<=1;
	else
		pwm<=0;

end 
endmodule
