



%{

y=g(x)与y=x交点为不动点
pn+1=g（pn)即将上一个y=下一个x迭代
若迭代收敛g（x）为连续函数则收敛与不动点

在xE（a,b）中对与所有x若g'(x) <= k < 1 则会收敛为吸引不动点
若g'(x) >1 则发散

绝对误差err = y-y^  相对误差err= (y-y^)/y

%}

%x=g(x)
%input tol 精度 max1 迭代次数
%P is {pn}
function [k,p,err,P] = fixpt(g,p0,tol,max1)

P(1) = p0;

for k=2:max1
	P(k) = feval(g,P(k-1));
	err = abs(P(k) - P(k-1))

	relerr = err/(abs(P(k))+eps)); %相对误差

	p=P(k)

	if (err<tol) |(relerr < tol)
		break;
	end

	if k == max1
		disp('max number of iterations exceeded')
	end

	P=P'

