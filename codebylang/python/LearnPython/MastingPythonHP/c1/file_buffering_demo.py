#coding:utf8
from  td import *

bufsize=1*1024*1024*100 #100M
start_time()
f=open('f','w',bufsize)
f.writelines('1'*bufsize)
f.flush()
f.close()
print "write use buf %s" %get_delta()


start_time()
f=open('f','w')
f.writelines('1'*bufsize)
f.close()
print "write no use buf %s" %get_delta()

start_time()
f=open('f','r',bufsize)
f.readlines()
print "read use buf %s" %get_delta()

start_time()
f=open('f','r',-1)
f.readlines()
f.close()
print "read no use buf %s" %get_delta()

#100M 
#write buf 0:00:06.400528           write buf 避免频繁的磁盘IO提高了速度
#write no use buf 0:00:07.315963
#read use buf 0:00:00.583460          
#read no use buf 0:00:00.152922     read no buf 文件全部被载入内存提高了速度



#1000M                         
#write use buf 0:00:46.695388  缓冲区太大，若引起操作系统换入换出，反而速度下降
#write no use buf 0:00:39.795823
#read use buf 0:00:07.553581
#read no use buf 0:00:15.404630 



