/*
	Yn=a*Xn+(1-a)*Yn-1;
	
	a<1; a������Ҫ����Xn����ǰ����
	С����Ҫ����Yn ����ʷ
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