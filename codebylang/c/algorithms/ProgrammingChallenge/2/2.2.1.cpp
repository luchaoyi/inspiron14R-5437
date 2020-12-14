/*************************************************************************
    > File Name: 2.2.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月29日 星期五 22时37分00秒
    > Update Time: 2015年05月29日 星期五 22时37分00秒
 ************************************************************************/

#include<iostream>
using namespace std;

/* 贪心算法：是一种简单粗暴的短视策略
 *
 * 例:硬币 1,5,10,50,500 有 c1,c5,c10,c50,c500枚，A元最少硬币
 */

const int V[6] ={1,5,10,100,500}

int C[6];
int A;


void solve()
{
	int ans = 0;
	for (i=5;i>=0;i--)
	{
		int t = min(A/V[i],C[i]); //个数
		A-=t*V[i];
		ans +=t;


	}
}