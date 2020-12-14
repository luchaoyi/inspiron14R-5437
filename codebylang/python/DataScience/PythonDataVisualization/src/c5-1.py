#coding:utf8
import random

import matplotlib as mpl 
import numpy as np 
import matplotlib.pyplot as plt
import matplotlib.dates as mdates

from mpl_toolkits.mplot3d.axes3d import Axes3D

mpl.rcParams['font.size']=10

fig=plt.figure()
#使用axes3d对象方法绘制3d图形
ax=Axes3D(fig) #生成一个3d-axes <=>ax=fig.add_subplot(111,projection='3d') 1*1=1个子区 is 3d 
YEAR=[2011,2012,2013,2014]


#ax.plot,ax.bar,ax.fill，有一系列3d绘图函数

for z in YEAR:
    xs=xrange(1,13)
    ys=1000*np.random.rand(12)
    color=plt.cm.Set2(random.choice(xrange(plt.cm.Set2.N)))
    ax.bar(xs,ys,zs=z,zdir='y',color=color,alpha=0.8)

#设置刻度set_major_locator,调用了传入的locator对象的方法设置刻度
ax.xaxis.set_major_locator(mpl.ticker.FixedLocator(xs))
ax.yaxis.set_major_locator(mpl.ticker.FixedLocator(ys))


ax.set_xlabel('Month')
ax.set_ylabel('Year')
ax.set_zlabel('Sales')


plt.show()
