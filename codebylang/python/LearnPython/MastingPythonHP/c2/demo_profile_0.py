#!coding:utf8


#cProfile 以函数为基本单位分析调用函数的的cpu时间
#line_profiler 分析某个函数的每行代码运行时间，有效的补充了cProfile
#KCacheGrind/pyprof2calltree and RunSnakeRun 支持性能分析数据可视化


#性能分析器cProfile is python default
#收集函数运行次数和CPU时间，不关心内存

import cProfile
import re
cProfile.run('re.compile("foo|bar")') #收集run代码的运行时间，函数调用信息

#195 function calls (190 primitive calls) in 0.000 seconds #primitive calls代表不包含递归的调用
#Ordered by: standard name
#ncalls  tottime  percall  cumtime  percall filename:lineno(function)
#...
#总调用次数/原生调用次数 总时间 tottime/ncalls 子函数累积时间和 cumtime/ncalls 源文件/行
#1    0.000    0.000    0.000    0.000 sre_compile.py:567(compile)
#3/1    0.000    0.000    0.000    0.000 sre_compile.py:64(_compile)


