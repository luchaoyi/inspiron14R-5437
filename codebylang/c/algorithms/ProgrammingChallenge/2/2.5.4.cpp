/*************************************************************************
    > File Name: 2.5.4.cpp
	A
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月30日 星期六 22时05分29秒
    > Update Time: 2015年05月30日 星期六 22时05分29秒
 ************************************************************************/

#include<iostream>
using namespace std;

struct edge{int from ,to,cost;};

edge es[MAX_E] //边
int V,E;


void short_path()
{
	for (int i =0 ;i<V;i++) d[i] = INF;
	d[s] = 0;

	while(true)
	{
		bool update = false;
		for(i=0;i<E;i++)
		{
			edge = es[i];

			if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost)
			{
				d[e.to] = d[e.from]+e.cost;
				update = true;
			}

			if(!update) 
				break;
		}
	}
}
