#!/usr/bin/python
#!coding:utf8

#cat testfile |python wc_map.py |LC_ALL=C sort|python wc_reduce.py 本地测试

import sys

def emit(key,value):
    print >>sys.stdout,'%s\t%d' %(key,value)

for line in sys.stdin:
    words=line.strip().split()
    for word in words:
        emit(word,1)
     


