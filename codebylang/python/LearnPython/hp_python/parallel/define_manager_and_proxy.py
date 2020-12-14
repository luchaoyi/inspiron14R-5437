#coding:utf8

import multiprocessing
from multiprocessing.managers import BaseManager


#自定义类A
class A:
    def __init__(self,value):
        self.x=value 
    
    def getX(self):
        return self.x 
    
    def setX(self,value):
        self.x=value
     
    def __iadd__(self,value):
        self.x += value
        return self
        
class MyManager(BaseManager):pass





from  multiprocessing.managers import BaseProxy 
#自定义代理对象，可实现更多方法
#调用者->代理对象->对象

class AProxy(BaseProxy):
    _exposed_=['__iadd__','getX','setX'] #定义对象A公开的方法
    
    #----------------------------------------------------------------------
    def __iadd__(self,value):
        self._callmethod('__iadd__',(value,)) #调用A对象的__iadd__
        return self
    @property
    #----------------------------------------------------------------------
    def x(self):
        """"""
        return self._callmethod('getX',())
    @x.setter
    #----------------------------------------------------------------------
    def x(self,value):
        """"""
        self._callmethod('setX',(value,))
        
        
        
 #自定义生成的代理对象添加了更多方法       
 #代理对象通过 self._callmethod('setX',(value,))调用被代理对象方法
    

MyManager.register("SHA",A,proxytype=AProxy) #MyManager注册一个类A,注册为SHA,为类A添加了一个方法SHA返回对象A的代理


if __name__=="__main__":
    m=MyManager()
    m.start() #自定义 manager need start 
    a=m.SHA(37)
    
    print A.__dict__
    print AProxy.__dict__

    print a
    print a.x
    a+=1    
    print a.x

 
