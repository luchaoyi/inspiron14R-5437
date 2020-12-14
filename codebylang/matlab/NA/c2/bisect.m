

%{
二分法 c=(a+b)/2

迭代次数N=(ln(b-a)-ln(delta))/ln(2)

%}


%c is zero
%yc=f(c)
function [c,err,yc] = bisect(f,a,b,delta)

ya = feval(f,a)
yb = feval(f,b)

if ya*yb > 0 
	break
end

max1=1+round((log(b-a)-log(delta))/log(2)) %计算出迭代次数

for 1:max1
	c=(a+b)/2
	yc = feval(f,c)

	if yc == 0
		a=c;
		b=c;
	elseif yb*yc>0
		b=c;
		yb=yc;
	else 
		a=c;
		ya=yc;
	end
	if b - a <delta
		break
	end
end

c=(a+b)/2;
yc=feval(f,c);
err = abs(b-a)






