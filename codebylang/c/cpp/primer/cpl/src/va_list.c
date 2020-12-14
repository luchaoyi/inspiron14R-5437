#include<stdio.h>
#include<stdarg.h>



#define __VA_LIST__
#ifndef __VA_LIST__
#define va_list char*
#define va_start(ap,arg) (ap=(va_list)&arg+sizeof(arg))
#define va_arg(ap,t) (*(t*)((ap+=sizeof(t))-sizeof(t))) 
#define va_end(ap) (ap=(va_list)0)
#endif

/*
  声明va_list只是为char*,只是为了指针运算时单位为1
*/

/*可变参数相关的宏定义在stdarg.h中,上面是自己定义的宏,已经注释没有使用
 * */


void  simple(char *format,...){
	char c;
	va_list ap;
	va_start(ap,format);

	while(c=*format++){
		if(c=='d'){
			printf("%d\n",va_arg(ap,int));
		}
		else{
			printf("%c\n",(char)va_arg(ap,int));
		}
	}
	va_end(ap);
}

int main(){
	simple("dcdc",4,'a',5,'b');
	return 0;
}
