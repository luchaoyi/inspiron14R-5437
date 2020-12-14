/*************************************************************************
    > File Name: 2.2.3.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月29日 星期五 23时18分39秒
    > Update Time: 2015年05月29日 星期五 23时18分39秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*   
 *字符串 S中选取头尾字母加入到T=“”串尾 ->形成字典序尽可能小的字符串
 *
 
  考虑尽早的选取开头结尾中较小的串加入尾部
  对于头尾相等的应该多看一个字符，以便更小的能尽早暴露

  构造S‘为S反转字符串
  S	：S小则S开头取文字，S头小于S尾
  S'：S'小则从S尾取
 
 *   */


int N
char S[MAX_N+1];


void solve()
{

	//			S	 
    //		|         |
	//		a	      b
	int a=0 ,b=N-1;

    int T[MAX_N-1];

	while(a>b){

		i=0;


		/*
		if(S[a])>S[b])
		{
			T[i]=S[b];
			b--;
		}
		else if(S[a]<S[b])
		{
			T[i]=S[a];
			a++;
		}
		else//==*/
		//{
			for(int j=0;a+j<=b;j++)
				if(S[a+j] < S[b-j])
				{

					left=true;
					break;
				}
				else(S[a+j] < S[b-j])
				{
					right=true;
					break;
				}

			if (left) T[i] =S[a++];
			if (right) T[i]=S[b--];

		//}
	

	
	}


}





