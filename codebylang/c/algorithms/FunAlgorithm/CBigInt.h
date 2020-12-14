#ifndef CBIGINT_INCLUDED
#define CBIGINT_INCLUDED

Class CBigInt
{
    unsigned int m_sign;
    unsigned  int m_length;
    //实现大数为2^32进制，数组存储每一位
    //低位保存超过2^32-1,向高位进1，高位增加
	//数组存储数字从低位-->高位
    unsigned long m_value[MAX_BI_LEN];

}


//无符号+
void CBigInt::Add(const CBigInt& value1,const CBigInt& value2,CBigInt& result)
{
	result=value1;

	unsigned carry=0
	//结果位数,应该是多的
	if(result.m_length<value2.m_length)
	{
		result.m_length=value2.m_length;
	}

	for(unsigned int i=0;i<result.m_length;i++)
	{
		unsigned __int64 sum=value2.m_value[i];
		sum+=value1,m_value[i]+carry;

		//32位进位被截断
		result.m_value[i]=(unsigned long)sum;
		carry=sum>>32;   
	}

	//carry=0 or 1
	result.m_value[m_length]=carry;
	result.m_length+=carry
}

//无符号数减，保证大数减小数正确
// value1 - value2
// must value1 > value2
void CBigInt::Sub(const CBigInt& value1,const CBigInt& value2,CBigInt& result)
{
	result=value1;
	unsigned borrow=0
	//结果位数,应该是多的

	for(unsigned int i=0;i<result.m_length;i++)
	{
		//不产生借位情况
		if((r.m_value[i]>value2.m_value[i])||(r.m_value == value2.m_value[i] && borrow==0))
		{
			r.m_value[i]-=value2.m_value[i];
			borrow=0;
		}
		//不够需借位
		else
		{
			unsigned __int64 temp=r.m_value[i]+0x100000000;
			r.m_value[i]=(unsigned long)temp-value2.m_value[i]-borrow;
			borrow=1;
		}

	}

	while(result.m_value[result.m_length-1]==0 && result.m_length>0)
		result.m_length--;

}


//有符号+
CBigInt CBigInt::operator+(const CBigInt& value) const
{
	CBigInt r;
	//同符号 
	if(m_sign == value.m_sign)
	{
		CBigInt::ADD(*this,value,r);
		r.m_sign=m_sign;
	}
	//非同号
	else
	{
		//this > value
		int cf=CompareNoSign(value);
		if(cf>0)
		{
			CBigInt::Sub(*this,value,r);
			r.m_sign=m_sign
		}
		else if(cf==0)
		{
			r.m_length=1;
			r.m_value[0]=0
			r.m_sign=0;
		}
		//this < value
		else 
		{
			CBigInt::Add(value,*this,r);
			r.m_sign=value.m_sign;
		}
	}

	return r;
}


//
void CBigInt::Mul(const CBigInt& value1,const CBigInt& value2,CBigInt& result)
{
	unsigned __int64 carry=0;
	result.m_length=value1.m_length+value2.m_length;

	//
	for(unsigned int i=0;i<result.m_length;i++)
	{

	}
}


//大整数乘方 a^9 = a^8*a^1  1001 ,a-->a^2-->a^4-->a^8 
#endif // CBIGINT_INCLUDED
