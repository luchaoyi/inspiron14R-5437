#!/usr/bin/python
#!coding:utf8

import sys

def emit(key,value):
    if key==None:return
    print >>sys.stdout,'%s\t%d' %(key,value)


wc_sum=0
last_word=None
for line in sys.stdin:
    keyandvalue=line.strip().split('\t')
    if len(keyandvalue)!=2:
        continue
    word=keyandvalue[0]
    value=int(keyandvalue[1])
    
    if(word==last_word):
        wc_sum+=value
    else:
        emit(last_word,wc_sum)
        last_word=word
        wc_sum=value

emit(last_word,wc_sum)
    

