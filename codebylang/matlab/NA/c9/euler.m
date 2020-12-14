



%{

欧拉利用的是泰勒级数展开
	t -> [a,b] tk=a+kh  h=(b-a)/M

	y'=f(t,y),

for i=2:M+1
	Y(i) = Y(i-1)+h*feval(f,T(i-1),Y(i-1));
end


	//在t0处泰勒展开

	y(t)  = y(t0) + y'(t0)(t-t0)+...

	h=tk+1-tk

	y(tk+1) = y(tk) + hf(tk,yk)
	欧拉近似
%}

% y'=f(t,y) , y(a) = y0

function E = euler(f,a,b,ya,M)

h = (b-a)/M;

T=zeros(1,M+1);
Y=zeros(1,M+1);

T=a:h:b
Y(1)=ya;

%{

for i=2:M+1
	Y(i) = Y(i-1)+h*feval(f,T(i-1),Y(i-1));
end
%}
for i=1:M+1
	Y(i+1) = Y(i)+h*feval(f,T(i),Y(i));
end

E=[T',Y'];

