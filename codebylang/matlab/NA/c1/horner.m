

%{

	P(x) = an*x^n+ ... a1*x1	

	 let bn = an then 
	 let bk=bk+1*x+ak

	 b0 = P(x)



%}

function p = P(x,a,n)

b=zeros(1,n)

b(n) = a(n)

for k=n-1:-1:0
	b(k) = a(k)+x*p

end




p'(x) : 导数

d=zeros(1,n-1);

d(n-1) = n*a(n)

for k=n-1:-1:0
	d(k-1) = k*d(k) + d(k)*x
end


$p(x) :积分

I=zeros(1,n+1)

I(n+1) = a(n) / (n+1)

for k=n:-1:1
	I(k) = a(k-1) / K*I(k+1) *x
end

I(0) = C+I(1)*x





