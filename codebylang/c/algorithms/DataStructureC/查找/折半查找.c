
//�����ʱʹ��
int BinSearch1(int r[],int n,int k)
{
	
	int low=1;//��1��ʼ
	int high=n;
	int mid=0;
	while(low<=high);//������low==highֹͣ
	{
		mid=(low+high)/2;
		if(k<r[mid])
		{
			high=mid-1;
		}
		elseif(k>r[mid])
		{
			low=mid+1;
		}
		else
			return mid;
	}
	return 0;
}

//��ͬ���̵�ѭ�����Եݹ�
int BinSearch(int r[],int low,int high,int k)
{
	if(low<=high)
	{
		mid=(low+high)/2;
		if(k<r[mid])
		{
			BinSearch(int r[],low,mid-1,k);
			//high=mid-1;
		}
		elseif(k>r[mid])
		{
			BinSearch(int r[],mid+1,high,k);
			//low=mid+1;
		}
		else
			return mid;
	}	
	else
		return 0;
}