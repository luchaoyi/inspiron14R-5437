/*************************************************************************
    > File Name: kmp.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月26日 星期二 20时28分06秒
    > Update Time: 2015年05月26日 星期二 20时28分06秒
 ************************************************************************/


void getnext(String T,int *next)
{

//init 
i=1; //后缀 相对的
j=0; //前缀	是固定的

//i指向后缀
//j指向前缀

next[1] = 0;
 
//next,数组指导匹配失败时该回朔的位置
while(i < T[0])
{
	 
	 //匹配
if (0==j || T[i] == T[j])
{
	i++;
	j++;

	next[i] = j;

	//相加后相等前后相等
	//ex:aaaaaa
	//则等过去
	if(T[i] != T[j])
	{
		 next[i]=j;
	}
	else
	{
		next[i] = next[j];

	}
}
                                                       
 //不匹配
else
{
	j=next[j]; //将前缀回溯到上一次匹配位置
}

}

}

//从pos开始索引，寻找

int index_KMP(String S,String T,int pos)
{
	int i =pos;
	int j =1;
	int next[255];

	get_next(T,next);

	while(i <= S[0] && j<= T[0])
	{
		if(0==j ||S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			//指导回朔位置
			j=next[j];
		}

		if(j>T[0])
		{
			//匹配成功
			return i-T[0]
		}
		else
		{
			return 0
		}
	}


}


/**
匹配
if()
{
	
}
else
{
	next 指导失配位置
	失配则 j=next[j]
}

**/
