void InsertSort(int r[],int n)
{
    //r0保存ri值做哨兵
    for(i=2;i<=n;i++)
    {
        r[0]=r[i];
        for(j=i-1;r[0]<r[j];j--)//升序 大的 后移
        {
            r[j+1]=r[j];
        }
        //到位j后卫移动的空位：j+1
        r[j+1]=r[0];
    }

}
////////////////////////////////////////////

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
			for(j=i-1;j>=0&&temp<r[j];j--)
				r[j+1]=r[j];
			r[j+1]=temp;
		}
		//r[i]>r[i-1]不用挪不用比较
		
	}
}

