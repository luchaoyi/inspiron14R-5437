/*
	��ֵ�˲�����ÿһ���������ڽ�����������Ӳ�������ȡ��ֵ
	����������ǿ
	
	���������������ڽϳ��ĳ���
*/

#defien SC 5
#defien MD 3
int Filter()
{
	int i;
	int R[SC];
	int temp;
	
	int maxIndex;
	
	int x0;
	
	for(i=0;i<=SC-1;i++)
		R[i]=SampAdc();
	
	//sort find Median
	
	for(i=0;i<=MD-1;i++)
	{
			
			temp=R[i];// cache;
			maxIndex=i;
			for(j=i+1;j<=SC-1;j++)
			{
				if(R[j]>temp)
					{	temp=R[j];
						maxIndex=j;
					}
			}
			if(maxIndex!=i)
			{
				R[maxIndex]=R[i];
				R[i]=temp;
			}
			//else ����
	}
	
	x0=R[MD-1];
	return x0;
}



