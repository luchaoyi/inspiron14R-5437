#include<stdio.h>


char * strcpy(char *dst,const char * src){
	char *s=dst;
	while(*dst++=*src++)  //<=> while((*dst++=*src++)!='\0')    while(not 0) 循环 while(0)结束循环 '\0' ASCII值为0
		;
	return s;
}


int main(){
	char src_a[5]="hello";  //'\0'默认在末尾,应该设置数组长度为6，这里gcc没有报错,g++直接报错了，gcc这里的实现不符合标准
	char dst_a[1];
	char s[]="hello";

	char *str="lllll!"; //str指向一个常量字符串

	printf("%d\n",sizeof(s));//->6
	
	printf("%d\n",sizeof(src_a));
	printf("%s\n",src_a);
	
	strcpy(dst_a,src_a);
	
	printf("%s\n",dst_a); //sizeof眼中dst_a是数组，长度定义1,printf位置的dst_a被处理为指针因此可以打印出hello
	printf("%d\n",sizeof(dst_a)); //数组长度1,字符串打印了hello

	str[1]='x';           //str指的位置存储在只读的segment因此修改会引发错误
	printf("%s\n",str); 

	return 0;
}
















