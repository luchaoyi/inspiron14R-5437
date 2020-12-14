#coding:utf8

#kmv实现非精确计数,对同一个key只计数一次,可以以低误差计算一个集合的势

import mm3
from blist import sortedset 

#利用hash函数的均匀性保留k的唯一最小hash值估算散列值总体空间和推导项的全部数量
#证明和计算方法来自与论文
class KMV(object):
    def __init__(self,num_hashes):
        self.num_hashes=num_hashes
        self.data=sortedset()
    def add(self,item):
        item_hash=mm3.hash(item)        #计算item的hashvalue
        self.data.add(item_hash)
        if len(self.data)>self.num_hashes:
            self.data.pop()
        
    def __len__(self):
        if len(self.data) <=2:
            return 0
        return (self.num_hashes-1)*(2**32-1)/float(self.data[-2]+2**31-1)
        
        
        
    
    
