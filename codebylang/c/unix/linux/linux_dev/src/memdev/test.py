import fcntl

#---ioctl---
c="#"
f=open("/dev/memdev0")
print fcntl.ioctl(f.fileno(),-2147390206,c) #getb
print fcntl.ioctl(f.fileno(),1073835265,'Y')#setb
print f.readlines()
print fcntl.ioctl(f.fileno(),27904) #reset

