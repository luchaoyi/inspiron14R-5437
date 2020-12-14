
%{
	
	非奇异矩阵	A=LU 则A存在三角分解 (Uii!=0)


	AX=B -> LUX=B 令 UX = Y 则 LY = B -->Y -->X

	三角分解开始 L=I
	后将无行交换的A矩阵高斯消去将 倍数填入响应 I矩阵的相应位置 --> L U 分解

	无行交换是限制 可以用置换矩阵 
	PA=LU

	PAX=PB
	LY=PB
	UX=Y
	-->X

%}


function X = lufact(A,B)



[N,N] = size(A);

X=zeros(N,1);
Y=zeros(N,1)

C= zeros(1,N+1);

R=1:N;





for p=1:N-1
	
	[max1,j] = max(abs(Aug(p:N,p))


	

	%交换
	if p!=j
		C=A(p,:);
		A(p,:) = A(j+p-1,:);
		A(j+p-1,:) = C;
  
		%R 记录交换历史

		d=R(p);
		R(p) = R(j+p-1);
		R(j+p-1)=d;
	
	if A(p,p) == 0
		break
	end 


	% L 矩阵下三角对角线全为1 U为上三角 所以LU可以存储在A中鬼斧神工

	for k=p+1:N
		mult = A(k,p)/ A(p,p);
		A(k,p) = mult;%L

		A(k:,p+1:N) = A(k,p+1:N)  - mult*A(p,p+1:N);

		
	end

	%solve 
	%PA=LU

	%PAX=PB

	%LY=PB
	%UX=Y
	%-->X

	Y(1) = B(R(1))

	%LY  =  PB  PB = B(R(i))  
	%回代
	for k=2:N
		Y(k) = B(R(k)) - A(k,1:k-1)*Y(1:k-1)  % / L(k,k) = 1
	end

	%	UX = Y

	X(N) = Y(N) / X(N,N)

	for k=N-1:-1:1
		X(k) = (Y(k)- A(k,k+1:N)*X(k,k+1:N)) / A(k,k);
	end

end









