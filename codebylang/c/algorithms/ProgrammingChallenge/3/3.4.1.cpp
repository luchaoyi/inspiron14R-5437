/*************************************************************************
    > File Name: 3.4.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月07日 星期日 20时39分39秒
    > Update Time: 2015年06月07日 星期日 20时39分39秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*											
 DP解小范围 TSP

 S,已经访问过的点集合 v当前所在点

 dp[S][v] 从v出发访问剩余点，最终回到起点的路径长度


 dp[S][v]=min{dp[S U {u}][u]+d{v,u}]}
 最终答案： 
 dp[空集][0]

 *				*/

int n;
int d[MAX_N][MAX_N];

int dp[1<<MAX_N][MAX_N];


int rec(int S,int v)
{
	if(dp[S][v] >=0)
	{
		return dp[S][v];
	}

	if(S == (1<<n)-1 && v==0)
	{
		return d[S][v];
	}
	//...
	//针对集合：状态压缩DP;
}


/*
 *
 *
 * 集合 {0,1,2,...n-1}
 * //集合编码为整数
 *
 * f(S) = E 2^i i属于S
 *
 * 空集：0
 * 只含有第i个元素
 *
 *
 *
 *加入元素:S|(1<<i) 1左移到第i位
 *去掉元素 :S&~(1<<i) 
 *
 * 交集：S&T
 * 并集：S|T
 * */
