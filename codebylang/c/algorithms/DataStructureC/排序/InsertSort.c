void InsertSort(int r[],int n)
{
    //r0����riֵ���ڱ�
    for(i=2;i<=n;i++)
    {
        r[0]=r[i];
        for(j=i-1;r[0]<r[j];j--)//���� ��� ����
        {
            r[j+1]=r[j];
        }
        //��λj�����ƶ��Ŀ�λ��j+1
        r[j+1]=r[0];
    }

}
////////////////////////////////////////////

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
			for(j=i-1;j>=0&&temp<r[j];j--)
				r[j+1]=r[j];
			r[j+1]=temp;
		}
		//r[i]>r[i-1]����Ų���ñȽ�
		
	}
}

