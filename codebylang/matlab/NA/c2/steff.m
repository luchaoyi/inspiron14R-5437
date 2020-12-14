


%{
	埃特金加速：加速任何线性收敛序列
	存在 A |A| < 1

	lim n->00 lim p - pn+1 / p- pn = A

	qn= pn - (dotpn)^2 / dot^2pn = pn - (pn+1-pn)^2 / pn+2 - 2pn+1 + pn 

%}


% P is approximation to zero 
% Q is sequence 
function [P,Q] = steff(f,df,p0,delta,epsilon,max1)

R = zeros(max1,3)

R(1,1) = p0

%结合牛顿迭代 g（x ) = x - f(x) / f'(x)
%p0 -> p1 -> p2 -->埃特金加速-->p3
for k =1:max1
	for j =2:3
		nrdenom = feval(df,R(k,j-1))
		
		if nrdenom == 0
			'division by 0 in newton-raphson method'
			break
		else
			% newton-raphson
			R(k,j) = R(k,j-1) - feval(f,R(k,j-1))/nrdenom;
		end
	end
	%          p2        p1      p0 
	aadenom = R(k,3) - 2*R(k,2)+R(k,1);

	if aadenom == 0
		'division by 0 in Aitken Acceleration'
		break
	else
		% p3 = p0-			(p1-p0)^2 / p2-2p1+p0
		R(k+1,1) = R(k,1) -  (R(k,2)-R(k,1))^2/aadenom; 
	end

	if (nrdenom == 0) | (aadenom == 0)
		break
	end

	err = abs(R(k,1) - R(K+1,1));

	relerr = err /(abs(R(k+1,1))+1)

	y = feval(f,R(k+1,1));

	if %满足精度
		P=R(k+1,1);
		Q=R(1:k+1,:)
	end
end


