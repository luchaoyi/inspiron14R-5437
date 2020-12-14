//简单字符串散列算法
//BKDR算法


typedef long unsigned long

BKDRHash(const string& str){	
	long seed=31;
	long hashval=0;

	for(i=0;i<str.length();i++){
		hashval=hashval*seed+str[i];
	}
	return hashval % HASHSIZE;
}

//RS 可提供一种随机散列
RS(const string& str){
	long a=31415,b=27183;
	long hasval=0;

	for(i=0;i<str.length();i++){
		hashval=(hashval*a+str[i])% HASHSIZE ;
		a=a*b%(HASHSIZE-1);
	}
}


//FNV1a 散列方法
//可快速处理大量数据并保持较小冲突率


#define FNV_32_INIT ((uint32_t)0x811c9dc5) //const long offsetbasis32=2166136261
#define FNV_32_PRIME((uint32_t)0x1000193)  //const long FNVprime32=16777619


FNV_1a_32bit()
{
	unsigned long hashval=FNV_32_INIT;

	for(){
		hashval=hashval^str[i];
		hashval*=FNV_32_PRIME;//等价于
		//hashval+=(hashval<<1)+(hashval<<4)+(hashval<<7)+(hashval<<8)+(hashval<<24);
		//
	}

	return hashval;
}

FNV1a_64_bit(){
...
}

