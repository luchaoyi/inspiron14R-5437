/*************************************************************************
    > File Name: 2.6.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月31日 星期日 09时04分14秒
    > Update Time: 2015年05月31日 星期日 09时04分14秒
 ************************************************************************/

#include<iostream>
using namespace std;


//素数 2-(n)^1/2范围内

bool is_prime(int n);
{


	for(i=0;i*i<=n;i++)
		if(n%i == 0 ) return false;
}

//约数枚举
vector <int> divisor(int n){
	vector<int> res;
	for(i=0;i*i<=n;i++)
	{
		if(0 == n%i)
		{
			res.push(i);
			if(n/i!=i)
				res.push(n/i);


		}
	}
	return res;
}


//筛数法：
//

int prime[MAX_N]
bool is_prime[MAX_N+1];

int sieve(int n)
{
	for(i=0;i<=n;i++) is_prime[i] = true;//初始假定都是素数
	is_prime[0]=is_prime[1] = false;

	for(int i=2;i<=n;i++)
	{
		if (is_prime[i] )
		{
			for(j=2*i;j<=n;+=i)
			{
				is_prime[j] = false;
			}
		}
	}
}

// x^22 = x16*x4*x2  
						

//(a*b*c)%n  ((((a%n)*b)%n)*c)%n
res=1;
while(n>0)
{

	if(n&1) res=res*x;
	x=x*x;  //x-x^2->x^4->x
}
