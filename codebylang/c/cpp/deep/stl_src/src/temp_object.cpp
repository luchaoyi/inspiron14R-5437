#include<iostream>
using namespace std;

class O {
public:
	O() {
		cout<<"O" <<endl;
	}
	O(int) {
		cout<<"O int" <<endl;
	}
	O(int,int){
		cout<<"O int int" <<endl;
	}

	void operator() () {
		cout<<"call()" <<endl;
	}
};

void test(...){}

int main() {
	O o;
	o();
	O(); //不是函数调用是产生临时对象
	O()(); //先构造临时对象，后函数调用
	test(O(),O(1),O(1,2));
	return 0;
}
