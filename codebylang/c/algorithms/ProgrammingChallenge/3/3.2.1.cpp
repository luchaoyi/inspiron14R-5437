/*************************************************************************
    > File Name: 3.2.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月03日 星期三 20时53分54秒
    > Update Time: 2015年06月03日 星期三 20时53分54秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*	tip 1
 *尺取法：对数组保存（起点，终点）下标然后交替推进
 
 
 a0,a1...an-1 S求出总和>=S 的连续子序列的长度的最小值。

 sum(i) = a0+ai-1
 [s,t)  = sum(t) - sum(s); 

 起点确定后可以快速搜索t

 *	*/


int n,S;
int a[MAX_N];


//注意到降低算法循环重数的方法就是多次的同等级循环做一些辅助计算，将问题转化
void  solve()
{

	for(int i=0;i<n;i++)
	{
		sum[i+1]=sum[i]+a[i];
		//注意sum的递推关系而不要傻傻的算
	}

	if(sum[n] < S)
	{
		return -1;
	}

	int res = n;

	//确定起点s搜索范围内t最小值
	for(int s=0;sum[n] - sum[s] >=S;s++)
	{
		...
	}

}

//改进，以as开始总和最初>S 序列 as ...at-1 则  as+1+...at-2<as+..at-2<S
//交替推进s,t
void solve()
{
	int res=n+1;
	int s=0;t=0,sun=0;

	for(;;)
	{
		while(t<n && sum <S)
		{
			sum+=a[t++]; //推进t
		}

		if(sum < S)
			break;

//  as+1+...at-2<as+..at-2<S，此时为以s=0为起点的最短,后面更长不用检查
//  而上面关系可得出s=s+1=1时 -->at-2< S所以下次从t-1开始
		res=min(res,t-s);

		//-a[s]  缩去最初的a[s]从t开始加
		sum-=a[s++];
		
	}
	if (res >n)

		return -1;
}

//尺取循环推进思想,解决连续的问题
//

