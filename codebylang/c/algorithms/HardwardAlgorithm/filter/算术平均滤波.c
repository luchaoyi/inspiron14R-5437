/*
	����ƽ���˲������������������������������ͳ��ƽ��ֵ����0
	��������β������ֵ����������������Ч���Ͳ�����������
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
	ȥ��ֵ��ֵ�˲�:���ǵ�ͻ��ë�̶Ծ�ֵ��Ӱ����ȡ��ֵǰ��������޳�
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



