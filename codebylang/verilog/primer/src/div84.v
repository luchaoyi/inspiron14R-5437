module div84(
input wire [7:0] numberator, //numberator/denominator 
input wire [3:0] denominator,
output reg[7:0] quotient,
output reg[3:0] remainder
);


reg[3:0] remH;
reg[3:0] remL;
reg[3:0] quotH;
reg[3:0] quotL;



always @(*)
begin

		div4({1'b0,numberator[7:4]},denominator,quotH,remH);
		div4({remH,numberator[3:0]},denominator,quotL,remL);
		quotient[7:4]=quotH;
		quotient[3:0]=quotL;
		remainder=remL;
end

task div4(
	input [7:0] number,
	input [3:0] denom,
	output [3:0] quot,
	output [3:0] rem 
);
reg[4:0] d;
reg[4:0] n1;
reg[3:0] n2;

begin
	d={1'b0,denom};
	n2=number[3:0];
	n1={1'b0,number[7:4]};

repeat(4)
	begin
		n1={n1[3:0],n2[3]};
		n2={n2[2:0],1'b0};
		if(n1>=d)
		begin
			n1=n1-d;
			//用n2低位保存商,左移后n2低位空余用来保存商
			n2[0]=1;
		end  
	end 
	quot=n2;
	rem=n1[3:0];

end 
endtask
endmodule
