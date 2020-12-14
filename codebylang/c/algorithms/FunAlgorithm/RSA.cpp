//大整数乘方 a^9 = a^8*a^1  1001 ,a-->a^2-->a^4-->a^8 
//(axb)%n = (a%n+b%n)%n
//模幂-->模乘
CBigInt ModularPower(const CBigInt& M,const CBigInt& E,const CBigInt& N)
{
	CBigInt k =1;
	CBigInt n=M%N;

	for(__int64 i =0;i<E.GetTotoalBits();i++)
	{
		//位===1
		if(E.TestBit(i))
			k=(k*n)%n;
		n=(n*n)%N;
	}
	return k;
}

//米勒-拉宾检验 
//n-1=m*2^k -> m,k


//随机选择a属于1,n-1之间
// a^m%n=1,
// a^(m*2^2r)!=-1 对r属于[0,k-1]每一个值检测,若同时成立则n是一个合数,

// 不成立0.75概率是素数，多次测试 0.25*0.25*...
// 将n-1分解为m*2^k
// 至少5次, 99.9% 

int MillerRabin()
{
	CBigInt m = n-1;
	int k = 0 ;

	//100[1] >>  10[0]遇到最低位==0 stop
	//n-1=m*2^k
	while(!m.TestBit(0))
	{
		m>>=1;
		k++
	}

	for(测试多次)
	{
		a=random(1与n-1之间);
		if(...)
		{
			return 0;
		}
	}
	return 1;//测试多次没有问题
}

//RSA 
//同余: a % n == b % n  a-b=kn
//互素，除了1没有公约数 欧拉数(n) = 小于等于n与n互素的数的个数
//素数的e(n) = n-1
//若n可以分解数两个互素的数 则 e(n)=e(pq)=e(p)e(q) = (p-1)(q-1)

