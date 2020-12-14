

%{
	上三角阵采用回代法
	xk =		bk - E(j=k+1,N) akj*xj  /	akk

	if akk !=0 存在唯一解
	end

	上三角或下三角
	det（A） = II aii

%}

function X=backsub(A,B)

n = length(B);

X=zeros(n,1);

X(n) = B(n) / A(n,n);

for k=n-1:-1:1
	X(k) = (B(k) - A(k,k+1:n)*X(K+1:n)) / A(k,k)
end


