

%{
	newton法 f(x) f'(x) f''(x) 在根p处连续
	
	注意 f'(x) !=0  lim h->0 f(x0+h)-f(x0) / h = f'(x0)

	pk = g(pk-1) = pk-1 - f(pk-1) / f'(pk-1) 迭代公式 这个迭代公式是不动点迭代

	收敛条件为 g'(x) <=k <1
	所以 f(x)  f'(x) f''(x) 连续

	推论 求 根号 A 近似 值 x^2 -A = 0 --> pk = (pk-1 + )A/pk-1)) / 2
	
	更多关于收敛阶与加速收敛
%}


function [p0,err,k,y]  = newton(f,df,p0,delta,epsilon,max1)

for k=1:max1
	p1 = p0 - feval(f,p0) / feval(df,p0);

	err = abs(p1-p0);
	relerr = 2*err / (abs(p1)+delta);


	p0=p1;

	y = feval(f,p1);

	if (err<delta) |(relerr<delta) |abs(y) < epsilon
		break
	end
end



