#!coding:utf8
#每个进程有不同的GIL，可以并行
#进程不共享资源，因此消耗更多内存，IPC(进程通信)更复杂

import multiprocessing

def run(pname):
    print pname

# multiprocessing.Process类用法和threading,Thread类似
def demo0():
    for i in range(10):
        p=multiprocessing.Process(target=run,args=("Process-"+str(i),))
        p.start()
        p.join()


#进程结束or中断产生一个退出码:
#0 正常完结
#>0 异常完结
#<0 被另一个进程中断

import time 
def demo1():
    def first():
        print "There is no problem here "

    def second():
        raise RuntimeError("Error raised!")
    def third():
        time.sleep(3)
        print "This process will be terminated"

    workers=[ \
            multiprocessing.Process(target=first), \
            multiprocessing.Process(target=second), \
            multiprocessing.Process(target=third), \
            ]
    for w in workers:
        w.start()

    workers[-1].terminate()
    for w in workers:
        w.join()

    for w in workers:
        print w.exitcode


#Pool类，创建进程池里面包含创建的子进程，没有装载任务。
#提供了方法:
#apply
#apply_async
#map
#在装载任务到子进程并执行

#--IPC--
#Queue类是 线程安全和进程安全的FIFO

from multiprocessing import Queue,Process
import random 

def generate(q):
    while True:
        #time.sleep(3)
        value=random.randrange(10)
        q.put(value)
        print "Adddd to queue:%s" %value


def reader(q):
    while True:
        #time.sleep(3)
        value=q.get()
        print "Get from queue:%s" %value


def demo2():
    queue=Queue()
    p1=Process(target=generate,args=(queue,))#两个进程都引用Queue,指向同一个对象共享数据
    p2=Process(target=reader,args=(queue,))
    p1.start()
    p2.start()


#Pipe返回一对连接对象，表示管道一端，每个连接对象都有send和recv方法提供双向通信
from multiprocessing import Pipe

def generate(pipe):
    while True:
        value=random.randrange(10)
        time.sleep(1)
        pipe.send(value)
        print "sent value:%s" %value


def reader(pipe):
    f=open("piperecv.txt","w")
    while True:
        value=pipe.recv()
        f.write(str(value))
        print "."


def demo3():
    left_p,right_p=Pipe()       #left_p<=====>right_p
    p1=Process(target=generate,args=(left_p,))
    p2=Process(target=reader,args=(right_p,))
    p1.start()
    p2.start()

if __name__=="__main__":
    #demo0()
    #demo1()
    #demo2()
    #demo3()


