/*************************************************************************
    > File Name: 2.7.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月01日 星期一 22时06分44秒
    > Update Time: 2015年06月01日 星期一 22时06分44秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*			
 *X={x1,x2,..xn} Y={y1,y2,...yn}
 *X,Y分量可交换则<X,Y>最小多少？
 

 my idea:直观上看将大的与小的分量相乘可以保证最小 建立排序或优先队列
 
 答案：我的想法是正确的。
 */


typedef long long ll;
int n;
int v1[MAX_N],v2[MXA_N];



void solve()
{
	sort(v1,v1+n);
	sort(v2,v2+n);

	for(i=0;i<n;i++) ans+=v1[i]*v2[n-i-1];
	
	printf("%d",ans);
}
