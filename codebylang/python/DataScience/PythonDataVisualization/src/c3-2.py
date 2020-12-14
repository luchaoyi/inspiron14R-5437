#!coding:utf8
from pylab import *
from matplotlib.pyplot import *


ax=gca()#ax=axes()
ax.locator_params(tight=True,nbins=10) #nbin=10,10个刻度
ax.plot(np.random.normal(10,.1,100))

figure("legend and annotate")


x1=np.random.normal(30,3,100)
x2=np.random.normal(20,3,100)
x3=np.random.normal(10,3,100)

plot(x1,label='u=30')
plot(x2,label='u=20')
plot(x3,label='u=10')

legend(ncol=3,loc=3,mode="expand") #生成图例子

annotate(
        "import value",(55,20),xytext=(5,38),arrowprops=dict(arrowstyle='->')
        ) # "import value" 注释文本的坐标为(5,38) -> (55,20) 被注释的数据点

axhline(10,c='r')
axhline(20,c='g')
axhline(30,c='b')

show()
