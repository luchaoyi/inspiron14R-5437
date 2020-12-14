


%{
	米勒法：用二次曲线，广义切线法
	用 （p0，f(p0)) ,(p1,f(p1)) (p2,f(p2)) 三点 设 p2 更优 
	t = x - p2
	
	t=h0  = p0-p2
	t=h1 = p1-p2
	t=0 = p2-p2

	y =at^2+bt+c

	代入

	c=f2

	e0=f0-c
	e1=f1-c

	a= e0h1-e1h0   / h1h0^2-h0h1^2

	b=e1h0^2-e0h1^2 / h1h0^2 - h0h1^2

	y=0
	z=-2c/b(+-)(b^2-4ac)^1/2

	t=z = x-p2=p3

	p3=p2+z
%}

function [p,y,err] = muller(f,p0,p1,p2,delta,epsilon,max1)

p=[p0,p1,p2];

Y = feval(f,P);

for k=1:max1
	h0 = p(1) - p(3);
	h1 = p(2) - p(3);
	
	c=Y(3);
	e0 = Y(1) - c;  
	e1 = Y(2) - c;

	denom = h1*h0^2 - h0*h1^2;

	a = (e0*h1-e1*h0) / denom;
	b = (e1*h0^2 - e0*h1^2) / denom;


	%有实根


	disc = b^2 - 4*a*c

	if disc >0
		disc = sqrt(disc);
	else
		disc = 0 ;
	end

	%确保精确 我们谨慎选择 步幅小的运算 

	if b < 0
		disc = -disc
	end

	z= -2*c/(b+disc);

	p = p(3) + z;

	
	% 更近的放在p（1） 三选2 胜一回就可以
	if abs(p-P(2)) < abs(p-P(1))
		
		%P(2)
		Q=[P(2),P(1),P(3)];
		P=Q;

		Y=feval(f,P)

	end
	
	
	if abs(p-P(3)) < abs(p-P(2)) 
		R=[P(1),P(3),P(2)];
		P=R;
		Y=feval(f,P);
	end
	P(3) = p;

	err = abs(z);
	relerr = err / (abs(p)+delta)

	if %..精度
		break
	end
end

	
	


