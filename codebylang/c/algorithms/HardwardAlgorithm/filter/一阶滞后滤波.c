/*
	Yn=a*Xn+(1-a)*Yn-1;
	
	a<1; a大则主要依赖Xn即当前采样
	小则主要依赖Yn 即历史
*/


#define A 0.03125

int filter()
{
	float x0,x1;
	float y1,y0;
	
	x0=SampAdc();
	y0=y1;
	
	while(1)
	{
		x1=SampAdc();
		y1=(1-A)*y0+A*x1;
		y0=y1;
	}
	
}