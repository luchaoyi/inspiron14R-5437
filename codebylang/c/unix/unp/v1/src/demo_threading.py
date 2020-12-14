#coding=utf8

import threading


def hello():
    print "123"
    print threading.currentThread()

#Thread类中start和run的关系
#start->_start_new_thread(self.__bootstrap, ()) 创建线程，设置执行__bootstrap
#__bootstrap->__bootstrap_inner->self.run()->self_target=target


t=threading.Thread(target=hello)
t.run() #没有启动线程直接执行了run
#123
#<_MainThread(MainThread, started 140382391715584)>

t=threading.Thread(target=hello)
t.start() 
#123
#<Thread(Thread-9, started 140381998221056)>



#这个是Thread的run函数，调用后del避免重复调用run
def run(self):
    """Method representing the thread's activity.

    You may override this method in a subclass. The standard run() method
    invokes the callable object passed to the object's constructor as the
    target argument, if any, with sequential and keyword arguments taken
    from the args and kwargs arguments, respectively.

    """
    try:
        if self.__target:
            self.__target(*self.__args, **self.__kwargs)
    finally:
        # Avoid a refcycle if the thread is running a function with
        # an argument that has a member that points to the thread.
        del self.__target, self.__args, self.__kwargs            


#扩展Thread不一定非要重载run方法
#mythread也有target,重点是对类的进一步扩展，添加其它函数或成员
class myThread(threading.Thread):
    def run(self):
        print 'myThread'
        print threading.currentThread()
        
t=myThread()
#重复调用run
t.run()
t.run()
t.start()

t=myThread(target=hello) #指定target为hello,因为run没有调用target因此target没有被执行
t.start()
        
        
    
 

