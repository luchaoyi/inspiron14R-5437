
void SelectSort(int r[],n)
{
	
	for(i=1;i<n-1;i++)
	{   
		min=i;
		for(j=i+1;j<n;j++)
		{   
			if(r[j]<r[min])//ѡ����С��
			{
				min=j;
			}
		}
		//ѡ����С�ķ�����ǰ��
		//���ٽ�������
		if(min!=i)
		{
			r[0]=r[min];//r[0]��Ϊ�����ռ�
			r[min]=r[i];
			r[i]=r[0]
		}
		
	}
}