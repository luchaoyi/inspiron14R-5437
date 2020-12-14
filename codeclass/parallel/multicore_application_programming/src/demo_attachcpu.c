/*************************************************************************
    > File Name: demo_attachcpu.c
    > Author: lcy
    > Mail: 751714700@qq.com 
    > Created Time: 2017年03月15日 星期三 21时36分16秒
 ************************************************************************/

#include<stdio.h>

#ifdef linux
#include <sched.h>
#include <sys/syscall.h>

pid_t gettid(){
	return syscall(__NR_gettid);
}

int threadbind(int proc){
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(proc,&cpuset);
	//gettid得到本线程id，将本线程绑定到cpuset中，cpuset添加了编号为proc的cpu
	return sched_setaffinity(gettid(),sizeof(cpu_set_t),&cpuset);//设置线程相关性，使它运行到指定虚拟cpu组上
}
#endif

