//无锁递增计数器,线程以自己id调用
volatile int priority = 0;
volatile int counter = 0;
volatile int waiting [2];

//每个线程调用 increment 都发出正在等待进入信号，如果另一个没有在等待
//则直接进入临界区，如果两个都在等待，则其中一个获得优先权，另一个保持等待直到获得优先权

//要保证正确性，需确保前面的存储在加载之前完成
//使用内存屏障

void increment(int id){
	waiting[id]=1;

	//确保waiting[id]=1的存储指令在后面访问 waiting[1-id]之前完成
	#ifdef __sparc
		asm("membar #StoreLoad":::"memory");
	#else
		asm("mfence":::"memory");
	#endif
	
	//two thread
	//other thread is waiting?
	while(waiting[1-id]==1){
		if(priority !=id){
			waiting[id]=0; //waiting[id]=0 then other thread can enter 临界区 
			while(priority !=id) {} //没有获得优先权而阻塞
			waiting[id]=1;
	#ifdef __sparc
		asm("membar #StoreLoad":::"memory");
	#else
		asm("mfence":::"memory");
	#endif
	
		}
	}
	/*临界区
	*/
	counter++;
	//离开 临界区
	priority=1-id;
	waiting[id]=0;

}
