#coding:utf8
import os
import socket
import sys


def client(fdr,fdw):
    path='./d$'
    os.write(fdw, path)
    r=''
    while True:
        c=os.read(fdr,1)
        r+=c
        if c=='$':
            break
    print r.strip('$')
    
def server(fdr,fdw):
    path=''
    while True:
        c=os.read(fdr, 1)
        if c=='$':
            break
        path+=c
    #读文件内容加入结束符
    r=open(path).read()
    r+='$'
    os.write(fdw,r)
    
#use socketpair 创建双工管道
def s_main():
    fd_a,fd_b=socket.socketpair() #默认阻塞读写
    
    pid=os.fork()
    if pid==0: #子进程pid==0,父进程得到fork的子进程的pid
        server(fd_a.fileno(),fd_a.fileno())
        sys.exit(0)

    client(fd_b.fileno(),fd_b.fileno())    
    os.waitpid(pid,0)
    #sys.exit(0)


#use popen实现
def p_main():
    f=os.popen('cat d','r') #启动进程cat，并读取cat的标准输入
    print f.read()
    f.close()
    
    
#use fifo 
def f_main():
    if os.path.exists("/tmp/fifo.1"):
        os.unlink("/tmp/fifo.1")
    
    if os.path.exists("/tmp/fifo.2"):
        os.unlink("/tmp/fifo.2")
        
    os.mkfifo("/tmp/fifo.1") #父->子 
    os.mkfifo("/tmp/fifo.2") #子->父
    
    pid=os.fork()
    if pid==0: #子进程pid==0,父进程得到fork的子进程的pid
        #os.open(filename, flag,mode) 不带缓冲io直接得到的是文件描述符
        fdr=os.open('/tmp/fifo.1',os.O_RDONLY)
        fdw=os.open('/tmp/fifo.2',os.O_WRONLY)
        
        
        server(fdr,fdw)
        sys.exit(0)
    
    fdw=os.open('/tmp/fifo.1',os.O_WRONLY) #注意如果调换这两句顺序会产生阻塞模式open会死锁
    fdr=os.open('/tmp/fifo.2',os.O_RDONLY)
    
    #fdr=os.open('/tmp/fifo.2',os.O_RDONLY)
    #fdw=os.open('/tmp/fifo.1',os.O_WRONLY) #死锁
    client(fdr,fdw)        
    os.waitpid(pid,0)
    
    os.unlink("/tmp/fifo.1") #删除pathname
    os.unlink("/tmp/fifo.2")
    
#use pipe
def pi_main():
    fr0,fw0=os.pipe()
    fr1,fw1=os.pipe()
    
    #创建两个pipe，实现双向通信
    fr0=os.fdopen(fr0,'r')
    fw0=os.fdopen(fw0,'w')
    
    
    fr1=os.fdopen(fr1,'r')
    fw1=os.fdopen(fw1,'w')
    
    #fdopen返回的是文件对象，底层操作函数需要使用文件描述符，使用文件对象.fileno()得到文件描述父
    
    pid=os.fork()
    if pid==0: #子进程pid==0,父进程得到fork的子进程的pid
        fw0.close()
        fr1.close()
        server(fr0.fileno(),fw1.fileno())
        sys.exit(0)
    
    fw1.close()
    fr0.close()
    client(fr1.fileno(),fw0.fileno())        
    os.waitpid(pid,0)
    
    
    
s_main()   
p_main()
f_main()
pi_main()


        
        
    
    
    