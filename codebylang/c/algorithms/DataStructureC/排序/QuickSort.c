/*
�˿���ʼ�ձ��ֽ���Ļ���,С�Ļ���
�����м�Ԫ��
��i=j����ʱ��Ȼ�ҵ��м�*/

int Partition(int r[],int first,int end)
{
	int i=first,j=end;
	int temp;
	while(i<j)
	{
		//���ҽ�����
		//����
		
		while(i<j&&r[i]<=r[j]) //��
			j--;
		//����ѭ��ʱ������r[i]>r[j]����
		if(i<j)
		{
			temp =r[i];
			r[j]=r[i];
			r[i]=temp;
			i++;
		}
		while(i<j&&r[i]<=r[j])//��
			i++;
		//����ѭ��ʱ������r[i]>r[j]����
		if(i<j)
		{
			temp =r[i];
			r[j]=r[i];
			r[i]=temp;
			j--;
		}
	}
	return i;
}


void QuickSort(int r[],int first,int end)
{
	if(first<end)
	{
		pivot=Partition(r,first,end);//����
		QuickSort(r,first,pivot-1);//��
		QuickSort(r,pivot+1,end);//��
	}
}
