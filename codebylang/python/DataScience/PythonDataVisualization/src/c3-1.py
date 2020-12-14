#!-*-coding:utf8-*-

from matplotlib.pyplot import *
x=[1,2,3,4]
y=[5,4,3,2]

#hold会在一个绘图窗口继续绘图
#not hold 不激活新的窗口时，会清除已绘内容
hold(True)
print ishold()
plot(x)
plot(y)

hold(False)
print ishold()
plot(x)
plot(y)


#hold是个全局配置
hold(True)

figure("D-A") #创建并激活窗口
#绘制在A
plot(x)
plot(y)

figure("D-B")
#绘制在B
plot(x,y)

figure("subplot")
#2*3窗口第一个
subplot(231)
plot(x,y)

subplot(232)
bar(x,y)


subplot(233)
#水平条形
barh(x,y)

subplot(234) 
#堆栈条形图,同x轴，y+y1为y轴,y与y1不同色
bar(x,y)
y1=[7,8,5,3]
bar(x,y1,bottom=y,color='r')

subplot(235)
boxplot([x,y])

subplot(236)
scatter(x,y)


figure("sin/cos")
title("sin and cos")
x=np.linspace(-np.pi,np.pi,100)
ysin=np.sin(x)
ycos=np.cos(x)
plot(x,ysin)
plot(x,ycos)

#set x/y坐标轴limit，limit之外的不会显示 
xlim(-3.0,3.0)
ylim(-1.0,1.0)

#绘图中的数学符号书写使用了Latex语法
xticks([-np.pi,-3,0,3,np.pi],[r'$-\pi$',r'$-3$',r'$0$',r'$3$',r'$\pi$']) #设置x axis刻度记号

show()


