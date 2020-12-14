#include<pthread.h>
#define MAX_SIZE 100


//利用pthread实现线程池
struct thread_pool{
	Queue<Runable>  task_queue; //任务队列 
	int EXIT_FLAG;
	int nthreads;

	//nthreads 线程数量
	thread_pool(int nthreads){
		this.nthreads=nthreads;
		pthread_t* tids=new pthread_t[nthreads];

		taskqueue=new Queue<Runable>(MAX_SIZE);
		for(int i=0;i<nthreads;i++)
			pthread_create(&tids[i],...,func=task); //指定执行task函数 
		
		for(int i=0;i<nthreads;i++)
			pthread_join(tids[i]); //阻塞等待子线程终止
	}

	~thread_pool(){
		//析构释放资源
	}

//commit递交任务到任务队列并唤醒阻塞在任务队列上的线程
	public void commit(Runable r){
		task_queue.put(r); //递交任务 
		task_queue.signal();//唤醒阻塞在任务队列的线程
	}


//task从任务队列取出任务执行任务,任务队列为空时阻塞
	private void task(){
		Runable *r=NULL;
		for(;;)
		{
			r=task_queue.get();
			if (r==NULL)
				//获取任务失败则线程阻塞
				task_queue.wait();
			r(); //取得任务后执行
		}

	}

	//关闭线程池
	public close(){
		for(int i=0;i<nthreads;i++)
			task_queue.put(r=pthread_exit); //递交任务为pthread_exit线程退出
	}

}

//利用pthread实现Thread对象

class Runable{
public:
	virtual void run()=0;
}

class Thread{
	Runable r;
	pthread_t tid;

	Thread(){...}
	
	Thread(Runable r){
		this.r=r;
	}

	
	void start(){
		pthread_create(tid,func=run,...);
	}

	//start->run->Runable.run
	void run(){
		this.r();
	}
}


//两种使用方法
//1.

class task:Runable{
	void run(){
		...;
	}
}
Thread t=new Thread(new task());
t.start();

//2.
class MyThread:Thread{
	void run(){
		...;
	}
}

Thread myThread=new MyThread();
MyThread.start();
