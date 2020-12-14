/*************************************************************************
    > File Name: 1.6.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月27日 星期三 22时37分14秒
    > Update Time: 2015年05月27日 星期三 22时37分14秒
 ************************************************************************/

#include<iostream>
using namespace std;



//三角形约束
//c<a+b -->c-a<b 


int n;
int a[MAX_N];

void solve()
{

	int i,j,k;
	//注意 i,j,k
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			for (k=j+1;k<n;k++)
			{ 

				int len= a[i]+a[j]+a[k];

				int max_a=max(a[i],max(a[j],a[k]));

				//最大的max_a < 其它两边之和

				//计算其它两边之和技巧
				if(max_a < (len-max_a))
				{
					//Update

					ans=max(ans,len);
				}

			}
		}
	}

	//print ans

}
