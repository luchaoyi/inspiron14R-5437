//1
void InsertSort(int r[],int n)
{
	int i,j,temp;
	
	int d;
	//ϣ������
	for(d=n/2;d>=1;d=d/2) //;��С��Ծ
	{
	//����
	//��if���ٲ���Ҫ�Ĳ���
		for(i=d+1;i<=n;i++)
		{
			if(r[i]<r[i-d])//����r[i]<r[i-d]����
			{
				temp=r[i];
				for(j=i-d;j>0&&temp<r[j];j=j-d)//j>0��֤��Խ�� ; //��Ծ����
					r[j+d]=r[j]; //����
			}
			r[j+d]=temp;
		}
	}
}

//2
void InsertSort(int r[],int n)
{
	int i,j,temp;

	int d;
	//ϣ������
	do
	{
		d=d/2; //��Ծ�ȿ����������
		//d=d/3+1
	//����
	//��if���ٲ���Ҫ�Ĳ���
		for(i=d+1;i<=n;i++)
		{
			if(r[i]<r[i-d])//����r[i]<r[i-d]����
			{
				temp=r[i];
				for(j=i-d;j>0&&temp<r[j];j=j-d)//j>0��֤��Խ�� ; //��Ծ����
					r[j+d]=r[j]; //����
			}
			r[j+d]=temp;
		}
	}while(d==1)
}


//�ԱȲ�������
void InsertSort(int r[],int n)
{
	int i,j,temp;
	
	for(i=1;i<=n;i++)
	{
	//����
	//��if���ٲ���Ҫ�Ĳ���
		if(r[i]<r[i-1])
		{
			temp=r[i];//����
			for(j=i-1;j>0&&temp<r[j];j--)
				r[j+1]=r[j]
		}
		//r[i]>r[i-1]����Ų���ñȽ�
		r[j+1]=temp;
	}
}