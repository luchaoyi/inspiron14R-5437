#include <linux/init.h>
#include <linux/module.h>


static int n=0;
static char *s="abc";

module_param(n,int,S_IRUGO);
module_param(s,charp,S_IRUGO);


//printk产生的信息可使用dmesg查看
static int hello_init(void)
{
    printk(KERN_ALERT "Hello, world !\n");
    printk(KERN_ALERT "%d\n",n);
    printk(KERN_ALERT "%s\n",s);

    return 0;
}
static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye,  world\n");
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
