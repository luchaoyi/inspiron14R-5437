#!-*-coding:utf8-*-
from pylab import *

figure(1,figsize=(6,6))
ax=axes([0.1,0.1,0.8,0.8])
labels='spring','summer','autumn','winter'
print labels
x=[15,30,45,10]
explode=(0.1,0.1,0.1,0.1)
pie(x,labels=labels,autopct='%1.1f%%',startangle=67)
figure() 
#explode指定了分裂度
pie(x,labels=labels,explode=explode,autopct='%1.1f%%',startangle=67)
show()

