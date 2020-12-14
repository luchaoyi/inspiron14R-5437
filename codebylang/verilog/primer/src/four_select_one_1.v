module fso(out, i0,i1,i2,i3,s0,s1);
output reg out;
input i0,i1,i2,i3,s0,s1;

always @(*)
begin
	case ({s0,s1})
		2'b00: out<=i0;
		2'b01: out<=i1;
		2'b10: out<=i2;
		2'b11: out<=i3;
	endcase
end 
//case 对每一位精确匹配 casex casez 会忽略x,z的匹配
endmodule
