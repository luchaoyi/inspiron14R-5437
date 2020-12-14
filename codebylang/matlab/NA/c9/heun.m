

%{
休恩方法思想是转化为积分逼近

y(t) = f'(t,y(t))

$(t0,t1)f(t,y(t)) = $(t0,t1)y'(t) = y(t1) - y(t0)

y(t1) = y(t0) + $(t0,t1)f(t,y(t)) 

所以可以采用计算积分的数值方法逼近

采用梯形公式 y(tk+1) = y(tk) +  h/2(f(tk,yk)+f(tk+1,yk+hf(tk,yk)))

%}


function H=heun(f,a,b,ya,M)
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
	k1 = feval(f,t(i),Y(i));
	k2 = feval(t(i+1),Y(i)+h*k1);

	Y(i+1) = Y(i)+h/2*(k1+k2);

end
H=[T',Y'];


