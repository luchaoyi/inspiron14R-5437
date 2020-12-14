#coding:utf8
import os
import time

LOCKFILE="/tmp/lf.lock"
#通过打开文件方式加锁
#Posix.1保证以O_CREAT|O_EXCL标志调用函数一旦文件存在则返回错误，因此必须保证检查文件存在和创建该文件的原子性，可以使用这种技巧将文件作为锁

def lock():
    try:
        tmpfd=os.open(LOCKFILE,os.O_RDWR|os.O_CREAT|os.O_EXCL)
        os.close(tmpfd)
    except Exception as e:
        #print e
        #print e.args
        #print os.errno.errorcode[e.args[0]]
        #e.args #包含了errno错误码和错误码对应的字符串 (17, 'File exists')
        if e.args[0]!=os.errno.EEXIST:
            print e
        else:
            print "lock failed!"
    
def unlock():
    if os.path.exists(LOCKFILE):
        os.unlink(LOCKFILE)


        
def main():
    pid=os.fork()
    if pid==0: 
        lock()
        print "A"
        unlock()
    else:
        lock()
        print "B"
        time.sleep(1)
        unlock()
        
main()
