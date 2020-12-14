//串行
memset(hist,0,256*sizeof(int));
for(int i=0;i<numPixs;i++){
	hist[pixs[i]]++;
}

//openmp
#pragma omp parallel for shared(numPixs,hist,pixs)
for(int i=0;i<numPixs;i++){
	unsigned char pix=pixs[i];
#pragma omp atomic
	hist[pix]++;
}

//openmp
//减少冲突，为每个线程分配一个数组
int numThreads=omp_get_num_procs();
int *h(int *)malloc(sizeof(int)*256*omp_get_num_procs);
//memset h 0
#pragma omp parallel shared(numPixs,h,pixs,hist) num_threads(numThreads)
{
	int id = omp_get_thread_num();

#pragma omp for
	for(int i=0;i<numPixs;i++){
	unsigned char pix=pixs[i];
	h[id*256+pix]++;
	}

#pragma omp for
	for(int i=0;i<256;i++){
		for(int id=0;id<numThreads;id++){
			hist[i]+=h[id*256+i];
		}
	}
}




