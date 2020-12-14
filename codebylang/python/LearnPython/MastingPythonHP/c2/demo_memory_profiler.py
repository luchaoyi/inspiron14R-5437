#coding:utf8

import sys


#加上这段代码保证正常执行
if 'profile' not in dir() or not hasattr(__builtins__,"profile"):
    def profile(func):
        def inner(*args,**kwargs):
            return func(*args,**kwargs)
        return inner
    
    
@profile
def fib(n):
    a,b=0,1
    for i in range(n):
        a,b=b,a+b
    return a
    
    

print fib(10)


"""
lcy@lcy:~/B/codecache/python/LearnPython/MastingPythonHP/c2$ python -m memory_profiler demo_memory_profiler.py 
Filename: demo_memory_profiler.py

Line #    Mem usage    Increment   Line Contents
================================================
     5   21.395 MiB    0.000 MiB   @profile
     6                             def fib(n):
     7   21.395 MiB    0.000 MiB       a,b=0,1
     8   21.395 MiB    0.000 MiB       for i in range(n):
     9   21.395 MiB    0.000 MiB           a,b=b,a+b
    10   21.395 MiB    0.000 MiB       return a

"""



