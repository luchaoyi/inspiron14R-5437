#coding:utf8

import memory_profiler
@memory_profiler.profile
def test():
    a= 'a'*(1024*10000)
    b=a[1024:]
    c=memoryview(a)
    d=c[1024:]



test()

#Line #    Mem usage    Increment   Line Contents
#================================================
#     5     21.4 MiB      0.0 MiB   @memory_profiler.profile
#     6                             def test():
#     7     31.2 MiB      9.8 MiB       a= 'a'*(1024*10000)
#     8     40.8 MiB      9.6 MiB       b=a[1024:]   这里进行了内存复制
#     9     40.8 MiB      0.0 MiB       c=memoryview(a) memoryview直接引用底层对象
#    10     40.8 MiB      0.0 MiB       d=c[1024:]
#
