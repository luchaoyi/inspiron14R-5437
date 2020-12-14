module debounce4(
input clk,
input rst,
input wire[3:0] inp,
output wire[3:0]outp 
);
//按键消抖，稳定3个周期后输出值

reg[3:0] delay1;
reg[3:0] delay2;
reg[3:0] delay3;


assign D=delay1&delay2&delay3;
//脉冲哦电路第二个周期输出值，delay1=1 delay2=1 ~delay3=1,第3个周期以后输出0
//assign D=delay1&delay2&~delay3;

always@(posedge clk)
begin
	if(rst)
	begin
		delay1<=0;
		delay2<=0;
		delay3<=0;
	end
	else
	begin
		delay1<=inp;
		delay2<=delay1;
		delay2<=delay2;
	end 
end 
endmodule
