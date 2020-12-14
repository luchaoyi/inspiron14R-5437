#include<iostream>
using namespace std;


void func(){
	cout << "xx" << endl;
}

class A{
public:
	A() {
		cout << "ctor \n";
	}
	A(const A& a){
		v=1;
		func();
		cout << "copy ctor \n";
	}

	//返回A&是为了级联赋值时避免无谓的拷贝
	//返回A也支持级联赋值，但无谓多了copy
	//返回引用类似返回指针,返回的引用，引用的对象
	//返回引用避免了返回对象->临时对象的拷贝
	A& operator= (const A& a) {
		cout << "op = \n";
		return *this;
	}
	int v;

};



A test0() {
	cout << "test 0 \n";
	A a;
	a.v=2;
	cout << &a <<endl;
	return a;
}

A& test1(){
	cout << "test 1 \n";
	A a;
	return a;
}


A&& test2(){
	cout << "test 2 \n";
	return A();
}

int main() {
	A a;
	A b;
	A c;
	c=a=b;
	cout << "---\n";
	A &ref = a; //名字ref和名字a引用的是相同对象，ref是a的别名
	A r = a;
	cout << "---\n";
	
	//这里优化了，一次copy都没有...
	A&& x0 = test0();
	cout << x0.v << "\n";
	cout << &x0 <<endl;
	// 返回引用 接收引用 完全没有copy ctor
	A &x1 = test1();
	//临时对象->x2 copy
	A x2 = test2();
	//无copy
	A &&x3 = test2();
	return 0;
}
