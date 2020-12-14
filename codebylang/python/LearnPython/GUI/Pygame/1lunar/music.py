#!coding:utf8

import pygame,sys 
pygame.init()

screen=pygame.display.set_mode([640,480])

sound_file="/home/lcy/音乐/bgm.mp3"
#mixer模块负责声音
pygame.mixer.init()
pygame.mixer.music.load(sound_file)
pygame.mixer.music.play(-1)#-1播发次数代表无限次play(2),播放两次

sound=1.0
while True:
    for event in pygame.event.get():
        if event.type==pygame.KEYDOWN:
            sound+=0.5
            pygame.mixer.music.set_volume(sound)#控制音量
        elif event.type==pygame.MOUSEBUTTONDOWN:
            sound-=0.5
            pygame.mixer.music.set_volume(sound)
        elif event.type==pygame.QUIT:
            sys.exit()



