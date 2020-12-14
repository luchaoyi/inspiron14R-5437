/*
	算术平均滤波：随机噪声干扰随着数据样本增加统计平均值趋于0
	故连续多次采样求均值，抑制噪声，抑制效果和采样次数正比
*/

#defien N 10
int Filter()
{
	int i;
	int R[N];
	
	int SumR=0;
	int x0;
	
	for(i=0;i<=N-1;i++)
	{
		R[i]=SampAdc();
		SumR+=R[i];
	}

	x0=SumR/N;
	
	return SumR;
}

/*
	去极值均值滤波:考虑到突发毛刺对均值的影响在取均值前对其进行剔除
*/


#defien N 10

//Upper bound
//Lower bound

#define MAX 4950 
#defien MIN 0

int Filter()
{
	int i;
	int R[N];
	
	int SumR=0;
	
	int max=MIN;
	int min=MAX;
	
	
	int x0;
	
	for(i=0;i<=N-1;i++)
	{
		R[i]=SampAdc();
		SumR+=R[i];
		
		if(R[i]>max)
			max=R[i];
		if(R[i]<min)
			min=R[i];
	}
	x0=(SumR-max-min)/(N-2);
	
	return SumR;
}



