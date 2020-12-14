#include<iostream>
using namespace std;

//c++11允许模板参数可变，即不确定参数，要访问模板变参参数列表只能通过<F7>模板递归的方式
template <typename T>
void handleValue(T value){cout<<value<<endl;}

//停止条件
template <typename T>
void processValues(T arg)
{
	handleValue(arg);
}

template <typename T1,typename... Tn>
void processValues(T1 arg1,Tn... args)
{
	processValues(arg1);
	processValues(args...); //递归                    
}

//编译器优先找非模板的具体类型函数，没有则对模板类型实例化调用实例化后的模板函数
//可指明实例化类型
int main(){
	processValues(1,2.5,"lcy");//自动推导则2.5为浮点数
	processValues<int,int,const char*>(1,2.5,"lcy"); //指明2.5类型为int时输出为2,2.5被隐式转换为int
	return 0;
}


