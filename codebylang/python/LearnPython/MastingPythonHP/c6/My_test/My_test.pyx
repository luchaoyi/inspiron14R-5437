from libc.stdio cimport printf as cprintf #直接引入已编译的C语言函数


cpdef void join_n_print(parts):
    print ' '.join(parts)
   
cpdef void say_hello():
    print "hello,world!"
    
def  c_printf():
    cprintf("hello,world!\n")

def  h_printf():
    #引入头文件.h，需要重新声明使用的函数或变量的类型和结构
    cdef extern from "stdio.h":
        extern int printf(const char *format, ...)  

    printf("hello,world!\n")



