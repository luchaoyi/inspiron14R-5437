#coding:utf8

from functools import wraps
import time

def timefn(fn):
    """
    一个装饰器使用time.time()计算时间差，粗略测量fn执行时间
    """
    #@wraps(fn) 将fn的函数名和docstring暴露给fn的调用者，否则看到的是修饰器的而不是被修饰函数的
    @wraps(fn)
    def measure_time(*args,**kwargs):
        t1= time.time()
        result=fn(*args,**kwargs)
        t2=time.time()
        print ("@timefn:"+fn.func_name+" took "+str(t2-t1)+"seconds")
        return result
    
    return measure_time




@timefn
def hello():
    print "hello,world!"
    
hello()
    



