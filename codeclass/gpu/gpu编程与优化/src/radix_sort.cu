//基数排序，按位比较排序
//从低位到高位则是在全局排序
//若从高到低位则会按取值划分为一段一段的排序，如按二进制串排序，可以从高位将为0排在为1前，然后划分为两段在两段内排序,不能在全局了


//数值按二进制位排序
//n个元素排序
void radix_sort(base_int *arr,base_int n){
//0 and 1两个桶
	base_int *tmp_0,*tmp_1;

	tmp_0=(base_int *)malloc(sizeof(base_int)*n);
	tmp_1=(base_int *)malloc(sizeof(base_int)*n);

	//32 bit 
	for(base_int bit=0;bit<32;bit++){
		base_int base_0=0;
		base_int base_1=0;


		//装桶
		for(i=0;i<n;i++){
			x=arr[i];

			base_int bit_mask=(1<<<bit);
			if (x&bit_mask)>0
			{
				//此位1 
				tmp_1[base_1]=x;
				base_1++;
			}
			else
			{
				tmp_0[base_0]=x;
				base_0++;
			}
		}

		//分发到原数组

		for(i=0;i<base_0;i++)
			arr[i]=tmp_0[i];

		for(i=0;i<base_1;i++){
			arr[i+base_0]=tmp_1[i];
		}

	}
}


//优化可以节省一个桶，用原数组作为tmp_0,还可以减少移动复制
//数值按二进制位排序
//n个元素排序
void radix_sort(base_int *arr,base_int n){
//0 and 1两个桶
	base_int *tmp_1;
	tmp_1=(base_int *)malloc(sizeof(base_int)*n);

	//32 bit 
	for(base_int bit=0;bit<32;bit++){
		base_int base_0=0;
		base_int base_1=0;


		//装桶
		for(i=0;i<n;i++){
			x=arr[i];

			base_int bit_mask=(1<<<bit);
			if (x&bit_mask)>0
			{
				//此位1 
				tmp_1[base_1]=x;
				base_1++;
			}
			else
			{
				//在arr原地装入为0的元素
				arr[base_0]=x;
				base_0++;
			}
		}

		//分发到原数组
		for(i=base_0;j<base_0+base_1;j++){
			arr[i]=tmp_1[i-base0];
		}
	}
}


//基数排序GPU并行
//只是将数据分段划分到不同线程处理，不同线程串行基数排序，同一线程串行执行基数排序，然后将分段结果合并

//gpu线程分段不是将连续的一段划分到一个线程，根据访问特性连续的不同线程访问连续地址
//一个线程应该按线程索引分段，跳跃性的分段

__device__ void radix_sort(base_int *arr,base_int n,base_int *tmp_1,base_int tdim)
{
	//32 bit 
	for(base_int bit=0;bit<32;bit++){
		base_int base_0=0;
		base_int base_1=0;
		base_int bit_mask=(1<<bit)
		//装桶
		//共tdim个线程,以它为跨度
		for(i=0;i<n;i+=tdim){
			x=arr[i+tid];
			if (x&bit_mask)>0
			{
				//此位1 
				tmp_1[base_1+tid]=x;
				base_1+=tdim;
			}
			else
			{
				arr[base_0+tid]=x;
				base_0+=tdim;
			}
		}


		for(i=0;i<base_1;i+=tdim){
			arr[i+base_0+tid]=tmp_1[i+tid];
		}
	}
}

