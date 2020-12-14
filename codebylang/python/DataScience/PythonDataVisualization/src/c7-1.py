#coding:utf8
import matplotlib as mpl 
import numpy as np 
import matplotlib.pyplot as plt


#对数图y轴是logy,展示了y的量级,适合用对数图的情况:
#1.展示值跨越多个量级
#2.展示变化率
#3.数据倾斜趋势明显(一些值比另一些大很多)
#对数据变换以更好的展示数据，这与ML中数据变换思想是类似的
x=np.linspace(1,10)
y=[10**el for el in x]
z=[2**el for el in x]

fig=plt.figure(figsize=(10,8))

ax1=fig.add_subplot(2,2,1)
ax1.plot(x,y,color='blue')
ax1.set_yscale('log')
ax1.set_title(r'log plot $10^x$')


ax2=fig.add_subplot(2,2,2)
ax2.plot(x,y,c='r')
ax2.set_yscale('linear')
ax2.set_title(r'linear plot $10^x$')

ax3=fig.add_subplot(2,2,3)
ax3.plot(x,z,c='g')
ax3.set_yscale('log')
ax3.set_title(r'log plot $2^x$')

ax4=fig.add_subplot(2,2,4)
ax4.plot(x,z,c='magenta')
ax4.set_yscale('linear')
ax4.set_title(r'linear plot $2^x$')






fig=plt.figure()
#stem 火柴杆图，可用于绘制离散数据
import random 
x=range(0,10)
y=[random.random()*el for el in x]


ax=plt.axes()
ax.stem(x,y)
ax.set_title(r'random sequence')

plt.show()
