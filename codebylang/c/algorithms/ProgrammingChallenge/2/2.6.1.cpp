/*************************************************************************
    > File Name: 2.6.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月31日 星期日 08时49分11秒
    > Update Time: 2015年05月31日 星期日 08时49分11秒
 ************************************************************************/

#include<iostream>
using namespace std;

int gcd(int a,int b)
{
	if(b==0) return a;

	return gcd(b,a%b);

}

