#include<iostream>
using namespace std;

//重载，覆盖与隐藏
class O {
public:
	/*重载f0
	 * */
	virtual void f0() {
		cout << "O f0" << endl;
	}
	virtual void f0(int a) {
		cout << "O f0 int a" << endl;
	}
	virtual void f0(char a) {
		cout << "O f0 char a" << endl;
	}
	virtual void f1() {
		cout << "O f1 char a" << endl;
	}
	static void f2() {
		cout << "O f2" <<endl ;
	}
};

class S : public O{
public:

	/*
	子类f0(),重写(覆盖)了父类的f0();
	此时父类的f0(int)和f0(char)被隐藏
	*/
	virtual void f0() {
		cout << "S f0" << endl;
	}
	virtual void f3() {
		cout << "S f3" << endl;
	}
};

int main() {
	S* sptr = new S;
	sptr->f0();
	sptr->f1();
	//隐藏，静态行为被编译器禁止
	//sptr->f0(1); 编译失败被隐藏
	//sptr->f0('1'); 编译失败被隐藏
	
	//通过父类指针可以调用
	//虚函数机制依然可以调用
	O* osptr = new S;
	osptr->f0();
	osptr->f0(1);
	osptr->f0('1'); 
	osptr->f1();


	void (*vf) ();
	void (*intf) (int);
	void (*cf) (char);
	void (*vf1) ();
	void (*vf3) ();
	//sptr首地址处存放的虚表地址
	//通过找到虚表中函数按照声明顺序排序
	//索引0位置为f0()
	//索引1位置为f0(int)
	long *this_addr = (long*)sptr;
	long vtbl_addr = *this_addr;
	long *vptr = (long*)vtbl_addr;
	vf = (void(*)())vptr[0];
	intf = (void(*)(int))vptr[1];
	cf = (void (*) (char))vptr[2];
	vf1 = (void (*) ())vptr[3];
	vf3 = (void (*) ())vptr[4];
	cout << "---" <<endl;
	vf();
	intf(1);
	cf('1');
	vf1();
	vf3();
	cout << "---" <<endl;
	//总结:被隐藏是编译器层面的禁止调用，但函数还是存在的并且在虚表中被正确设置
	O::f2();
	return 0;
}
