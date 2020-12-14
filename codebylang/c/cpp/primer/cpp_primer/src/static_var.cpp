#include <stdio.h>

//声明：指定变量的名字和类型，可以多次声明。
//定义：为该成员变量分配存储空间，有且仅有一个定义。
//初始化：为该成员变量赋初值
class A {
public:
static int a; //声明但未定义，还未分配内存,链接出错，A::a未定义
// static int a = 1; //禁止编译,非const static;
//const static int a = 1; //声明+定义+初始化
};

//int A::a;//定义
int A::a = 2; //定义+初始化

class B{
public:
	B() {
		printf("-B-\n");
	}
};

//test 被调用时B才初始化，且仅初始化一次
void test() {
	static B b;
}

static B b; //初始化在main之前发生
int main() {
printf("%d\n", A::a);
test();
test();
test();
return 0;
}

/*
全局/静态变量放置在data或bss段
对于基本类型,若有初始化值则在data段直接编译初始化值到文件，否则在bss段
对于对象，都在bss段，因为对象初始化要调用构造函数,编译时无法获取

静态初始化 
	加载器加载文件时为data和bss段数据分配空间并初始化基本类型为编译文件指定值(.data)/默认值(.bss)
动态初始化 
	在main函数之前，.init段代码执行对全局/静态对象调用构造函数

静态初始化在加载时完成,可认为所有的静态初始化过程是同步完成的
动态初始化，则在main函数之前完成，对于同一个编译单元内的静态变量，动态初始化顺序等同于定义顺序，而对于跨编译单元的静态变量，初始化顺序未定义

construt on first use idiom
	若静态对象被定义在函数内，则直到函数第一次被调用才初始化，利用这样的特性可明确顺序，消除不确定性
*/ 
