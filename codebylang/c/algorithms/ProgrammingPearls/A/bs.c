typedef int DataType
int n;
DataType x[MAXN];


int binarysearch(DataType t)
{
	int l,h,m;
	l=0;
	h=n-1;

	while(l<=m)
	{
		m=(l+h)/2;
		if(x[m]<t)
			l=m+1;
		else if (x[m==t])
			return m;
		else
			h=m-1;
	}

	return -1;
}


//assert在程序中加入断言，判断程序正确性,指导代码开发
