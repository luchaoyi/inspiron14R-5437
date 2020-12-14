#include<iostream>
using std::cout;
using std::endl;

class A{
public:
	int a=1;
	A(){
		cout<<"A"<<endl;
	}
};

class B:public virtual A{
public:
	int b=2;
	B(){
		cout<<"B"<<endl;
	}
};

class C:public virtual A{
public:
	int c;
	C(){
		cout<<"C"<<endl;
	}
};

class D:public B,public C{
public:
		int d;
		D(){
		cout<<"D"<<endl;
		}
};

int main(){
	D d;
	cout<<d.a<<endl;
	return 0;
}

