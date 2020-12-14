#include<iostream>
using namespace std;

class Singleton {
public:
	// 第一次使用时才产生
	static Singleton* Instance() {
		if (!pInstance_)
			pInstance_ = new Singleton;
		return pInstance_;
	}

	// 多线程Double Check
	// double check的正确性依赖于，编译器重排不能交换1和2的顺序
	// 多线程下volatile pInstance_;
	static Singleton* Instance() {
		if (!pInstance_) {
			std::lock_guard<std::mutex> lk(mut);  //1
			//mem_fence();
			if (!pInstance_) {                    //2 
				pInstance_ = new Singleton;
			
			}
		}
		return pInstance_;
	}

private:	
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	//避免用户delete
	~Singleton() {
		if (!pInstance_)
			delete pInstance_;
	}
	static Singleton* pInstance_;
};

Singleton* Singleton::pInstance_ = 0;


// 饿汉式 本就是线程安全的，因为在main之前对象九创建了
class Singleton1 {
public:
	static Singleton* Instance() {
		return &Instance_;
	}

private:	
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	// 静态变量初始化，main函数执行前，无论有没有使用，都初始化了
	// 可保证线程安全性
	~Singleton();
	static Singleton Instance_;
};

Singleton Singleton::Instance_;

// 利用静态变量仅执行一次的特性
// c++11 线程安全的
class Singleton2 {
public:
	// Instance初次调用时初始化，注册析构函数到atexit中
	// obj的销毁在程序结束时
	static Singleton& Instance() {
		// Lock() c++11不用加锁，编译器保证静态变量初始化线程安全
		static Singleton obj; //<- 仅执行一次
		// Unlock()
		return obj;
	}

private:	
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	// 静态变量初始化，main函数执行前，无论有没有使用，都初始化了
	// 禁止用户delete
	~Singleton();
};

/*
销毁顺序与生命周期管理
template<typename T,typename T_Destroyer>
void SetLongevity(T* pObj, unsigned longevity, T_Destroyer d) {
1.新加入元素pObj到数组
2.根据longevity使最大的在头部
3.atexit注册一个函数(先从尾部取元素，然后调用Destroyer)
}
*/

int main() {
return 0;
}
