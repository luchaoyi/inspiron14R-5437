//入口
void entry(void) {
	int ret;
/*
 进程初始化时，堆栈保存者环境变量和传递给main的参数
 */
   //1.从进程初始化堆栈获取argc和argv
   int argc;
   char **argv;
   char* ebp_reg=0;
   asm("movl %%ebp,%0 \n":"=r"(ebp_reg)); //ebp->ebp_reg 
   argc = *(int *)(ebp_reg + 4);
   argv = (char**)(epb_reg + 8);
   //2.初始化
   
   //3.c++ 调用全局构造函数
   do_global_ctors();
   //4.
   ret = main(argc, argv);
   //退出清理函数 1.调用注册的退出回调函数 2.syscall os exit 
   exit(ret);
}


void exit(int ret) {
	//...
	//g++实现的c++全局析构函数的实现是利用__cxa_atexit实现的
	//即注册退出回调函数
	//构建一个链表存储函数指针和参数，退出时遍历链表依次执行函数
	crt_call_exit_routine(); 
	//...
}

