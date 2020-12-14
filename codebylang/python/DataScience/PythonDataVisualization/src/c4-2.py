#coding:utf8
import matplotlib as mpl 
import numpy as np 
import matplotlib.pyplot as plt

def p_s(x,y):
    return (1-(x**2+y**2))*np.exp(-y**3/3)

x=np.arange(-5,5,0.01)
y=np.arange(-5,5,0.01)

X,Y=np.meshgrid(x,y) #根据x，y生成一个网格。X,Y存储每一个格点的X,Y坐标
print X,Y
Z=p_s(X,Y)
N=np.arange(-1,1.5,0.1) #z的刻度

CS=plt.contour(X,Y,Z,N)
plt.colorbar(CS)

plt.show()
