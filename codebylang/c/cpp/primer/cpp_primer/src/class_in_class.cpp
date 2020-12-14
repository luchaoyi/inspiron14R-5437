#include<iostream>
using std::cout;
using std::endl;

class A{
public:
	int c;
	class B;

	A()
	{
		cout<<"A"<<endl;
		
	}
	A(int c){
		this->c=c; //this is指针
		cout<<"this->c is "<<(*this).c<<endl;
	}

	void mem(){ 
		cout<<"A"<<endl;
		cout<<c<<endl;
	}
};

class A::B{
public :
	static const int a=1;
	static const int b=2;
};

class C : A{
public:

	C(){
		cout<<"C"<<endl;
	}

	C(int c){
		A(1); //编译器已经调用了A(),这里自行调用A::A(int c)版本
		cout<<"this c"<<endl;
	}

};

class D:A{
public:
	D(int c){
		cout<<"this c"<<endl;
	}
};

int main(){
	A::B b;
	A a;              //a.B报错，类中的类型使用类::类使用
	cout<<A::B::a<<endl;    //作用域符的左边只能是class or namespace
	cout<<b.a<<endl; //b::a是错误的，对象不能使用::引用成员
/*----------------------*/

//父子，子父，先构造父类对象在构造子类对象,销毁顺序相反
//编译器会默认调用父类无参构造函数
//析构函数只能定义一个


	A a_0(1);
	cout<<"---"<<endl;
	C c;
	cout<<"---"<<endl;
	D d(1);
	cout<<"---"<<endl;
	C c_0(1);

	A *pa = new A();
	pa->mem();
	pa->c=10;
	pa->mem();
	(*pa).mem();
	return 0;
}
