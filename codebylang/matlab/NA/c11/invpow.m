



function [lambda,V] = invpow(A,X,alpha,epsilon,max1)


[n,n] = size(A);

A=A-alpha*eye(n);


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
lambda = 1/c1+alpha
V=X;

