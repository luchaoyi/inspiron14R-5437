
/*
	希尔排序是跳跃排序
	可以较少移动交换次数
	可以优化对序列有序性依赖的排序算法
	
	希尔步长的选择(for(d=n/2;d>=1;d=d/2));使程序不稳定
	
	p175;
/*

void shellinsertSort(int a[],int n)
{
	int temp; //牌
	
	for(d=n/2;d>=1;d=d/2) //跨度跳跃
	{
		
		
		for(i=0;i<d;i++) //为跨度内所有元素执行同跨度排序   错误的思量变成了类似分治的感觉
		{
			for(j=i;j<n;j+=d)
			{
				//用if减少不必要比较的操作
				if(a[j]<a[j-d])
				{	
					temp=a[j];
					
					for(k=j-d;k>=i&&temp<a[k];k=k-d)
					{
						a[k+d]=a[k];
					}
					//当不满足时j已经递减到了前一个
					//此时空余的是j+1;
					a[k+d]=temp;
				}
			}
		}
	}
	
}
*/


void InsertSort(int r[],int n)
{
	int i,j,temp;
	
	int d;
	//希尔排序
	for(d=n/2;d>=1;d=d/2) //;缩小跳跃
	{
	//升序
	//用if减少不必要的操作
		for(i=d+1;i<=n;i++)//正确的选择
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

