#!-*-coding:utf8-*-
from mpi4py import MPI
comm=MPI.COMM_WORLD
rank=comm.rank
print "hello world (from process %d)" %rank


#mpi多个进行运行同一份代码只是comm.rank不同
#if rank 可以指定单独进程完成某个任务



#同步，确保hello,world在print rank之前
comm.Barrier() #同步障


if rank==0:
    print "rank 0!"
if rank==1:
    print "rank 1!"
if rank==2:
    print "rank 2!"
if rank==3:
    print "rank 3!"

