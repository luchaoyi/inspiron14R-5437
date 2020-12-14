
%{

	TM(x) = a0/2  + E (ajcos(jx)+bjsin(jx))

	M阶三角多项式



	xj = -pi + 2*jpi/N

	aj =  2/N E f(xk)cos(jxk)
	bj = 2/N  E f(xk)sin(jxk)

	三角多项式逼近傅立叶级数

%}

function [A,B] = tpcoeff(X,Y,M)

N=length(X) - 1;
max1 = fix((N-1)/2);


%2M<N
if M>max1
	M=max1;
end

A = zeros(1,M+1);
B = zeros(1,M+1);



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Yends = (Y(1) + Y(N+1)) /2;

Y(1)  = Yends;
Y(N+1) = Yends;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
A(1) = sum(Y);

for j =1:M
	A(j+1) = cos(j*X)*Y;
	B(j+1) = sin(j*X)*Y;
end

 
%A(2-N+1)  A1-->AN
%A0 
A= 2*A/N;
B=2*A/M;

A(1) = A(1) /2 ;





%{

z =A(1);
for j=1:M
	z = z + A(j+1) *cos (j*x) +B(j+1)*sin(j*x);
end
%}
