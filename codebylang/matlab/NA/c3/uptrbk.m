
%{
	高斯选主元消去法
	用arr 消去 akr k=r+1:n
	AX=B --> [A|B] --> [U|Y]

	若arr = 0 考虑交换 r行下的行 如果找不到则 矩阵是奇异的不存在惟一解


	选取绝对值大的作为主元可以减小误差
%}


function X = uptrbk(A,B)




%A 列数
[N,N] = size(A);

X=zeros(n,1);

C= zeros(1,n+1);




%N*N+1
Aug=[A B]

%消元

%N row only one last 不用消
for p=1:N-1
	
	%select max as 主元
	% j is max index Y is value
	[Y,j] = max(abs(Aug(p:N,p)))
	

	%交换
	if p!=j
		C=Aug(p,:);
		Aug(p,:) = Aug(j+p-1,:);
		Aug(j+p-1,:) = C;
	end

	if 0 == Aug(p,p) 
		'A is a singular No unique  solution'
		break
	end
	
	for k=p+1:N
		m = Aug(K,p)/ Aug(p,p);
		Aug(k:,p:N+1) = Aug(k,P:N+1)  - m*Aug(p,p:N+1);
	end
end

X = backsub(Aug(1:N,1:N),Aug(1:N,N+1));






