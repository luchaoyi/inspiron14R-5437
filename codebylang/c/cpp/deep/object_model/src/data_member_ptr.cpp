#include<iostream>
#include <stdio.h>
using namespace std;

class X{
public:
	virtual ~X(){};
	X():x(1),y(2),z(3.1) {}
	void show(int i) {
		cout << i << endl;
	}
	virtual void print(int i) {
		cout << i <<endl;
	}

	virtual void printp(int i) {
		cout << i <<endl;
	}

	int x;
	int y;
	float z;
};

int main() {
	//类型为X::
	int X::*px = &X::x; 
	int X::*py = &X::y;
	float X::*pz = &X::z;
	void (X::*pf)(int) = &X::show;
	void (X::*vpf)(int) = &X::printp;

	X test;
	cout << test.*px <<endl;
	cout << test.*py <<endl;
	cout << test.*pz <<endl;
	(test.*pf)(5);
	(test.*vpf)(-5);


	
	//												0           8   16     24
	//class X的内存布局 |vptr|x|y|z|,vptr -> vtbl = [&type_info|&~X,&print,&printp]
	//类数据成员指针是成员变量的offset
	printf("%d\n",px); //8 offset
	printf("%d\n",py); //12 offset
	printf("%d\n",pz); //16 offset
	//指向类实例化的对象test的成员z的指针是普通指针 
	float * ptz = &test.z; 
	printf("%p\n",ptz); //对象的成员得到addr

	//指向类非虚成员函数指针的指针是地址,本质上类的普通成员函数被转化为添加this指针的普通成员函数
	printf("%p\n",pf);  // 类非虚函数addr 
	//指向类虚函数的成员函数指针是offset
	printf("%d\n",vpf); //类虚函数offset 输出25,25-1=24

return 0;
}
