//use cas implement spin lock

void lock_spinlock(volatile int *lock)
{
	//if lock==1 then CAS failed
	while(CAS(lock,0,1)!=0){} //if CAS return not 0,CAS failed,so spin
}
void free_spinlock(volatile int *lock)
{
	*lock=0;
}

//no use atomic operation implement spin lock

void lock_spinlock(volatile int *lock){
	while(*lock==1){} //if *lock is 1 loop  
	*lock=1;         //if *lock !=1,means lock is free ,then  *lcok =1 ,it is means get lock 
}

void free free_spinlock(volatile int * lock){
	*lock=0;
}


//advance
void lock_spinlock(volatile int *lock)
{
	//if lock==1 then CAS failed
	while(CAS(lock,0,1)!=0){} //if CAS return not 0,CAS failed,so spin
	acquire_memory_barrier(); 
}
void free_spinlock(volatile int *lock)
{
	release_memory _barrier();
	*lock=0;
}

int try_spinlock(volatile int *lock){ 
	if(CAS(lock,0,1)==1) {return 0;} //if failed ,it does not spin (== it is not spining) ,return immediately
	else
	{
		acquire_memory_barrier();
		return 1;
	}
}



















