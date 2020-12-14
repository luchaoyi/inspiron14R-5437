//f(x)=0 xn+1 = xn-f(xn)/f'(xn)
//f'(x) = dot y/dot x --> f(x+0.000005) - f(x+0.000005)  / 0.00001

double CalcDerivative(FunctionPtr f,double x)
{
	return (f(x+0.000005)-f(x-0.000005))/0.00001;
}

double NewtonRaphson(FunctionPtr f,double x0)
{
	x1=x0-f(x0)/CalcDerivative(f,x0);
	while(abs(x1-x0)>PRECISION)
	{
		x0=x1;
		x1=x0-f(x0)/CalcDerivative(f,x0);
	}
}
