//通过结构体变量中某个成员的首地址进而获得整个结构体变量的首地址
#define offsetof(TYPE, MEMBER) ((size_t)& ((TYPE *)0)->MEMBER) //假设在0地址分配了一个结构体,通过它的MEMBER成员的地址可以得到偏移量
#define container_of(ptr, type, member) ({ \
 
       const typeof( ((type *)0)->member ) *__mptr = (ptr); \
 
       (type*)((char *)__mptr - offsetof(type,member));})
