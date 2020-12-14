%{
	
	割线法利用割线而不用切线可以不用计算f‘（x）
	pk+1 = pk    -     f(pk)*(pk-pk-1)/f(pk)-f(pk-1)
%}



function [p0,err,k,y]  = scant(f,df,p0,p1,delta,epsilon,max1)


for k=1:max1
	p2 = p1 - feval(f,p1)*(p1-p0) / (feval(f,p1)-feval(f,p0));

	err = abs(p2-p1);
	relerr = 2*err / (abs(p2)+delta);


	p0=p1;
	p1=p2;

	y = feval(f,p2);

	if (err<delta) |(relerr<delta) |abs(y) < epsilon
		break
	end
end



