//根据CPU,Cache规则计算Cache行首地址
//首地址相同则位于同一个Cache
//Intel Cache行首地址是Cache行大小整数倍

#include<iostream>

void* GetCacheAlignAddr(void *pAddr);

#define CACHE_LINE_SIZE 64

void* GetCacheAlignAddr(void *pAddr){
	int m=CACHE_LINE_SIZE;
	void *pRet=(void *)((reinterpret_cast<int>(pAddr)+m-1)&(-m) );
	return pRet;
}

