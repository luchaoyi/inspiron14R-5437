#include<iostream>
 
using namespace std;
 
class A
{
public:
	A(int a) 
	{
		this->a = a;
		cout << "in constructor" << endl;
	}


	A(A* test) 
	{
		this->a = test->a;
		cout << "in copy constructor" << endl;
	}
	void printA()
	{
		cout << this->a << endl;
	}
private:
	int a;
};


int & test(int &t) {
	t+=1;
	return t;
}

int main(void)
{
	A a(2);
	A b(&a);
	b.printA();

	int t =1;
	test(t)= test(t)=test(t);
	cout<< t <<endl;

	return 0;
}
