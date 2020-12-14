#include<stdio.h>

#define N 100
int main()
{
	int i,j,a[N];
	for(i=2;i<N;i++) a[i]=1;//假设所有为素数
	
	for(i=2;i<N;i++)
	{
		if(a[i])//素数--->素数的倍数
		//j=i的原因因为从小到大筛所以i*<i的数已被筛过
			for(j=i;i*j<N;j++) a[i*j]=0;		
	}
	
	for(i=2;i<N;i++) 
		if(a[i]) printf("%4d",i);
	return 0;
}

