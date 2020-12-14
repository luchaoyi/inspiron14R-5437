#coding:utf8
import multiprocessing
import ctypes
import numpy as np

#共享numpy数组的方法是构建共享的multiprocessing.Array然后把它转换成numpy数组
if __name__=="__main__":
    SIZE_A=100
    SIZE_B=200
    NBR_ITEMS_IN_ARRAY=SIZE_A*SIZE_B
    shared_array_base=multiprocessing.Array(ctypes.c_double, 
                                           NBR_ITEMS_IN_ARRAY,lock=False)
    #包装Array
    main_nparray=np.frombuffer(shared_array_base,dtype=ctypes.c_double)
    #resize
    main_nparray.resize(SIZE_A,SIZE_B)
    
    
    

