static size_t NFS_LineSize=128 //Cache行长度
size_t NFS_GetLinesize(){
	return NFS_LineSize;
}


// n 元素个数
// element_size 元素size
void *NFS_Allocate(size_t n ,size_t element_size,void *hint)
{
	size_t m = NFS_GetLinesize();
	size_t bytes=n*element_size;
	unsigned char* base;

	if(bytes<n || bytes +m <bytes ||
			!(base=(unsigned char *)(bytes>=BigSize?malloc(m+bytes):(*MallocHandler(m+bytes))))
			)
	{
		//overflow
		//throw std::bad_alloc();
	}

	/*
	 *(a+m)&(-m) = 大于a的m的整数倍中最接近m的数
	    In [9]: (1+128)&(-128)
		Out[9]: 128
		In [10]: (129+128)&(-128)
		Out[10]: 256
		In [11]: (257+128)&(-128)
		Out[11]: 384
	*/

	unsigned char * result=(unsigned char*)((uintptr)(base+m)&-m);
	//...
	return result;
}

