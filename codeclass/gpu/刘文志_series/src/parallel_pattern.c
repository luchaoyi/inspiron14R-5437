//2范数,平方->求和->开根

//map 模式,对每个数据施加同样操作,数据并行的特征
inline float(float d){
	return d*d;
}

//计算平方
void computeSqure(int len,const float * __restrict__ in,float * restric out){
	for(int i=0;i<len;i++){
		out[i]=map(in[i]);
	}
}

//SIMD指令实现,SIMD很适合实现map模式并行
//ARM NEON实现
void computeSqure(int len,const float * __restrict__ in,float * restric out){
	int end=len-len%4; // 指令一次加载16字节数据

#pragma omp parallel for  //并行for循环
	for(int i=0;i<end;i+=4) 
	{
		//32*4=4个32bit浮点数=16字节 
		float32x4_t a=vldlq_f32(in+i); //in+i起始地址
		a=vmulq_f32(a,a);//vector mul
		vstlq_f32(out+i,a);
	}
	//4B对齐后,剩余的
	for(int i=end;i<len;i++){
		out[i]=map(in[i]);
	}
}

//reduc模式,对前面平方求和

float computeSum(int len,const float * restric out){
	float sum=0
	for(int i=0;i<len;i++){
		sum+=out[i];
	}
	return sum;
}

float computeSumNEON(int len,const float *restric out){
	int end=len-len%4;
	float32x4_t sum=vdupq_n_f32(0.0f);
	for(int i=0;i<end;i+=4){
		float32x4_t a = vldlq_f32(out+i); //加载vector
		sum=vaddq_f32(sum,a);//向量对应加
	}
	float ret=0.0f;
	for(int i=end;i<len;i++){
		ret+=out[i]
	}
	ret+=(sum[0]+sum[1])+(sum[2]+sum[3]);
	return ret;
}

