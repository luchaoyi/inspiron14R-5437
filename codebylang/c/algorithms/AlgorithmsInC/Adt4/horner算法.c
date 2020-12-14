double polyeval(pPoly p,float x)//多项式求值
{
	double t=0;
	
	//多项式求值算法
	//horner算法
	//a4X^4+a3X^3+a2X^2+a1X+a0=(((a4x+a3)X+a2)X+a1)X+a0;
	
	for(i=N;i>=0;i--)
	{
		t=t*x+p->a[i]; //a[N]x+a[N-1]
	}
		
}

