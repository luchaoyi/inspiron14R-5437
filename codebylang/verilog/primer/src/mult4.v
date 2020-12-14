module mult4
(
	input wire[3:0] a,
	input wire[3:0] b,
	output reg[7:0] p
);


reg [7:0] pv;
reg [7:0] bp;

integer i;

//移位累加
//阻塞赋值，最终综合为串行,电路.
always @(*)
begin
	pv=8'd0;
	bp={4'b0000,b};
	for(i=0;i<=3;i=i+1)
	begin
		if(a[i]==1)
			pv=pv+bp; 

		bp={bp[6:0],1'b0};
	end
	p=pv;
end 

endmodule
