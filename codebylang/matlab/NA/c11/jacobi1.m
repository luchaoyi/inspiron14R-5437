


%{
性质K非奇异
B = K^-1AK
则A与B相似

A         B
lambda     lambda
V         K^-1V



AX =lambdaX 

B=k^-1AK
两边同乘 K^-1X

BK^-1X = K^-1AK*K^-1X = K^-1AX = K^-1*lambdaX=lambda*k^-1X %代换

let Y=K^-1X

BY=lambdaY


求B的特征Y X=KY 

设R是正交矩阵（R^-1 = R' RR'=I)

D=R'AR
...

DY=lambdaY

X=RY

if A为对称矩阵 则D也为 对称矩阵


若构造 R1...Rn  R=R1*..Rn 使D迭代为对角阵

AR=RD
则 D的对角线元素为 lambda R=[X1,X2,..Xn] 对应特征向量

R为旋转矩阵 可以通过使非对角为零来计算旋转角度

主要思想通过相似变换正交变换和对角阵和旋转矩阵性质

 
绕xpxq面旋转
R=[1 
	 c	s
	 -s c
			1]   

%}


function [V,D] = jacobi1(A,epsilon)

[n,n] = size(A);
D=A;

V=eye(n)

state =1;

%D-diag(diag(D)) 除去对角线阵 找出每列最大元素
[m1,p] = max(abs(D-diag(diag(D))));

[m2,q] = max(m1);

p=p(q); %p是最大元素行号q列号
%find max index (p,q)


while(state == 1)
	
	theta = D(q,q) - D(p,p) /2*D(p,q);

	t=sign(theta) / (abs(theta)+sqrt(theta^2+1));

	c=1/sqrt(t^2+1);

	s=c*t;

	R=[c,s;-s,c];

	D([p q],:) = R'*D([p,q],:);
	D[:,[p q]] = D([p,q],:)*R;

	V[:,[p,q]] = V(:.[p,q])*R;
	[m1,p] = max(abs(D-diag(diag(D))));

	[m2,q] = max(m1);

	p=p(q); %p是最大元素行号q列号
	%find max index (p,q)

	if(abs(D(p,q))<epsilon*sqrt(sum(diag(D).^2)/n))
		state =0;
	end
end

