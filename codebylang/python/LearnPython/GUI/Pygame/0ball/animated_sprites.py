#!coding:utf8
import pygame,sys
from random import *

#pygame.sprite.Sprite类实现了碰撞检测等一些基本功能，继承直接用
class MyBallClass(pygame.sprite.Sprite):
    def __init__(self,image_file,location,speed):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load(image_file)
        self.rect=self.image.get_rect()
        self.rect.left,self.rect.top=location
        self.speed=speed

    def move(self):
        self.rect=self.rect.move(self.speed)
        if self.rect.left<0 or self.rect.right>width:
            self.speed[0]=-self.speed[0]
        if self .rect.top<0 or self.rect.bottom>height:
            self.speed[1]=-self.speed[1]

def animate(group):
    screen.fill(background)
    for ball in group:

        group.remove(ball)
        #检测 ball 与 group 组内成员的碰撞
        if pygame.sprite.spritecollide(ball,group,False):
            ball.speed[0]=-ball.speed[0]
            ball.speed[1]=-ball.speed[1]
        group.add(ball)

        ball.move()
        screen.blit(ball.image,ball.rect)

    pygame.display.flip()
    #pygame.time.delay(20)


pygame.init()
background=[255,255,255]
size=width,height=640,480
screen=pygame.display.set_mode(size) 
screen.fill(background)
image_file="ball.jpg"

group=pygame.sprite.Group()


clock=pygame.time.Clock()#控制fps

for row in range(0,4):
    for col in range(0,4):
        location=[col*180+10,row*180+10]
        speed=[choice([-2,2]),choice([-2,2])]
        ball=MyBallClass(image_file,location,speed)
        group.add(ball)



pygame.time.set_timer(pygame.USEREVENT,1000) #定时器事件
pygame.time.set_timer(pygame.USEREVENT+1,500) #定时器事件
#事件循环
while True:
    #从事件队列获取一个事件
    for e in pygame.event.get():
        if e.type==pygame.QUIT:
            sys.exit()
        elif e.type==pygame.USEREVENT:
            #1000ms(1s)发生一次
            print "*"
        elif e.type==pygame.USEREVENT+1:
            #500ms发生一次
            print "-"


    clock.tick(60)
    animate(group)

""" 
    pygame.time.delay(20)
    screen.fill(background)

    for ball in balls:
        ball.move()
        screen.blit(ball.image,ball.rect)
    pygame.display.flip()
"""

            

