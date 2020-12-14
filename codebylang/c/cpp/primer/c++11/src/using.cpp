#include<iostream>
using namespace std;

class A{
public:
	void f() {
		cout << "A::f" <<endl;
	}

	virtual void vf() {
		cout << "A::vf" <<endl;
	}
};

class B:public A {
public:
	//B定义的f(int)隐藏了父类的f(),使用using引入到B的作用域
	using A::f;
	void f(int i) {
		cout << "B::f" <<endl;
	}
};

int main() {
	B b;
	b.f();
return 0;
}
