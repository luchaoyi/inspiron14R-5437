#coding:utf8

#Xw=y
#w=(X.TX).-1X.Ty
import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
from  tensorflow.python.framework import ops
ops.reset_default_graph()
sess=tf.Session()


#y=x+N(0,1) 生成数据
x_vals=np.linspace(0,10,100)
y_vals=5*x_vals+np.random.normal(0,1,100)


#模型y=w.Tx->Xw=y

X=tf.placeholder(tf.float32, shape=[None,1]) 
y=tf.placeholder(tf.float32,shape=[None,1])
X_T=tf.transpose(X)
inv=tf.matrix_inverse(tf.matmul(X_T,X)) #(X.TX)^-1
my_output=tf.matmul(tf.matmul(inv,X_T),y)

[[w]]=sess.run(fetches=my_output,feed_dict={X:np.transpose([x_vals]),y:np.transpose([y_vals])})
print w

#使用tf函数求解线性方差组X.TXw=X.Ty
[[w_by_slove]]=sess.run(fetches=tf.matrix_solve(tf.matmul(X_T,X),tf.matmul(X_T,y)),feed_dict={X:np.transpose([x_vals]),y:np.transpose([y_vals])})
print w_by_slove


best_fit = []
for i in x_vals:
    best_fit.append(w*i)
plt.plot(x_vals, y_vals, 'o', label='Data')
plt.plot(x_vals, best_fit, 'r-', label='Best fit line',linewidth=3)
plt.legend(loc='upper left')
plt.show()



