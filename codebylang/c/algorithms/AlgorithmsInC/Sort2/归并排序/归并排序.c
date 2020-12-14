
/*
	归并排序: 递归时将合排序元素劈开分开
			  递归返回合并排序
			  
	如果在数组末尾增加一个观察哨就可以去掉末尾判断即扫尾
*/

int MergeAB(int a,int n,int b,int m)
{
	int i=0,j=0,k=0;
	int *c=(int)malloc((n+m)*sizeof(int))
	while(i<m&&j<m)cs
	{
		if(a[i]>b[j])
			c[k++]=b[j++];
		if(a[i]<=b[j])
			c[k++]=a[i++];
		
	}
		
	while(i<n)
	{temp[k++]=a[i++];} //将判断提出来优化效果好
	while(j<m)
	{temp[k++]=b[j++];}
	
	/* 
		for(i=0,j=0,k=0;k<n+m;k++)
		{
			if(i==n){c[k]=b[j++];continue;}//如果在数组末尾增加一个观察哨就可以去掉末尾判断
			if(j==m){c[k]=a[i++];continue;}
			
			if(a[i]>b[j])
				c[k++]=b[j++];
			if(a[i]<=b[j])
				c[k++]=a[i++];
			
		}
	*/

}

/*
	原位归并排序
	通过使用指针操纵数组
	原位归并
*/


merge(listl,listr,listl_size,listr_size);
{
	int temp[MAX_SIZE];
	//该借力使就借力千万别忘了
	int i,j,k,n;
	i=j=k=0;

	while(i<  listl_size && j < listr_size)
	{
		if(listl[i]<listr[j]) //升序扔小的
		{
			temp[k++]=listl[i++];
		}
		else
		{
			temp[k++]=listr[j++];
		}

	}
	
	//存在一个结尾时另一个没结尾情况
	//扫尾	
	while(i<listl_size)
	{temp[k++]=listl[i++];}
	while(j<listr_size)
	{temp[k++]=listr[j++];}
	
	for(n=0;n<listl_size+listr_size;n++)
	{
		listl[n]=temp[n];
	}//复制回去
	
}

MergeSort(int r[],int n)
{
	//二路归并
	int *listl=r;
	int listl_size=n/2;
	int *listr=r+listl_size;
	int listr_size=n-listl_size;

	MergeSort(listl,listl_size);
	MergeSort(listr,listr_size);

	merge(listl,listr,listl_size,listr_size);
		
}



























