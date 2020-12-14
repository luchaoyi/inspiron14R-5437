#!-*-coding:utf8-*-

import ctypes

omp=ctypes.CDLL('./demo_omp.so')

omp.demo0()
omp.sp()
omp.demo1()
omp.sp()
omp.demo2()
omp.sp()
omp.demo3()
omp.sp()
omp.demo4()


