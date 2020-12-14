#include <iostream>
#include <vector>
using namespace std;

/*
传值和传引用不同时存在
void process(int i)//值
{
    cout << "process(int): " << i << endl;
}
*/ 


void process(int& i)//左值引用
{
    cout << "process(int&): " << i << endl;
}

void process(int&& i)//右值引用
{
    cout << "process(int&&): " << i << endl;
}

void forward(int&& i)
{
	//右值引用，引用右值，但右值引用是一个左值
    cout << "forward(int&&): " << i << ",  ";
    process(i); //不完美的转发，在这个位置,i是一个有名字的对象，右值引用是一个左值
	process(move(i));//转为右值

}


/*
 传入左值时T被推导为 int &,t的类型为int& && ->int &
 传入右值时T推导为int,t的类型为int && 
 模板允许接受左右引用
 */
template <typename T>
void other_forward(T&& t) {
	process(std::forward<T>(t));
	process(static_cast<T &&>(t));  
}


int main(int argc, const char * argv[]) {
    int a = 0;

    process(a);
    process(1);

	process(std::forward<int &>(a)); //保持左值和右值属性保持不变
	process(std::forward<int &&>(1));

	cout << "#-#" << endl;
	int&& b = move(a);
	process(b); //右值引用是左值

	cout << "#-#" << endl;
    forward(move(a));//强制转换为右值,std::move()强制转换为右值引用
    forward(1); 
	
	cout << "#-#" << endl;
	other_forward(a);
	other_forward(1);

    return 0;
}
