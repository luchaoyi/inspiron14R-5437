
#define MAX_SZIE 10

merging(int *listl,int *listr,int listl_size,int listr_size)
{
	int temp[MAX_SIZE];
	int i,j,k;
	i=j=k=0;
	
	while(i<listl_size || j<listr_size)
	{
		//这样最终也可以完成不过最终会增加不必要的比较
		if(listl[i]<listr[j])
		{
			temp[k++]=listl[i++]; 	 //扔左
		}
		else
		{
			temp[k++] = listr[j++]; //扔右
		}
	}	
}

merging(int *listl,int *listr,int listl_size,int listr_size)
{
	int temp[MAX_SIZE];
	int i,j,k;
	i=j=k=0;
	
	while(i<listl_size && j<listr_size)
	{
		if(listl[i]<listr[j])
		{
			temp[k++]=listl[i++]; 	 //扔左
		}
		else
		{
			temp[k++] = listr[j++]; //扔右
		}
	}	
	
	//？？？对比上个减少了比较
	while(i<listl_size)
	{
		temp[k++]=listl[i++];
	}
	
	while(j>listr_size)
	{
		temp[k++]=listr[j++];
	}
}


int MergeSort(int k[],int n)
{
	if(n>1)
	{
		int *listl = k;
		int  listl_size =n/2;
		int *listr = k+(n/2);
		int  listr_size = n-listl_size;
		
		MergeSort(listl,listl_size);//散开
		MergeSort(listr,listr_szie);//散开
		
		//最后归并
		merging(listl,listr,listl_size,listr_size);
	}
}