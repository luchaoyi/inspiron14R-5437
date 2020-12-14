#include<iostream>
using namespace std;

//编译时assert
template<bool> struct Simple_Assert;
template<> struct Simple_Assert<true> {};

#define SIMPLE_CHECK(expr) \
	Simple_Assert<(expr)>();

//可附加消息的编译时assert
template<bool> struct Static_Assert {
	Static_Assert(...){};
};
template<> struct Static_Assert<false> {};

#define STATIC_CHECK(expr, msg) \
	{\
		class ERROR_##msg{}; \
		new Static_Assert<(expr)>(ERROR_##msg()); \
	}


//常数做编译期分派
//常数->类型->分派
template<int v>
struct Int2Type {};


template<bool FLAG>
void dispaly() {
	show(Int2Type<FLAG>());
}

void show (Int2Type<true>) {
	cout << "T" << endl;
}

void show(Int2Type<false>) {
	cout << "F" << endl;
}

//空对象Type2Type<T>作类型分派，比直接使用类型T分派开销小
template<typename T>
struct Type2Type {};


//型别选择,false选择U
template<bool flag, typename T, typename U>
struct Select{
	typedef T Result;
};

template<typename T, typename U>
struct Select<false,T,U>{
	typedef U Result;
};


// 侦测是否可转换
template<typename T, typename U>
class Conversion {
	typedef char Small;
	class Big{char dummy[2];};
	//T->U? Small : Big 
	static Small Test(U);
	static Big Test(...);
	static T MakeT();
public:
	// 没有代码执行，只有类型推导
	// 利用sizeof的类型推导机制,隐藏在sizeof背后有一套完整的expr类型推导机制
	enum{
		exists = sizeof(Test(MakeT())) == sizeof(Small),
		//是否可以双向转换
		exists2Way = exists && Conversion<U,T>::exists,
		// T is U
		sameType = false
	};
};

// 特化 T is U
template<typename T>
class Conversion<T,T> {
public:
	enum {
		exists = 1, exists2Way = 1, sameType = 1
	};
};

// 继承关系判断 U : public T
// U*可以向T* 转型，U!=T，且T 不是void*
#define SUPER_SUB(T,U) \
	(Conversion<const U*, const T*>::exists && \
	 !Conversion<const T*, const void*>::sameType && \
	 !Conversion<T,U>::sameType)

class NullType;
class EmptyType{};

template <typename T>
class TypeTraits{
private:

	template<typename U> class UnConst {
		typedef U Result;
	}

	// 特化去除const修饰
	template<typename const U> class UnConst {
		typedef U Result;
	}
public:
	typedef UnConst<T>::Result NonConstType;
};

int main() {
	SIMPLE_CHECK(1 > 0);
	STATIC_CHECK(1 > 0, INVAILD_PTR);
	dispaly<true>();
	dispaly<false>();

	cout << Conversion<bool, char*>::exists << endl;

	cout << Conversion<double, char>::exists << endl;
	cout << Conversion<double, char>::exists2Way << endl;
	cout << Conversion<double, char>::sameType << endl;

	double *p;
	void *q;
	// 隐式转换不可以，C强制转换可以
	p=(double *)q;

	cout << Conversion<double*, void*>::exists << endl; // 1
	// invaild conversion from void* to double*
	cout << Conversion<double*, void*>::exists2Way << endl; // 0
	cout << Conversion<double*, void*>::sameType << endl; //0
	return 0;
}
