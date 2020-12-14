#:coding:utf8

#使用1byte计数器可以最大计数到2**255,而普通计数器计数需要256个bit即32byte
#非精确计数

from  random import random

class MorrisCounter(object):
    _counter=0
    #----------------------------------------------------------------------
    def add(self):
        if random()<1.0/(2**self._counter):
            self._counter+=1
    def reset(self):
        self._counter=0
        
    def get_count(self):
        if self._counter==0:
            return 0
        return 2**self._counter
        
        
    
    
    
if __name__=="__main__":
    m=MorrisCounter()
    print m.get_count()
    
    for i in range(16):
        m.add()
        print m.get_count()
        
    m.reset()
    print m.get_count()
    
    
    

        
        
        
    
    
