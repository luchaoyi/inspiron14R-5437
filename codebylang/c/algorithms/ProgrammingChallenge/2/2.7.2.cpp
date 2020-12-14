/*************************************************************************
    > File Name: 2.7.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月01日 星期一 22时23分56秒
    > Update Time: 2015年06月01日 星期一 22时23分56秒
 ************************************************************************/

#include<iostream>
using namespace std;


/*	
 * 0,1矩阵交换为下三角阵，最少交换次数
 *
 * my idea：
          统计每行最后一个1的位置位置决定排序位置越靠前越在前面，则转化为一个排序问题，交换排序只允许顺序交换相邻两个
		  采用插入排序缩小交换范围

1位置:行
 *	*/

int N;
int M[MAX_N][MAX_N]

int a[MAX_N];//第i行最后1出现位置


void solve()
{
	int res = 0;
	
	for(int i=0; i < N;i++)
	{
		a[i] = -1; //若没有1则置-1
		
		for( int j=0; j < N; j++)
		{
			if(M[i][j]==1) a[i] = j;
		}
	}

	//确定可以交换到第一行的，选择最近的
	
	for(int i =0;i<N;i++)
	{
		int pos = -1;

		for(j=i;i<N;i++)
		{
			//最先出现a[j] <=i的即为最近的
			if(a[j] <= i)
			{
				pos = j;

				break;
			}
		}
	}

	for(int j =pos; j>i;j--)
	{
		swap(a[j],a[j-1]);
		res++ ;

	}
	printf("%d",res);
}


