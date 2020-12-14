驱动程序
	1.对设备select/poll/epoll需要设备驱动的支持,驱动程序需要提供select/poll/epoll调用的poll函数（驱动提供的poll函数不是select/poll/epoll的poll）,poll->poll_wait->p->qproc=poll_initwait(&table)=__pollwait            
				poll{
                    poll主要实现两个功能
                    1.poll函数调用poll_wait()函数将调用select的用户进程插入到该设备驱动对应资源的等待队列
                    2.返回一个bitmask告诉select当前资源哪些可用
                }
                poll_wait{
                    调用了p->_qproc函数，而p->_qproc被do_select调用poll_initwait(&table)初始化为__pollwait函数
                   	}
                   	
	do_select->poll_initwait->init_poll_funcptr(&pwq->pt, __pollwait)
	sys_epoll_ctl->ep_insert, ->epo_insert->ep_insert->init_poll_funcptr(&epq.pt, ep_ptable_queue_proc)
	epoll和select调用驱动的poll函数，poll->poll_wait->p->_qproc的流程是一致的,但是select的p->_qproc=__pollwait,epoll的p->_qproc=ep_ptable_queue_proc,从p->_qproc后转向的不同的函数，不同的函数注册了不同的驱动唤醒回调函数。
	
                __pollwait
                {
                  1.为调用select的进程生成一个等待队列项等待队列项关联调用select的进程
                  2.init_waitqueue_entry(&entry->wait, current),设置一个唤醒进程的回调函数,此回调函数供驱动使用,当驱动调用wake_up唤醒队列时pollwake被调用,这里pollwake=default_wake_function,调用队列的默认函数用来唤醒睡眠的进程
                  3.add_wait_queue(wait_address,&entry->wait),将为调用select的进程生成的等待队列项插入到设备驱动对应资源的等待队列(注意添加等待队列的动作并不阻塞进程，添加动作只是告知了有进程在等待对应资源)
               }
               
      2.唤醒，设备驱动程序维护自己的读写等待队列,当设备驱动发现资源变为可读写时且有进程睡眠在该资源的等待队列时，调用wake_up()函数唤醒资源等待队列上的睡眠进程.（再次强调，睡眠的进程不是由__pollwait添加等待队列的动作引发的，wake_up->pollwake=default_wake_function。
      
select
        select函数调用过程,select -> sys_select -> core_sys_select -> do_select，core_sys_select函数主要负责把描述符集合用户空间<->内核空间复制
        do_select
        {    
            for(;;){
                1.循环遍历所监测的fd_set内的所有文件描述符，调用对应的驱动程序的poll函数
                2.遍历结束,retval保存了检测到的可操作的文件描述符的个数
                      如果有文件可操作，则跳出for(;;)循环
                    如果没有文件可操作 || timeout时间未到 ||没有信号中断则执行schedule_timeout睡眠,睡眠时间长短由__timeout决定，一直等到该进程被唤醒,唤醒后继续执行for(;;)直到满足跳出循环条件
            }    
        }
        select进程在do_select中引发睡眠，而睡眠前调用了由驱动提供的poll将自身添加到了驱动等待队列，select进程由驱动在资源就绪时唤醒select进程。

select缺点
1）每次调用都需要要把描述符集合从用户空间copy到内核空间，检测完成之后，又要把检测的结果集合从内核空间copy到用户空间,2次复制。
2)多次线性遍历
    1.首先应用程序遍历描述符，把他们加到fd_set集合里，然后调用select/poll这是应用层的一次遍历.
    2.进入内核空间，do_select先进行一次遍历调用每个描述符的poll回调检测.
    3.若第一次遍历没发现就绪描述符加入等待队列,第二次是有资源就绪被唤醒,再调用poll遍历一遍收集信息.
    4.select返回后应用程序再次遍历所有描述符，FD_ISSET检测结果集.

3）描述符数量限制，poll没有限制，select有1024的硬性限制，可修改内核增大限制。

linux特有epoll     
    epoll机制分为3个函数epoll_create,epoll_ctl, epoll_wait
            1.epoll调用epoll_create在内核建立一个epoll对象
            2.然后使用epoll_ctl向对象中添加，删除，修改感兴趣的事件，
            3.epoll_wait等待描述符事件
            
	epoll_ctl添加的事件保存在epoll对象维持的红黑树的结构中，可以很高性能的实现删除/修改/添加/查找。
   	epoll_ctl添加事件时修改了驱动函数wake_up调用的回调函数，此回调函数(wake_up->pollwake=default_wake_function，select中驱动检测描述符就绪时使用的是default_wake_function执行唤醒 ，这里回调函数被更改为另一个函数)将就绪的描述符直接添加到了epoll对象维持的一个双向链表中,并唤醒阻塞在读就绪链表的进程，而epoll_wait只需要检查就绪链表是否为空，不为空直接将链表中的事件复制到用户态,如果链表为空，则阻塞。
    epoll_ctl添加事件时调用了驱动的poll函数检查就绪状态，就绪则添加到就绪链表,所有的事件就绪描述符都在双向链表中。

    当epoll_wait检查就绪链表为空时，需要阻塞调用epoll_wait的进程，因此当就绪链表非空时需要有个回调函数可以唤醒睡眠在epoll_wait上的进程,因此epoll对象需要维持一个因为调用epoll_wait等待就绪双向链表非空而睡眠的队列，向就绪链表添加对象时调用回调函数唤醒睡眠的等待进程。
    epollfd关联了内核为epoll创建的虚拟文件系统中的一个文件，因此epollfd也是一个文件描述符，因此epollfd自身也可以被select/poll/epoll(epoll),因此epollfd也需要实现poll，而poll调用的poll_wait也需要一个等待队列，因此epoll对象中有两个等待队列。
    
部分代码
 struct eventpoll {

... ...

/* Wait queue used by  sys_epoll_wait()*/

wait_queue_head_t wq; // epoll_wait->sys_epoll_wait()的等待队列 


  /* Wait queue used by file->poll() */
  wait_queue_head_t poll_wait; // epollfd自身的poll的等待队列 ，epollfd被select/poll/epoll时调用epollfd的poll()函数时所使用的等待队列

/* List of ready file descriptors */
  struct list_head rdllist;      //描述符就绪队列，挂载的是 epitem结构 

  /* RB tree root used to store monitored fd structs */
  struct rb_root rbr; //存储 新添加的描述符的红黑树根， 此成员用来存储添加进来的所有描述符。挂载的是epitem结构

... ...
};

SYSCALL_DEFINE1(epoll_create1, int, flags)  
{  
    int error, fd;  
    struct eventpoll *ep = NULL;  
    struct file *file;  

   ... ...
    error = ep_alloc(&ep);    //申请一个 eventpoll对象
   ... ... 
      // 返回struct file关联ep对象，并传入eventpoll的文件操作指针eventpoll_fops,文件操作指针实现了对文件的操作方法

    //系统调用对设备文件的操作是调用了由设备文件提供的操作方法,即设备文件告诉系统调用自己应该怎样被操作
    file = anon_inode_getfile("[eventpoll]", &eventpoll_fops, ep,  
                              O_RDWR | (flags & O_CLOEXEC));  
    if (IS_ERR(file)) {  
        error = PTR_ERR(file);  
        goto out_free_fd;  
    }  

//fd关联file,file关联ep对象，因此可以通过epollfd找到file进而找到eventpoll对象
    fd_install(fd, file);  
    ep->file = file;  
    return fd;  
out_free_fd:  
    put_unused_fd(fd);  
out_free_ep:  
    ep_free(ep);  
    return error;  
}  

总结
    驱动程序要为select/poll/epoll机制提供一个poll方法，poll方法提供设备就绪状态的查询，以及未就绪时添加进程到等待队列，select/poll/epoll要为驱动程序提供一个回调函数，回调函数实现了select/poll/epoll进程的唤醒。即驱动程序告知select/poll/epoll自己如何被监听，select/poll/epoll告知自己如何被唤醒,而select/poll/epoll的睡眠是没有就绪设备时自己主动选择睡眠。
    select第一次遍历调用poll,就绪则直接返回，否则睡眠，唤醒后再次遍历
    epoll_ctl每次插入一个事件时调用poll就绪则放入就绪链表
    epoll_wait从就绪链表取描述符事件，空则阻塞，被唤醒时回调函数已经将描述符放置到了就绪链表，因此只看就绪链表
