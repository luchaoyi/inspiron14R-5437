#!-*-coding:utf8-*-
import matplotlib.pylab as plt
import numpy as np

plt.figure(0)

ax=plt.gca()
y=np.random.randn(9)
col_labels=['a','b','c']
row_labels=['1','2','3']
table_vals=[[11,12,13],[21,22,23],[31,32,33]]
row_colors=['r','g','b']
plt.table(cellText=table_vals,colWidths=[0.1]*3, \
            rowLabels=row_labels,colLabels=col_labels, \
            rowColours=row_colors, \
            colColours=row_colors,\
            loc='upper right')
plt.plot(y)



plt.figure(1)

# 1 1 1
# 2 3 3
# 2 3 3
#将Figure划分为3*3的网格生成子区，起始子区0行0列
axes1=plt.subplot2grid((3,3),(0,0),colspan=3) #跨越3列则第一个子区占据了网格第0行
axes2=plt.subplot2grid((3,3),(1,0),rowspan=2)     
axes3=plt.subplot2grid((3,3),(1,1),rowspan=2,colspan=2) 

plt.show()
