
struct poly
{
	int N;//最高次幂
	int *a;//系数数组数组有N+1项
} *pPoly;



//指针操纵ADT很容易用=进行交换
pPoly polymult(pPoly a,pPoly b)
{
	int *c
	int N=a->N+b->N;
	
	c= (int *)calloc(N*sizeof(int));
	
	for(i=0;i<=a->N;i++)
		for(j=0;j<=b->N;j++)
		{
			c[i*j]+=a[i]*a[j];
		}
}

pPoly polyadd(pPoly a,pPoly b)
{
	//另一种思路是交换指针使大的始终为a
	//然后统一返回a
	int i;
	if(a->N>b->N)
	{
		for(i=0;i<=N;i++)
		 a[i]+=b[i];
		
		return a[i];
	}
	else
	{
		
		b[i]+=a[i];
		return b[i];
	}
}


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

