#coding:utf8

import multiprocessing
import time 

class Process(multiprocessing.Process):     
    def __init__(self,id):
        super(Process,self).__init__()
        self.id=id
    
    def run(self):
        """"""
        time.sleep(1)
        print "Id is %d"%self.id
        
 

#----------------------------------------------------------------------
def inc(x):
    """"""
    return x+1
    
        

if __name__=="__main__":
    p=Process(0)
    p.start()
    p.join() #等待p完成才继续执行
    
    print "end"


    l=[1,2,3,4,5,6,6,7,8,9,10,11]
    #进程池预先创建多个进程
    #提供map,apply等方法装载执行任务
    pool=multiprocessing.Pool()
    print pool.map(inc,l)
    print "end"
    print pool.map(inc,l)
    print "end"
    
    #异步立即返回一个对象，需要自己get
    #同步直接阻塞直到返回结果
    result=[pool.apply_async(inc,(i,)) for i in l] #(i,)  可迭代 not i
    print [r.get() for r in result]
    print [pool.apply(inc,(i,)) for i in l]
    
