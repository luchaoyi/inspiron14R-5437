#!-*-coding:utf8-*-

from mpi4py import MPI
import h5py
import mpi4py

comm=MPI.COMM_WORLD
rank=comm.rank



print "*"

with h5py.File('atomicdemo.hdf5','w',driver="mpio",comm=comm) as f:

    f.atomic=True #牺牲性能打开严格一致性
    dset=f.create_dataset('x',(1,),dtype='i')
    
    if rank==0:
        dset[0]=10
    comm.Barrier()

    if rank==1:
        print dset[0]
