

%{

A 主特征值lambda和唯一归一化V
幂法

X0 =[1 1 1 ...1]'

迭代
Yk = AXk

Xk+1 = 1/ck+1   * Yk

ck+1 是Yk中绝对值最大的分量

幂法可以选取
ck+1 可以是Xk中最大的分量

Xk-->V  ck--->lambda


移位特征值

lambda V 是A特征对

a 任意常量 lambda - a， V 是A-aI的特征对

逆特征值

lambda！=0 1/lambda，V 是 A^-1 的特征对


当a越接近lambdai then  1/(lambda-a) 越大  

移位反幂法
所以 令a初始接近 lambdai 求 （A-aI）^-1的最大特征值u1

A的 lambdaj = 1/u1+a



%}

function [lambda,V] = power1(A,X,epsilon,max1)

lambda = 0;
cnt=0;
err=1;

state = 1;

while ((cnt<=max1)&(state==1))
	Y=A*X;

	[m j] = max(abs(Y));
	
	C1 = m;

	dotc=abs(lambda-c1);
	
	Y=1/c*Y;

	dotV = norm(X-Y);
	

	err=max(dotc,dotV);

	X=Y;
	lambda=C1;
	state=0;

	if(err>epsilon)
		state=1;
	end
	cnt=cnt+1;
end
V=X;




