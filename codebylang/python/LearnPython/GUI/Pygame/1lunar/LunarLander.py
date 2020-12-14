#!coding:utf8
import sys,pygame,easygui,random


def drawground():
    screen.fill([0,0,0])
    screen.blit(moon,[0,600-moon.get_height()])



sound_file="/home/lcy/音乐/bgm.mp3"
#mixer模块负责声音
pygame.mixer.init()
pygame.mixer.music.load(sound_file)
pygame.mixer.music.play(-1)#-1播发次数代表无限次play(2),播放两次

screen=pygame.display.set_mode([400,600])
ship=pygame.image.load('lunar.jpg')
moon=pygame.image.load('ms.jpg')
stsk=pygame.image.load('StarSky.jpg')


#技能
q=pygame.image.load('q.jpg')
w=pygame.image.load('w.jpg')
e=pygame.image.load('e.jpg')
r=pygame.image.load('r.jpg')
s=[q,w,e,r]

#-------------
drawground()
x=200
y=600-moon.get_height()-ship.get_height()
screen.blit(ship,[x,y])
pygame.display.flip()

start=True
speed=0.5

num=0 #记录第几个场景
select=-1

while True:
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            sys.exit()
        elif event.type==pygame.MOUSEBUTTONDOWN:
            #print event.pos,event.button
            x,y=event.pos 
            screen.blit(ship,[x,y])
        elif event.type==pygame.KEYDOWN:
            if event.key==pygame.K_DOWN:
                speed-=0.5
            elif event.key==pygame.K_UP:
                speed+=0.5
            elif event.key==pygame.K_LEFT:
                x-=20
            elif event.key==pygame.K_RIGHT:
                x+=20 
            elif event.key==pygame.K_q:
                select=0
            elif event.key==pygame.K_w:
                select=1
            elif event.key==pygame.K_e:
                select=2
            elif event.key==pygame.K_r:
                select=3
            elif event.key==pygame.K_a:
                select=-1
    y-=speed
    if y+ship.get_height()<0:
       y=600-ship.get_height()
       num+=1
       if num>0:
           start=False

    if y>600:
        y=0
        num-=1
        if num<=0:
            start=True

    if start:
        drawground()
        if y+ship.get_height()>600-moon.get_height():
            easygui.msgbox("飞船砸地上了")
            sys.exit()
    else:
        #screen.fill([0,0,0]) 
        screen.blit(stsk,[0,0])


    if select!=-1:
        screen.blit(s[select],[random.randint(0,400),random.randint(0,600)])


    screen.blit(ship,[x,y])
    pygame.time.delay(10)
    pygame.display.flip()

            




