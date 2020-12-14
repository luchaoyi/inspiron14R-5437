#!-*-coding:utf8-*-
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation #动画模块

fig=plt.figure()
ax=plt.axes(xlim=(0,2),ylim=(-2,2))
#动画，快速刷新的一系列图片
line,=ax.plot([],[],lw=2)


#绘制下一帧前,清除当前帧
def init():
    line.set_data([],[]) #空屏幕
    return line,

def animate(i):
    x=np.linspace(0,2,1000)
    y=np.sin(2*np.pi*(x-0.01*i))*np.cos(22*np.pi*(x-0.01*i))
    #print i
    line.set_data(x,y)
    return line,



#interval 与 fps没有关系，在不同设备生成动画


#FuncAnimation是在Fig显示动画,调用回调函数生成动画
#init and animate is callback function
#interval是两幅图像迭代的间隔
animator=animation.FuncAnimation(fig,animate,init_func=init
        ,frames=200,interval=20,blit=True)

#保存动画到mp4文件
#fps is fp/s
#保存mp4的帧速率
#200fp/30fps =6.?s
animator.save('ba.mp4',fps=30,extra_args=['-vcodec','libx264'],writer='ffmpeg_file')
plt.show()





