module counter(out,clk,rst);
input clk,rst;
output reg[3:0] out ;

always @(posedge clk)
begin
	if(rst)
		out<=0;
	else
		out<=out+1;
end
endmodule 


