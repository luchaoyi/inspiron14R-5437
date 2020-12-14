cimport dishes
from dishes cimport spamdish
from libc.stdio cimport printf

#类c函数,编译后不能被python直接调用
cdef void prepare(spamdish * d):
    d.oz_of_spam=42
    d.filler=dishes.sausage

#python函数，编译后可以被python调用
cpdef void serve():
    cdef spamdish d
    prepare( &d )
    #print "%d oz spam,filler no.%d" % (d.oz_of_spam,d.filler)
    #优化
    printf("%d oz spam,filler no.%d\n",d.oz_of_spam,d.filler)
    
