#!coding:utf8

import tensorflow as tf
import numpy as np

#xavier让权重满足0均值方差为2/nin+nout,分布可以用高斯或均匀分布
#这里采用均匀分布(min,max),E(x)=(max-min)/2,D(x)=(max-min)/12
#根据输入输出数量初始化两层间的权重
def xavier_init(fan_in,fan_out,constant=1):
    Min=-constant*np.sqrt(6.0/(fan_in+fan_out))
    Max=constant*np.sqrt(6.0/(fan_in+fan_out))
    return tf.random_uniform((fan_in,fan_out),minval=Min,
                             maxval=Max,dtype=tf.float32)
    
#一个隐藏层的autocoder
class Autocoder:
    def __init__(self):
        """Constructor"""
        pass
#写代码时专门写一个初始化权重的函数生成所有的权重，并添加到一个字典中，这样可以使用字符串取到对应的变量
#用一个字典管理所有变量可以避免声明很多变量，造成混乱
#可以将所有的placeholder用一个字典管理，专门管理输入输出
    def init_weights(self):
        all_weights={}
        all_weights['w1']=tf.Variable(xavier_init(self.n_input,self.n_hidden))
        all_weights['b1']=tf.Variable(tf.zeros([self.n_hidden]),dtype=tf.float32)
        all_weights['w2']=tf.Variable(xavier_init(self.n_hidden,self.n_input))
        all_weights['bb']=tf.Variable(tf.zeros([self.n_input]),dtype=tf.float32) 
        return all_weights
        


