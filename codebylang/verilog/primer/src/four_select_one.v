module fso(out, i0,i1,i2,i3,s0,s1);
output out;
input i0,i1,i2,i3,s0,s1;

assign out = s0?(s1?i3:i2):(s1?i1:i0);           
endmodule