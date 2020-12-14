

%{
f(x) 在[-1,1] 上的插值
切比雪夫多项式
T0(x) = 1 T1(x) = x;

Tk(x) = 2xTk-1(x) - Tk-2(x)

1) TN(x) 中 x^N  的系数为2^(N-1) 
2)TN(x) = cos(N arccos(x)) -1<=x<=1
3)TN(x) 有N个零点 xk = cos((2k+1)*pi / 2N)



切比雪夫逼近 f(x) -> E cjTj(x)

c0 = 1/(N+1)  * E f(xk)T0(xk) 

cj = 2/(N+2) * E f(xk) Tj(xk)

xk = ((2k+1)*pi / 2N+2)

%}




function [C,X,Y] = cheby(fun,a,b)

if nargin==2 
	a=-1;b=1;
end

d= pi/(2*n+2);

C=zeros(1,n+1);

for k =1:n+1
	X(k) = cos((2*k-1)*d);
end

%区间变换
% x = (b-a)/2*t +(a+b)/2
X=(b-a)*X/2+(a+b)/2;
x=X;

Y=eval(fun);

for k =1:n+1
	z=(2*k-1)*d
	for j=1:n+1
		C(j) = C(j)+Y(k)*cos((j-1)*z)
	end
end

C=2*C/(n+1);
C(1) = C(1) /2;

