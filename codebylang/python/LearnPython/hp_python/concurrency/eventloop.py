#coding:utf8

from Queue import  Queue
from  functools import partial

#事件循环
eventloop=None
class Eventloop(Queue):
    #事件循环从队列去除事件函数执行
    #my idea:不同动作对应一个回调函数，动作发生将对应回调函数put到队列中
    def start(self):
        while True:
            function=self.get()
            function()
            
def do_hello():
    global eventloop
    print "hello"
    eventloop.put(do_world)
        
def do_world():
    global eventloop
    print "world"
    eventloop.put(do_hello)
      
if __name__=="__main__":
    eventloop=Eventloop()
    eventloop.put(do_hello)
    eventloop.start() #start中来回切换运行 do_hello和do_world
    
    
        
    
        
            
            
        
        
    
    
