
/*
	整理扑克牌思想
*/

void insertSort(int a[],int n)
{
	int temp; //牌
	
	for(i=0;i<n;i++)
	{
		
		
		//用if减少不必要比较的操作
		if(a[i]<a[i-1])
		{	
			temp=a[i];
		
			for(j=i-1;j>=0&&temp<a[j];j--)
			{
				a[j+1]=a[j];
			}
			//当不满足时j已经递减到了前一个
			//此时空余的是j+1;
			a[j+1]=temp;
		}
		//r[i]>r[i-1]不用挪不用比较
		//就放在原地
		
	}
	
}
