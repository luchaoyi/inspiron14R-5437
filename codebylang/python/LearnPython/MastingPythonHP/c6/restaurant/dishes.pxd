#定义文件，Cython文件要使用的变量，类型，函数的C声明
cdef enum otherstuff:
    sausage,eggs,lettuce

cdef struct spamdish:
    int oz_of_spam
    otherstuff filler

