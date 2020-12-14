#include<stdio.h>
/*
	void *可以接受任何类型的赋值(不能接受小数,因为地址是整数)
	void *可以赋值给任何类型的变量 但是需要进行强制转换
*/
int main(){
	//void a //直接error
	void *a=1; //这里a存储了1
	a++;
	a=(int)a+1;
	//a=(int)a+1.1;  //error: incompatible types when assigning to type ‘void *’ from type ‘double
	//不能和float操作
	printf("%d\n",a);

	void *b="1244"; //这里b->[1244]
	printf("%d\n",b); //b=4195928是"1244"的存储地址
	printf("%s\n",b);


	//void *c=1.2;    //error 地址不可能出现小数
	
return 0;
}






