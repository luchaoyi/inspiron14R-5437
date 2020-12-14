#include<iostream>
using namespace std;
int main() {
/*
  40089d:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%rbp)      temp = 1, a is 1  
  4008a4:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax       ap = &temp,-0x18(%rbp) is ap
  4008a8:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  4008ac:	48 8b 45 e8          	mov    -0x18(%rbp),%rax     
  4008b0:	48 89 45 f0          	mov    %rax,-0x10(%rbp)    bp = ap,-0x10(%rbp) is ap
  4008b4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax    
  4008b8:	c7 00 07 00 00 00    	movl   $0x7,(%rax) *bp = 7  
*/
	const int a = 1;
	const int *ap=&a;
	int *bp=const_cast<int *>(ap);
	*bp = 7 ;
	// a is const 编译器生成代码时用到a的地方直接使用的是立即数1
	// *ap=&a，编译器在内存中分配一空间赋值为a,此后ap和bp操作的都是这个空间
	cout <<a<<endl; //1
	cout<<*ap<<endl; //7
	cout<<*bp<<endl; //7
	return 0;
}
