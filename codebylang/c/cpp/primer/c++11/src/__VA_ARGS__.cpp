#include<iostream>
using namespace std;

#define EXEC(func_name,T,a,...)			\
	do {								\
		auto temp = (T)a;				\
		func_name(temp,__VA_ARGS__);	\	
	}while(0)							\

void test(float a,int b,int c,int d) {
	cout <<a+b+c+d << endl;
}

int main() {
	EXEC(test,int,1.2,1,2,3);
	EXEC(test,double,1.2,1,2,3);
	return 0;
}
