#!coding:utf8



#线程模块
#thread:提供有限线程能力,适合小项目,也会增加额外资源消耗
#threading: 更强大,高层次线程支持




import thread 
import time



def print_time(threadName,delay):
    count=0
    while count<5:
        time.sleep(delay)
        count+=1
        print "%s:%s" % (threadName,time.ctime(time.time())) 
        if delay==2 and count ==2:
            thread.exit()

global_value=0

def run(threadName,lock):
    global global_value
    lock.acquire() #请求锁,需要等待则等待
    lock_copy=global_value
    print "%s with value %s" %(threadName,lock_copy)
    global_value=lock_copy+1
    lock.release() #释放锁



def demo0():
    try:
        #传入运行函数，参数元组，命名参数字典
        thread.start_new_thread(print_time,("Thread-1",2,))
        thread.start_new_thread(print_time,("Thread-2",4,))
    except:
        print "Error:unable to start thread"

    while 1:
        pass

def demo1():
    lock=thread.allocate_lock() #allocate_lock返回线程锁对象
    for i in range(10):
        thread.start_new_thread(run,("Thread-"+str(i),lock))

    while 1:
        pass



#--------threading-------
import threading
#threading模块把线程内容封装在一个类中，实例化类使用线程
#简单使用方:直接实例化threading.Thread 

def demo3():
    lock=threading.Lock()
    for i in range(10):
        t=threading.Thread(target=run,args=("Thread-"+str(i),lock))#创建线程对象
        t.start() #trigger


#复杂的方法:封装自己的线程类,继承threading.Thread并扩展

class MyThread(threading.Thread):
    def __init__(self,count):
        threading.Thread.__init__(self)
        self.total=count
    def run(self):
        for i in range(self.total):
            time.sleep(1)
            print "Thread: %s - %s" %(self.name,i)


def demo4():
    t1=MyThread(4)
    t2=MyThread(3)
    t1.start()
    t2.start()

    t1.join() #等待t1线程结束
    t2.join() #如果不等待结束则print finished会在t1和t2的run结束前运行

    print "program finished"


#--------threading的Event对象--------------
#Event对象包含一个内部标记
#set is set flag
#clear  is clear flag 
#is_set is is set flag ?
#wait wait until set 

class ThreadA(threading.Thread):
    def __init__(self,event):
        threading.Thread.__init__(self)
        self.event=event
    def run(self):
        count=0
        while count<5:
            time.sleep(1)
            if self.event.is_set():
                print "A"
                self.event.clear()
            count+=1


class ThreadB(threading.Thread):
    def __init__(self,event):
        threading.Thread.__init__(self)
        self.event=event
    def run(self):
        count=0
        while count<5:
            time.sleep(1)
            if not self.event.is_set():
                print "B"
                self.event.set()
            count+=1


def demo5():
    event=threading.Event()
    #A,B共享event对象
    #A and B  self.event->event 
    ta=ThreadA(event)
    tb=ThreadB(event)
    ta.start()
    tb.start()



if __name__=="__main__":
    #demo0()
    #demo1()
    #demo3()
    #demo4()
    demo5()

