
///////////////////////////////////////////
void BubbleSort(int r[],n)
{
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			//升序排列
			if(r[i]>r[j])
			{
				t=r[i];
				r[i]=r[j];
				r[j]=t;
			}
		}
	}
}

/////////////////////////////////////////
void BubbleSort(int r[],n)
{
	exchange=n;
	while(exchange!=0)//记录是否有记录交换将比较减少到最小
	{
		bound=exchange;//开始无序区为[0-n]
		
		
		for(i=1;i<bound;i++)
		{
			if(r[i]<r[i-1])//向后交换升序
			{	
				t=r[i]；
				r[t]=r[i-1];
				r[i-1]=t;
				
				exchange=i-1;//缩小无序区减少交换比较
			}
			
		}
	}
	
	
}

////////////////////////////////////////////////
void BubbleSort(int r[],n)
{
	int flag=1;//减少不必要的循环
	for(i=0;i<n-1&&flag;i++)
	{
		for(j=n-1;j>i;j--)
		{
			//升序排列
			flag = 0;//
			if(r[j-1]>r[j])
			{
				t=r[j-1];
				r[j-1]=r[j];
				r[j]=t;
				flag=1;//当没有交换变量时不在比较提前退出
			}
		}
	}
//////////////////////////////////////////////