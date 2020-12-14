

%{
	严格对角优势 |akk| > E|akj|
	对角线元素绝对值大于其它元素之和
	迭代会绝对收敛到唯一解
	而收敛的不一定有严格对角优势
	充分条件

	jacobi 迭代用旧值生成新值而
	gseid  迭代尽量用新值生成新值 收敛的更快
	不过某些情况下 jacobi 会 收敛 而gseid不会

%}

function X = gseid(A,B,P,delta,max1)
%P 解有个初始解

N=length(B);


for k=1:max1

	for j =1:N
		if j ==1
			X(1) = (B(1) - A(2:N)*P(2:N) / A(1,1);
		elseif j==N
			X(N) = (B(N) - A(1:N-1)*X(1:N-1) / A(N,N);
		else
			X(j) = (B(j) - A(j,1:j-1)*X(1:j-1)-A(j,j+1:N)*P(j+1:N)) / A(j,j);

		end
	end
	
	err = abs(norm(X'-P));
	relerr = err / (norm(X)+eps);
	P=X';

	if (err < delta) |(relerr <delta)
		break
	end


end

X=X';

