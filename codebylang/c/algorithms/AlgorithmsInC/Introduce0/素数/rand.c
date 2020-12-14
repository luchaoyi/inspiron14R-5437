/*rand()函数是产生随机数的一个随机函数。C语言里还有 srand()函数等。


rand()函数是产生随机数的一个随机函数。C语言里还有 srand()函数等。


(1)使用该函数首先应在开头包含头文件stdlib.h
#include<stdlib.h>(C++建议使用#include<cstdlib>，下同)
(2)在标准的C库中函数rand()可以生成0~RAND_MAX之间的一个随机数，其中RAND_MAX 是stdlib.h 中定义的一个整数，它与系统有关。
(3)rand()函数没有输入参数，直接通过表达式rand()来引用；例如可以用下面的语句来打印两个随机数：
printf("Random numbers are: %i %i\n",rand(),rand());
(4)因为rand()函数是按指定的顺序来产生整数，因此每次执行上面的语句都打印相同的两个值，所以说C语言的随机并不是真正意义上的随机，有时候也叫伪随机数。
(5)为了使程序在每次执行时都能生成一个新序列的随机值，我们通常通过为随机数生成器提供一粒新的随机种子。函数 srand()(来自stdlib.h)可以为随机数生成器播散种子。只要种子不同rand()函数就会产生不同的随机数序列。srand()称为随机数生成器的初始化器。



/* This program generates and prints ten random integers between 1 and RAND_MAX*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
unsigned int seed; /*申明初始化器的种子，注意是unsigned int 型的*/
int k;
printf("Enter a positive integer seed value: \n");
scanf("%u",&seed);
srand(seed);
printf("Random Numbers are:\n");
for(k = 1; k <= 10; k++)
{
printf("%i",rand());
printf("\n");
}
return 0;
}
/*当提供的种子相同时，随机数序列也是相同的。而且当种子为1时，与不使用srand()函数时一样的，也就是说rand()函数默认情况下初始化种子值为1；
在stdlib.h 中这两个函数的原型是：
int rand();
void srand (unsigned int);
srand(time(0)); i=rand();
或者srand(time(NULL));
这样i就是一个真正意义上的随机数。
rand()产生伪随机数，srand函数提供种子，种子不同产生的随机数序列也不同，所以通常先调用srand函数 time()返回的是系统的时间（从1970.1.1午夜算起），单位：秒，种子不同当然产生的随机数相同几率就很小了。
用rand()随机生成在[x,y]内的整数
int k;
k=x+rand()%(y-x+1)/*k即为所求范围内随机生成的数，rand()%a的结果最大为a-1*/
