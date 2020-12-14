primitive udp_or(out,a,b);

output out;
input a,b;

table
	//a b : out 
	  0 0 : 0;
	//1 ?包含了10 11 1x
	  1 ? : 1;
	  ? 1 : 1;
	//  1 1 : 1;
	  0 x :x;
	  x 0 :x;
endtable
endprimitive
