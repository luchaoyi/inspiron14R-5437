
void SelectSort(int r[],n)
{
	
	for(i=1;i<n-1;i++)
	{   
		min=i;
		for(j=i+1;j<n;j++)
		{   
			if(r[j]<r[min])//选择最小的
			{
				min=j;
			}
		}
		//选择最小的放在最前面
		//减少交换次数
		if(min!=i)
		{
			r[0]=r[min];//r[0]作为交换空间
			r[min]=r[i];
			r[i]=r[0]
		}
		
	}
}