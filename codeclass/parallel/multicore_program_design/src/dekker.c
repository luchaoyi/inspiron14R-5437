//dekker 用在没有硬件支持原子读-改-写操作的情况下实现临界区

enum state {UNLOCKED,LOCKED};

//dekker算法实现双cpu自旋锁
typedef struct {
	char status[2]; //每个cpu的状态
	char turn; /*发生僵局时下一步哪个cpu执行*/
} lock_t;


initlock(lock_t *lock)
{
	lock->status[0]=UNLOCKED;
	lock->status[1]=UNLOCKED;
	lock->turn = 0;
}

void lock(volatile lock_t *lock)
{
	lock->status[cpuid()]=LOCKED; //置锁定状态

	//判断
	while(lock->status[othercpu()]==LOCKED){
		if(lock->turn!=cpuid()){
			lock->status[cpuid()]=UNLOCKED;
			while(lock->turn==othercpu())
				;
			lock->status[cpuid()]=LOCKED;  /*再试*/
		}
	}

}

void unlock(lock_t *lock)
{
	lock->status[cpuid()] = UNLOCKED;
	lock->turn=othercpu();
}


