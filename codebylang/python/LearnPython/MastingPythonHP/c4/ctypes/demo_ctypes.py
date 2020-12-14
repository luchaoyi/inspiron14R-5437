#coding:utf8
#ctypes提供python的c语言接口


#ctypes可以载入 .dll/.so,调用c语言编写的函数
#若在python中调用动态库同名函数，python除了整型和字符串可以直接调用，其它都需要使用ctypes的类型包装
#需要根据类型对应关系包装


import time 
import ctypes
import math


import td



#加载系统库
from ctypes import cdll
#libc.so.6 is c language standard library
libc=cdll.LoadLibrary('libc.so.6')
print [libc.rand() for x in range(20)]


#加载自己的库
td.start_time()
#gcc -shared -o check_prime.so -fPIC check_prime.c
objdll=ctypes.CDLL('./check_prime.so')
check_prime_types=objdll.check_prime #加载check_prime.so，将函数check_prime赋值给check_prime_types.

print "load time %s" %td.get_delta()

def p_check_prime(x):
    values=xrange(2,int(math.sqrt(x)))
    for i in values:
        if x%i==0:
            return False
    return True



src="""
def p_check_prime(x):
    values=xrange(2,int(math.sqrt(x)))
    for i in values:
        if x%i==0:
            return False
n_py=[x for x in xrange(1000000) if p_check_prime(x)]
"""

code=compile(src,"","exec")



td.start_time()
n_py=[x for x in xrange(1000000) if p_check_prime(x)]
print "python time %s" %td.get_delta()

td.start_time()
n_c=[x for x in xrange(1000000) if check_prime_types(x)]
print "c time %s" %td.get_delta()


td.start_time()
exec(code)
print "compile time %s" %td.get_delta()


#load time 0:00:00.000186:
#python time 0:00:09.799220:
#c time 0:00:01.775289:
#compile time 0:00:09.906512:


print "---ctypes and c type---"
#python ctypes:int ,string,c_float(c),c_double(d),c_char(e)
#void type_demo(int a,char *b,float c,double d,char e
tpd=objdll.type_demo
a=10
b="abcde"
c=1.2
d=1000000000000.5
e='o'
tpd(a,b,ctypes.c_float(c),ctypes.c_double(d),ctypes.c_char(e))




