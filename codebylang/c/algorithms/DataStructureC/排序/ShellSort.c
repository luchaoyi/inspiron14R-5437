//1
void InsertSort(int r[],int n)
{
	int i,j,temp;
	
	int d;
	//希尔排序
	for(d=n/2;d>=1;d=d/2) //;缩小跳跃
	{
	//升序
	//用if减少不必要的操作
		for(i=d+1;i<=n;i++)
		{
			if(r[i]<r[i-d])//由于r[i]<r[i-d]所以
			{
				temp=r[i];
				for(j=i-d;j>0&&temp<r[j];j=j-d)//j>0保证不越界 ; //跳跃插入
					r[j+d]=r[j]; //后移
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
	//希尔排序
	do
	{
		d=d/2; //跳跃度可以自行设计
		//d=d/3+1
	//升序
	//用if减少不必要的操作
		for(i=d+1;i<=n;i++)
		{
			if(r[i]<r[i-d])//由于r[i]<r[i-d]所以
			{
				temp=r[i];
				for(j=i-d;j>0&&temp<r[j];j=j-d)//j>0保证不越界 ; //跳跃插入
					r[j+d]=r[j]; //后移
			}
			r[j+d]=temp;
		}
	}while(d==1)
}


//对比插入排序
void InsertSort(int r[],int n)
{
	int i,j,temp;
	
	for(i=1;i<=n;i++)
	{
	//升序
	//用if减少不必要的操作
		if(r[i]<r[i-1])
		{
			temp=r[i];//揭牌
			for(j=i-1;j>0&&temp<r[j];j--)
				r[j+1]=r[j]
		}
		//r[i]>r[i-1]不用挪不用比较
		r[j+1]=temp;
	}
}