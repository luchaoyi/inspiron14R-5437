#include<iostream>
#include<exception>

using std::cout;
using std::endl;
using std::dec;


class B0{
public:
	int a=1;
	virtual void s0(){
		cout<<"s0"<<endl;
	}

	virtual void s1(){
		cout<<"s1"<<endl;
	}


};

class B1{
public:
	int b=2;
	virtual void s3(){
		cout<<"s3"<<endl;
	}
	virtual void s4(){
		cout<<"s4"<<endl;
	}

};

class A:public B0, public B1{
public:
	virtual void s0(){
		cout<<"A,s0"<<endl;
	} 

	virtual void s3(){
		cout<<"A,s3"<<endl;
	}

	virtual void s5(){
		cout<<"A,s5"<<endl;
	}
};



void show(){
	cout<<"show"<<endl;
}




int main()
{
	A a;
	cout<<sizeof(a)<<endl;
	cout<<sizeof(int)<<endl;

	B0 *p0=&a;
	B1 *p1=&a;
	
	cout<<dec<<p0<<endl;
	cout<<dec<<p1<<endl;

	//多重继承中父类指针只能访问和子类共有的方法
	p0->s0();
	p0->s1();
	//p0->s3(); error p0不能访问s3(),因为B0没有S3()

	//p1->s0(); error p1不能访问s0(),因为B1没有S0() 
	p1->s3();
	p1->s4();

	//p0->s5(); error
	//p1->s5(); error 
	
	
	//a对象的8Byte数据
	//包含两个虚表指针16B，两个int 8B,以及对齐8B
	int *p=(int *)&a;
	cout<<p<<endl;
	cout<<*p<<endl;
	cout<<*(p+1)<<endl;
	cout<<*(p+2)<<endl;
	cout<<*(p+3)<<endl;
	cout<<*(p+4)<<endl;
	cout<<*(p+5)<<endl;
	cout<<*(p+6)<<endl;
	cout<<*(p+7)<<endl;


	void (*f)();
	f=show;
	f();


	return 0;
}
