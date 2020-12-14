#include<iostream>
using namespace std;

class A {
public:
	A() {
		cout << "A" << endl;
	}

	~A() {
		cout << "~A" << endl;
	}
};

class B {
public:
	A a[5];
};


class C{
public:
	virtual void test() {
		cout << "C" << endl;
	}
};


// 栈由编译器复杂管理 栈中的对象和对象数组，编译器自动调用其构造函数和析构函数
// 堆由程序员自己管理，堆对象的构造和释放由程序员new/delete自行控制
// B中的对象成员a，由编译器负责正确调用构造和析构函数
//编译器递归的处理对象，对象成员的构造和析构
//指针和引用交给了程序员，程序员也需要递归的处理指针和引用，保证它们的正确性

int main() {
	A a[3];
	cout << "- - -" << endl;
	B b;
	cout << " - - - " << endl;
	//b1在堆中new/delete控制生命周期，编译器要保证构造和析构它的成员a
	B* b1 = new B; 
	delete b1;
	cout << " - - - " << endl;
	//C* c;      //c(this)->vptr->test(); c没有赋值，引用时coredump
	//c->test();
	return 0;
}
