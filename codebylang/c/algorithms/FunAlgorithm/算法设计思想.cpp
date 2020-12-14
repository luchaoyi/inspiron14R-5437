/*
n位M进制，按k位分解大整数 x=x1*M^k+x0 ,y=y1*M^k+y0
x*y=x1y1M^2k + (x1y0+x0y1)*M^k+x0y0
(x1y0+x0y1)=(x1+x0)(y1+y0)-x1y1-x0y0 
*/

//递归分解,分治法
CBigInt Karatsuba(const CBigInt& mul1,const CBigInt& mul2)
{
	if(mul1.GetBigNCount())==1||mul2.GetBigNCount()===1)
	{
		return mul1*mul2;
	}

	unsigned int k = max(mul1.GetBigNCount()),mul2.GetBigNCount())/2;
	high1=mul1[n-1:k]<<k; 
	low1=mul1[k-1:0];
	high2=...
	low2=...

	CBigInt z0=Karatsuba(low1,low2);
	CBigInt z2=Karatsuba(high1,high2);
	CBigInt z1=Karatsuba(low1+high1,low2+high2);

	CBigInt z3=z1-z0-z2;

	z2=z2<<2*k;
	z3=z3*<<k;

	return z2+z3+z0;
}


//动态规划
//字符串编辑距离，str1-->str2 插入，删除替换操作，最少的次数，编辑距离
int EditDistance(char* src,char* dst)
{
	//
	if(strlen(src)==0||strlen(dst)==0)
		return abs(strlen(src)-strlen(dst));

	//当前字符相等，看下一个字符
	if(src[0]==dest[0])
		return EditDistance(src+1,dest+1);

	edIns =EditDistance(src,dest+1)+1; //src插入了一个字符串,并没有真正执行插入操作，只是假设插入，计算EditDistance 
	edDel = EditDistance(src+1,dest)+1;//
	edRep = EditDistance(src+1,dest+1)+1;


	return min(min(edIns,edDel),edRep);
}

//动态规划，src[1:n] --> dest[1:m]  子问题 src[1:i] -->dest [1:j]
//src[i]=dest[j] d[i][j]=d[i-1][j-1],不需要编辑
//d[i][j] =  min三种操作 
//动态规划程序采样带记忆的递归程序实现比价容易
int EditDistance(char *src,char * dest)
{
	int i,j;
	int M=strlen(src);
	int N=strlen(dest);

	int d[MAX_STRING_LEN][MAX_STRING_LEN]={0xffff};

	for(i=0;i<=M;i++) d[i][0]=i;
	for(j=0;j<=N;j++)d[0][j]=j;

	for(i=1;i<=M;i++)
	{
		for(j=1;j<=N;j++)
		{

			if(src[i-1]==dest[j-1])
			{
				d[i][j]=d[i-1][j-1];

			}
			else
			{
				int edIns = d[i][j-1]+1; //d[i,j]j多了一个字符,src插入
				int edDel = d[i-1][j]+1; //d[i,j]i少了一个字符,src删除 
				int edRep = d[i-1][j-1]+1;
				d[i][j]=min(min(edIns,edDel),edRep);
			}
		}
	}

	return d[M][N];
}

//穷举搜索+剪枝
//...
