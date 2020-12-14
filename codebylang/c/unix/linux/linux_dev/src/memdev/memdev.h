#ifndef _MEMDEV_H_
#define _MEMDEV_H_

#include<linux/ioctl.h>

#define MEMDEV_MAJOR 190 /*预设设备号*/
#define MEMDEV_NR_DEVS 2 /*设备数*/
#define MEMDEV_SIZE 4096  /*内存大小*/

struct mem_dev{
	char * data;        //内存起始地址
	unsigned long size;//内存大小
	 struct semaphore sem; //信号量
};


/*
 * ioctl
 **/
 
 
#define MEMDEV_IOC_MAGIC 'm'
#define MEMDEV_IOCRESET _IO(MEMDEV_IOC_MAGIC,	0)
#define MEMDEV_IOCSETB _IOW(MEMDEV_IOC_MAGIC,	1,char)
#define MEMDEV_IOCGETB _IOR(MEMDEV_IOC_MAGIC,	2,char)

#define MEMDEV_IOC_MAXNR 2

#endif /*_MEMDEV_H_*/
