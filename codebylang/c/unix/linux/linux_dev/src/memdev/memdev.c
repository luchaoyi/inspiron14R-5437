#include<linux/module.h>
#include<linux/init.h>
#include<linux/types.h> 
#include<linux/fs.h>
#include<linux/errno.h>
#include<linux/mm.h>
#include<linux/sched.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/semaphore.h>  //信号量

#include<asm/io.h>
#include<asm/switch_to.h>
#include<asm/uaccess.h>  //用户空间<->内核空间 数据交换
#include "memdev.h"


static int mem_major = MEMDEV_MAJOR;
module_param(mem_major,int,S_IRUGO);

struct cdev cdev; //静态定义cdev结构,也可动态申请
struct mem_dev *mem_devp; //自定义设备结构体指针


//操作函数名字可自定义，但类型已经固定
int mem_open(struct inode *inode,struct file *filep){
	struct mem_dev * dev;

	int num=iminor(inode); //获得次设备号
	if(num>=MEMDEV_NR_DEVS)
		return -ENODEV;
	dev=&mem_devp[num]; //根据编号获取操作的对象
	filep->private_data=dev;
	return 0;
}

int mem_release(struct inode * inode,struct file *filep){
	return 0;
}

static ssize_t mem_read(struct file *filep,char __user *buf,size_t size,loff_t *ppos){
	unsigned long p=*ppos;
	unsigned int count=size;
	int ret=0;
	struct mem_dev *dev=filep->private_data;


	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if(p>=MEMDEV_SIZE) //超范围
		goto out;
		//return 0;

	//超范围,读剩余
	if(count>MEMDEV_SIZE-p)
		count=MEMDEV_SIZE-p;

	if(copy_to_user(buf,(void *)(dev->data+p),count)){
		ret=-EFAULT;
	}
	else{
		*ppos+=count;
		ret=count;

		printk(KERN_INFO "read %d bytes from %d\n",count,p);
	}

out:
	up(&dev->sem);
	return ret;
}

//写
static ssize_t mem_write(struct file *filep,const char __user *buf,size_t size,loff_t *ppos){
	unsigned long p=*ppos;
	unsigned int count=size;
	int ret=0;
	struct mem_dev *dev=filep->private_data;

	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if(p>=MEMDEV_SIZE) //超范围
		goto out;
		//return 0;

	//超范围,读剩余
	if(count>MEMDEV_SIZE-p)
		count=MEMDEV_SIZE-p;

	if(copy_from_user(dev->data+p,buf,count)){
		ret=-EFAULT;
	}
	else{
		*ppos+=count;
		ret=count;

		printk(KERN_INFO "write %d bytes from %d\n",count,p);
	}

out:
	up(&dev->sem);
	return ret;
}


static loff_t mem_llseek(struct file * filep,loff_t offset,int whence){
	loff_t newpos;
	switch(whence){
		case 0:
			newpos=offset; //从文件头开始
			break;
		case 1:  //从当前位置开始
			newpos=filep->f_pos+offset;
			break;
		case 2:
			newpos=MEMDEV_SIZE-1+offset;//文件尾开始
			break;
		default:
			return -EINVAL;
	}

	if ((newpos<0) || (newpos > MEMDEV_SIZE)){
		return -EINVAL;
	}
	filep->f_pos=newpos;
	return newpos;
}


//cmd 由用户空间直接传递过来
//arg 无论数值/指针统一由 unsigned long 保存
static long mem_ioctl(struct file *filep,
		unsigned int cmd, unsigned long arg){
	
	int err=0,ret;
	struct mem_dev *dev=filep->private_data;

	//内核提供宏从cmd中解析TYPE,NR,DIR,SIZE
	if(_IOC_TYPE(cmd) !=MEMDEV_IOC_MAGIC) return -ENOTTY;
	if(_IOC_NR(cmd) > MEMDEV_IOC_MAXNR) return -ENOTTY;

	//access_ok用户空间指针检查
	if(_IOC_DIR(cmd) &_IOC_READ) //用户空间从内核读，则是内核向用户空间写
		err=!access_ok(VERIFY_WRITE,(void *)arg,_IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =!access_ok(VERIFY_READ, (void *)arg,_IOC_SIZE(cmd));
	if (err) return	-EFAULT;

	//驱动代码在内核空间因此用户空间的指针不能直接解引用使用，需要检查并复制指针指向的数据到内核空间
	switch(cmd){
		case MEMDEV_IOCRESET:
			memset(dev->data,0,MEMDEV_SIZE); //reset
			return 0;
		case MEMDEV_IOCSETB:
			ret = __get_user(dev->data[0],(char *)arg); //从用户空间拿一个字符到内核空间
			return ret;
		case MEMDEV_IOCGETB:
			ret = __put_user(dev->data[0],(char *)arg); //从内核空间拿一个字符到用户空间
			return ret;
		default:
			return -ENOTTY;
	}
}


static const struct file_operations mem_fops ={
	.owner=THIS_MODULE,
	.llseek=mem_llseek,
	.read=mem_read,
	.write=mem_write,
	.unlocked_ioctl=mem_ioctl,
	.open=mem_open,
	.release=mem_release,
};




static int memdev_init(void){
	int result=0;
	dev_t devno=MKDEV(mem_major,0); //构造设备编号
	int i;

	

	//[14512.214394] 27904
	//[14512.214399] 1073835265
	//[14512.214402] -2147390206
	
	printk(KERN_INFO "%d\n",(MEMDEV_IOCRESET));
	printk(KERN_INFO "%d\n",(MEMDEV_IOCSETB));
	printk(KERN_INFO "%d\n",(MEMDEV_IOCGETB));

	//指定了不为0的编号则静态申请
	if(mem_major)
		result=register_chrdev_region(devno,2,"memdev");
	else //动态申请
	{
		result=alloc_chrdev_region(&devno,0,2,"memdev"); //devno被填写
		mem_major=MAJOR(devno);
	}

	if (result<0) //failed
	{
		printk(KERN_INFO "memdev:can't get major %d\n",mem_major);
		return result;
	}

	cdev_init(&cdev,&mem_fops); //绑定操作
	cdev.ops=&mem_fops;
	cdev.owner=THIS_MODULE;

	
	//驱动和编号关联
	cdev_add(&cdev,MKDEV(mem_major,0),MEMDEV_NR_DEVS); //向内核注册
	mem_devp=kmalloc(MEMDEV_NR_DEVS * sizeof(struct mem_dev),GFP_KERNEL);

	if(!mem_devp){
		result=-ENOMEM;
		goto fail_malloc;
	}

//初始化自定义设备结构体
	for(i=0;i<MEMDEV_NR_DEVS;i++){
		sema_init(&mem_devp[i].sem,1);
		mem_devp[i].size = MEMDEV_SIZE;
		mem_devp[i].data=kmalloc(MEMDEV_SIZE,GFP_KERNEL);
		memset(mem_devp[i].data,0,MEMDEV_SIZE);
	}
	return 0;

fail_malloc:
	unregister_chrdev_region(devno,1);
	return result;
}


static void memdev_exit(void){
	int i;
	cdev_del(&cdev);
	for(i=0;i<MEMDEV_NR_DEVS;i++)
		kfree(mem_devp[i].data);
	kfree(mem_devp);

	unregister_chrdev_region(MKDEV(mem_major,0),2);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("...");
module_init(memdev_init);
module_exit(memdev_exit);
