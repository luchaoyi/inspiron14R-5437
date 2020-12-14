/*************************************************************************
    > File Name: 3.2.4.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月06日 星期六 16时43分20秒
    > Update Time: 2015年06月06日 星期六 16时43分20秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
 折半枚举：抽签问题
四个数列取数求出 ai+bj+cm+cn=K所有组合个数
 A
 B
 C
 D
 
 n2
 计算a+b c+d

 排序后可以固定一个，都另一个二分搜索
 a+b=K-(c+d)
 */


void solve()
{
	int res=0;

	for
		for
			CD=C[i]+D[j];
	sort(CD,CD+n*n);

	for
		for
			temp=A[i]+B[j];
			{
				//二分搜索
				//搜索到返回1 res+=1
				res+=search(K-temp,CD);
			}
}

//重量太大，或价值太大时背包问题 章节2Dp ,O(nW),换一种方式
//n较小采用搜索,折一半
