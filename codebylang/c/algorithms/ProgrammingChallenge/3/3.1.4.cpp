/*************************************************************************
    > File Name: 3.1.4.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月02日 星期二 20时19分08秒
    > Update Time: 2015年06月02日 星期二 20时19分08秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*  
 *n个物品（w,v)select k个物品 单位重量价值最大
 *  */

//二分搜索目标是单位重量价值 构造判断为单位重量价值>=x

//Evi/Ewi >=x ->Evi>=xEwi->Evi>=Ex*wi ->E(vi-xwi)>=0 
bool C(x)
{
	for(int i=0;i<n;i++)
		y[i]=v[i]-x*w[i];

	//选择k个所以从大开始
	sort(y,y+n);
	double sum=0;

	for(i=0;i<k;i++)
	{
		sum+=y[n-i-1];
	}

	return sum>=0;
}

//二分搜索
