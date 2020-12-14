#!coding:utf8
import pygame,sys,easygui

answer=easygui.msgbox("开始游戏?")
if answer!="OK":
    sys.exit()

pygame.init()
#display是显示表面唯一能看见的，其它表面想显示需要复制到显示表面

bg=[255,255,255]
sw=640
sh=480
screen=pygame.display.set_mode([sw,sh]) 
screen.fill(bg)

#pygame.draw.*绘制图形的
#                           RGB                线宽 width=0，完全填充
pygame.draw.circle(screen,[255,0,0],[320,240],30,0)
screen.set_at([10,10],[255,0,0])#操作单个像素颜色
ball=pygame.image.load("ball.jpg")
x=50
y=50 
bh=ball.get_height()
bw=ball.get_width()

screen.blit(ball,[x,y])#图形像素复制术语：块移 
pygame.display.flip()#display内存中有两份,一份处于当前显示，draw绘制在非显示的一面,filp后显示被更新.

speedx=5
speedy=5

#事件循环
while True:
    #从事件队列获取一个事件
    for e in pygame.event.get():
        if e.type==pygame.QUIT:
            sys.exit()
        elif e.type==pygame.MOUSEBUTTONDOWN:
            answer=easygui.msgbox("结束游戏?")
            if answer=="OK":
                sys.exit()

    pygame.time.delay(20)
    pygame.draw.rect(screen,bg,[x,y,90,90],0)#用背景擦除原来球
    x+=speedx 
    y+=speedy
    screen.blit(ball,[x,y])
    pygame.display.flip()#display内存中有两份,一份处于当前显示，draw绘制在非显示的一面,filp后显示被更新.
    if x+bw>sw or x<=0:
        speedx=-speedx
    if y+bh>sh or y<=0:
        speedy=-speedy
       


