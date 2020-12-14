


%{
试值法 构造割线 m= f(b) - f (a)           /     b - a 割线斜率
令割线 = 0
c = b -		f(b)(b-a) / f(b) - f(a)

%}


%c is zero
%yc=f(c)

% delta is the tolerance for the zero 
% epsilon is the tolerance for the f
function [c,err,yc] = regula(f,a,b,delta,epsilon,max1)

ya = feval(f,a)
yb = feval(f,b)

if ya*yb > 0 
	break
end

for 1:max1
	
	dx = yb*(b-a)/yb-ya
	c=b-dx
	
	ac = c-a

	yc = feval(f,c)
	
	if yc == 0
		break
	end

	elseif yb*yc>0
		b=c;
		yb=yc;
	else 
		a=c;
		ya=yc;
	end

	dx = min (abs(dx),ac)

	if abs(dx) < delta ,break ,
	end

	if abs(yc) < epsilon,break,
	end

end

c=(a+b)/2;
yc=feval(f,c);
err = abs(b-a)






