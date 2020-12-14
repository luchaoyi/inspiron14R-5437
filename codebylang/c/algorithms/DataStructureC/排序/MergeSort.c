

merge(listl,listr,listl_size,listr_size);
{
	int temp[MAX_SIZE];
	//该借力使就借力千万别忘了
	int i,j,k;
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
}

MergeSort(int r[],int n)
{
	int *listl=r;
	int listl_size=n/2;
	int *listr=r+listl_size;
	int listr_size=n-listl_size;

	MergeSort(listl,listl_size);
	MergeSort(listr,listr_size);

	merge(listl,listr,listl_size,listr_size);
		
}


