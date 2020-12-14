/*
 *BFS use queue
 *DFS use stack
 *将相邻节点加入queue or stack 中，多个线程从其取出任务，使用任务队列的并行化方法
 * 需要实现一个线程安全的queue or stack
 *
 * 已访问节点需要使用一个visited数组标记,对数组多个线程同时r/w，需要加锁保护
 *
 * visited 是一个更新一次多次读取的数组,符合r/w锁,但是临界区太小，不能体现出其性能优势
 *
 * 锁的数量:
 *	 使用单个锁来保护则竞争激烈
 *	 使用每个元素/锁则内存占用太大
 *
 *	 可以
 *		将数组分段，则每段一个锁
 *		对下标取模，则同模竞争一个锁(这个更好，相邻元素，可能同时访问概率更大，因此同模竞争情况可能更少
 * */



j=k%NUM_LOCKS;
pthread_mutex_lock(&Vmutex[j]);
	lVisted=visited[k];
pthread_mutex_unlock(&Vmutex[j]);
if(!lVisted){  //这段代码在进行 lVisted判断时，可能有线程会更新lVisted,出现错误
	pthread_mutex_lock(&Vmutex[j]);
	visited[k]=1;
	pthread_mutex_unlock[&Vmutex[j]];

	//...
	//访问操作
}


j=k%NUM_LOCKS;
pthread_mutex_lock(&Vmutex[j]);
	if(!visited[k])
{
		iWillVisit=1; //将visited的访问全移交到一个线程手中
		visited[k]=1;//并将此后的路堵死
	
}
pthread_mutex_unlock(&Vmutex[j]);
if(iWillVisit){  
	//...
	//访问操作 
}
