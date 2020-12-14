


%{
	对于f(x)多个 存在多个 零点时 先采用等间隔采样预估 出多个 近似点位置
	（i） y(k-1)y(k) < 0  x = (xk+xk-1)/2
	(ii) |y(k)| < e  (y(k)-y(k-1)）* (y(k+1) - y (k)) <0 斜率变号

%}

function R = approot(X,epsilon)

Y = f(X);

yrange = max(Y) - min(Y);

epsilon2 = epsilon*yrange;

n = length(X);

X(n+1) = X(n);
Y(n+1) = Y(n);
m=0;

for k = 2:n
	if Y(k-1)*Y(k) < 0 
		m =m+1;
		R(m) = (X(k)+X(k-1))/2;
	end
	s= (Y(k)-Y(k-1)) * (Y(k+1) - Y(k));

	if (abs(Y(k))<epsilon2) & (s<=0)
		m=m+1;
		R(m) = X(k);
	end
end

