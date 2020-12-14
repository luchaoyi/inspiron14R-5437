#!/usr/bin/python2.7
#usage python dictname wordsnum 

import sys
import random

print sys.argv
dictname=sys.argv[1]
wordsnum=int(sys.argv[2])

with open(dictname,'rt') as f:
    words=f.readlines()

words = [w.rstrip() for w in words]
for w in random.sample(words,wordsnum):
    print w




