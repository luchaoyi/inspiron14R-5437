/*************************************************************************
    > File Name: 2.3.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月30日 星期六 14时56分03秒
    > Update Time: 2015年05月30日 星期六 14时56分03秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
 * 完全背包问题，物品可以每中多次挑选
 * *
 */


solve()
{
	//物品
	for( i =0 ;i <n;i++)
	{
		//容量
		for(j=0;j<=W;j++)
			//件数
			for(k=0;k*w[i]<=j;k++)
				//优化重复计算 

				//容量为j情况下选择选择第i中i次最大价值 相当k >=1 多选择依次容量变小j=j-w[i]但是还可以选择这个物品i所以相当于
				 //价值相当于dp[i+1][j-w[i]]+v[i] 
				dp[i+1][j] = max(dp[i+1][j],dp[i][j-k*w[i]]+k*v[i]);
	}                      //|
	                       //|
						   //|
						   //|
						   //|
	print dp[n][W]			//|
						   //|
						   //|
						   //| 优化代码在边
}

//动态规划表格化存储双循环实现非常适合
solve()
{
	for(i=0;i<n;i++)
	{
		for(j=0;j<=W;j++)
		{
			if(w[i]>j)
			{
				dp[i+1][j]=dp[i][j];
			}
			else
			{
				dp[i+1][j]=max(dp[i][j],dp[i+1][j-w[i]]+v[i]);
			}
	
		}
	}

	print dp[n][W];

}

//最长上升子序列：即串 S =s1,s2,s3中升序排列的子序列长度
//dp[i] 以ai结尾的 最长上升子序列 
//dp[i] = max(1,dp[j]+1) if(j<i aj<ai))以a[j]结尾的序列


int n;
int a[MAX_N];
int dp[MAX_N];


void solve()
{
	int res = 0;
	for(i=0;i<n;i++)
	{
	
		dp[i] = 1;
		for(j=0;j<i;j++)
		{
			if(a[j]<a[i])
				dp[i] = max(dp[i],dp[j]+1);

		}

		res=max(res,dp[i]);


	}
}
