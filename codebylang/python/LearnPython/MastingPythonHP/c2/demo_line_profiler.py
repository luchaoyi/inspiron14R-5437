#coding:utf8

import line_profiler
import sys


#line_profiler 以行为单位分析代码
#line_profiler性能分析器被设计为一个装饰器


@profile
def fib(n):
    a,b=0,1
    for i in range(n):
        a,b=b,a+b
    return a
    
    

fib(10)
def test():
    for i in range(0,10):
        print i**2
    print "End of the function"

prof = line_profiler.LineProfiler(test) #装饰test

prof.enable()
test()
prof.disable()
prof.print_stats(sys.stdout)



result="""
lcy@lcy:~/B/codecache/python/LearnPython/PythonHP/c2$ kernprof -l -v  demo_line_profiler.py
0
1
4
9
16
25
36
49
64
81
End of the function
Timer unit: 1e-06 s
Total time: 0.000113 s
File: demo_line_profiler.py
Function: test at line 37

Line #      Hits         Time  Per Hit   % Time  Line Contents
==============================================================
    37                                           def test():
    38        11           15      1.4     13.3      for i in range(0,10):
    39        10           91      9.1     80.5          print i**2
    40         1            7      7.0      6.2      print "End of the function"

Wrote profile results to demo_line_profiler.py.lprof
Timer unit: 1e-06 s

Total time: 2e-05 s
File: demo_line_profiler.py
Function: fib at line 8

Line #      Hits         Time  Per Hit   % Time  Line Contents
==============================================================
     8                                           @profile
     9                                           def fib(n):
    10         1            2      2.0     10.0      a,b=0,1
    11        11           10      0.9     50.0      for i in range(n):
    12        10            7      0.7     35.0          a,b=b,a+b
    13         1            1      1.0      5.0      return a
"""
