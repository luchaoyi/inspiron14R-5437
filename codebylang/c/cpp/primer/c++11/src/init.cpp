
#include<iostream>
#include<vector>
using namespace std;

/* 
默认初始化:没有初始化，由编译器默认操作
值初始化:使用了(),{}初始化器，但没有指定初始化值
	类类型则调用其默认构造函数，如果没有默认构造函数，则不能进行初始化
	不同类型则默认初始化
直接初始化 使用(),{}并指定初始化值,直接构造
拷贝初始化 调用拷贝/移动构造函数的初始化 ,拷贝/移动构造,基本类型拷贝初始化和直接初始化没有什么区别，类类型多了
对象拷贝，有开销
列表初始化 使用{}初始化，编译器首先尝试列表初始化，失败则尝试其它初始化方式，如直接/拷贝等
*/ 


int main() {
	vector<int> a; //默认初始化
	vector<int> b(); //值初始化
	vector<int> c(10); //值初始化
	cout <<"c.size():" <<c.size() <<endl;
	for (const auto& z : c) {
		cout << z <<endl;
	}
	vector<int> d{1,2,2,3,4}; //列表初始化
	vector<int> e(10,2); //直接初始化

	cout << "e.size():"<<e.size() <<endl;
	for (const auto& z : e) {
		cout << z <<endl;
	}

	//拷贝初始化
	vector<int> f = d;
	vector<int> g(d);
}
