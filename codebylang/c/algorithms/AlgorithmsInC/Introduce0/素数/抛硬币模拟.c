#incldue<stdio.h>
#incldue<stdlib.h>

int heads()  //p=1/2概率模拟
{
	return rand()<RAND_MAX/2;
}

int main()
{
	int i,j,cnt;
	int M=1000,N=32; 
	
	int f[33];//保存实验结果0-32次正面的频数
	
	for(i=0;i<=N;i++) f[i]=0;
	
	for(i=0;i<M;i++)//1000次实验
	{
		for(cnt=0,j=0;j<=32;j++)//抛32次
		{
			if(heads())//出现正面
			{
				cnt++;//cnt统计出现正面次数
			}
		}
		//实验做完cnt为正面朝上次数f[cnt]正面出现cnt次频数+1;
		f[cnt]++;
	}
	//打印10次打印一个*
	for(i=0;i<=N;i++)
	{	printf("%2d",i);	
		for(j=0;j<=f[i];j+=10) printf("*");
		
		 printf("\n");	
	}
	return 0;
}
