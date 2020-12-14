/*************************************************************************
    > File Name: 3.1.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月02日 星期二 19时40分34秒
    > Update Time: 2015年06月02日 星期二 19时40分34秒
 ************************************************************************/

#include<iostream>
using namespace std;

/* 
 *切割绳子 ，要求从N条绳子中切割得到K条等长绳子，求绳子长度最长多少
 *
 *切割绳子范围为 从0  ->min(Li) 即原始绳子中最长的为上界，从中搜素是否满足切出k条
 *
 * */


N=4
K=11
//L={8.02,7.43,4.57,5.39}
L=[MAX_N]


//构造判断转化为搜索问题
//判断是否满足条件，二分搜索快速逼近
int C(double x)
{
	num=0;
	for(i=0;i<N;i++)
	{
		num+=int(L[i]/x);
	}

	return num>=k;

}

//二分搜索
void solve()
{

	minL=0;
	//原始绳子最长的肯定不满足切出来是0条
	maxL=max(L);
	if(K<=1)
		return maxL;

	for(int i ;i<100;i++)
	{
		mid=(maxL+minL) / 2;

		if(C(mid))  minL=mid;
		else maxL=mid;
	}

	return floor(ub * 100) / 100;
}
