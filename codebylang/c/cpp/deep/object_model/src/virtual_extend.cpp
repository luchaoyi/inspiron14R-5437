#include<iostream>
#include<typeinfo>
using namespace std;

class A {
public:
	virtual void FA() {
		cout << "FA" <<endl;
	}
};

class B: public A{
public:
	virtual void FB() {
		cout << "FB" <<endl;
	}
};

class C: public A{
public:
	virtual void FC() {
		cout << "FC" <<endl;
	}
};

class SUBD: public B,public C{
public:
	virtual void FD0() {
		cout << "FD0" <<endl;
	}

	virtual void FD1() {
		cout << "FD1" <<endl;
	}
};

typedef void(*PTRFUN)();

int main() {
	//D的内存布局
	//|Bvptr|Cvptr|,sizeof(D) is 16
	//vtbl按照声明顺序安排
	SUBD* d = new SUBD();
	cout << sizeof(*d) <<endl;
	long * base_addr =(long*)d; 
	long * Bvptr = (long *)*base_addr;
	long * Cvptr = (long *)*(base_addr+1);

	

	//第一份虚表子类D和父类B共享
	//B区域对应的虚表保存者继承A的FA,B定义的FB和D定义的FD0,FD1
	((PTRFUN)Bvptr[0])(); 
	((PTRFUN)Bvptr[1])(); 
	((PTRFUN)Bvptr[2])(); 
	((PTRFUN)Bvptr[3])(); 
	cout<<"---"<<endl;

	//第二份虚表仅包含父类C的虚函数
	//C区域对应的虚表保存者继承A的FA,C定义的FC
	//第二个C的虚表不包含D独有的虚函数
	((PTRFUN)Cvptr[0])(); 
	((PTRFUN)Cvptr[1])(); 
	//((PTRFUN)Cvptr[2])(); //g++编译器第二个父类没有重复包含子类定义的函数
	//子类定义的函数在第一个虚表
	//C区域对应的虚表保存者继承A的FA,C定义的FC

	//vtbl[0]处为第一个虚函数,vtbl[-1]处为type_info信息
	type_info* tp;
	cout<<"---"<<endl;
	tp = (type_info*)(*(Bvptr-1));
	cout << tp->name() <<endl;
	tp = (type_info*)(*(Cvptr-1));
	cout << tp->name() <<endl;
	return 0;
}
