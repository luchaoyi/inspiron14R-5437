#include<iostream>
#include<typeinfo>
using namespace std;
/*
利用模板trait可实现类型函数,输入为类型，为类型返回结果
*/ 

class C{
public:
	C(double a) {
		d=a;
	}
	void operator +=(int a) {
		d += a;
	}
	double d;
};

//类型大小
template<typename T> 
size_t sizeOf() {
	return sizeof(T);
}

//类型是否为class
template<typename T>
class IsClass{
	typedef char One;
	typedef struct {char a[2];} Two;
	template<typename C>
	static One test(int C::*);
	template<typename C>
	static Two test(...);
public:
	// 替换失败非错误,只有T为class时才匹配One,其它匹配TWO
	const static bool FLAG = (sizeof(IsClass<T>::test<T>(0)) == 1);
};

// 根据bool C，决定使用类型 
template <bool C, typename Ta, typename Tb>
class IfThenElse;

template <typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb> {
public:
	typedef Ta TYPE;
};

template <typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb> {
public:
	typedef Tb TYPE;
};

//求和时选择尺寸大的作为返回类型
template<typename T1, typename T2>
typename IfThenElse<(sizeof(T1)>sizeof(T2)), T1, T2>::TYPE
add (T1 a, T2 b) {
	return a + b;
}

template<typename T>
class Param {
public:
	// Class类型使用引用类型，非class使用值类型
	typedef typename IfThenElse<(IsClass<T>::FLAG),
			T&,T>::TYPE  PARAMTYPE;
};

template<typename T>
void test(typename Param<T>::PARAMTYPE a) {
	a+=5;
}

/*
约定仿函数的第N个参数类型为ParamNT
给定一个类型函数，根据仿函数和N给出，仿函数的第N个参数类型
*/
template<typename T1, typename T2, typename T3>
class DemoFunctor {
public:
	enum{NumParams = 3};
	typedef T1 Param1T;
	typedef T2 Param2T;
	typedef T3 Param3T;
	typedef T3 ReturnT;
	ReturnT operator() (T1 a,T2 b,T3 c) {
		return a+b+c;
	}
};

template<typename F, int N>
class UsedFunctorParam;

#define FunctorParamSpec(N)               \
	template<typename F>			      \
    class UsedFunctorParam<F, N> {		  \
	public:                               \
	typedef typename F::Param##N##T Type; \
}                                         

//FunctorParamSpec(1);
template<typename F>			      
class UsedFunctorParam<F, 1> {		
public:
	typedef typename F::Param1T Type;
};

FunctorParamSpec(2);
FunctorParamSpec(3);
FunctorParamSpec(4);
FunctorParamSpec(5);
// ...定义到20,很少有多于20个参数的函数
FunctorParamSpec(20);

#undef FunctorParamSpec 

template<typename F, int N>
class FunctorParam {
private:

	class Unused {
	private:
		class Private{};
	public:
		typedef Private Type;
	};

public:
	// N大于F的参数数量，相当于越界，返回一个私有空类型 
	typedef typename IfThenElse<F::NumParams>=N,
		UsedFunctorParam<F,N>,
		Unused>::TYPE::Type Type;
};


template<typename T1, typename T2, typename RT>
class DemoBindFunctor {
public:
	enum{NumParams = 2};
	typedef T1 Param1T;
	typedef T2 Param2T;
	typedef RT ReturnT;
	ReturnT operator() (T1 a,T2 b) {
		return a / b;
	}
};

/*
模仿binder1st/binder2nd,实现一个binder
 */
//占位符
class _p1 {};
class _p2 {};

template<typename Functor,typename Placement>
class binder;

template <typename Functor>
class bin_function {
public:
    typedef typename Functor::Param1T T1;
	typedef typename Functor::Param2T T2;
	typedef typename Functor::ReturnT RT;
};

//binder1st 
template<typename Functor>
class binder<Functor,_p1> : 
public bin_function<Functor> {
private:
	Functor f;
	typename bin_function<Functor>::T1 value;
public:
	binder(const Functor& op, 
			const typename bin_function<Functor>::T1& x1) :f(op), value(x1) {}
	typename bin_function<Functor>::RT 
		operator() (const typename bin_function<Functor>::T2& x2) {
		return f(value, x2);
	}
};

//binder2nd 
template<typename Functor>
class binder<Functor,_p2> : 
public bin_function<Functor> { 
private:
	Functor f;
	typename bin_function<Functor>::T2 value;
public:
	binder(const Functor& op, 
			const typename bin_function<Functor>::T2& x2) : f(op), value(x2) {}

	typename bin_function<Functor>::RT 
		operator() (const typename bin_function<Functor>::T1& x1) {
		return f(x1, value);
	}
};

//基本操作定义一个inline做类型推导
template<typename Functor,typename Placement,typename T>
inline binder<Functor,Placement> bindf(Functor f,Placement p, T val) {
	return binder<Functor,Placement>(f,val);
}

//封装函数指针为functor使其适应框架
template<typename T1, typename T2, typename RT>
class FunctorPtr{
public:
	enum{NumParams = 2};
	typedef T1 Param1T;
	typedef T2 Param2T;
	typedef RT ReturnT;
	FunctorPtr(RT (*fptr)(T1,T2)) : fptr(fptr) {}
	ReturnT operator() (T1 a,T2 b) {
		return fptr(a,b);
	}
private:
	RT (*fptr)(T1,T2);
};

//辅助类型推导函数
template<typename T1, typename T2, typename RT>
inline FunctorPtr<T1,T2,RT> func_ptr(RT (*fptr)(T1,T2)) {
	return FunctorPtr<T1,T2,RT>(fptr);
}

int demo(int a,int b) {
	return a - b;
}


enum class DataType {
	SHORT,
	INT,
	FLOAT
};

template<DataType d>
class Type;

template<>
class Type<DataType::SHORT>{
public:
	typedef short TYPE;
};

template<>
class Type<DataType::INT>{
public:
	typedef int TYPE;
};

template<>
class Type<DataType::FLOAT>{
public:
	typedef float TYPE;
};

DataType DT(const DataType& dt) {
	return dt;
}

int main() {
	cout << sizeOf<int>() << endl;
	cout << IsClass<int>::FLAG <<endl;  
	cout << IsClass<C>::FLAG <<endl;  
	auto c = add(1.2, 1);
	cout << c << ":" << typeid(c).name() << endl;
	//Class类型传引用类型，非class传值
	int i = 1;
	C cc(1.0);
	test<C>(cc);
	test<int>(i);
	cout << cc.d << endl;
	cout << i << endl;

	typedef DemoFunctor<char*, int& , double&&> DF;
	cout<<typeid(FunctorParam<DF, 1>::Type).name()<<endl; //Pc 
	cout<<typeid(FunctorParam<DF, 2>::Type).name()<<endl; //i
	cout<<typeid(FunctorParam<DF, 3>::Type).name()<<endl; //d
	cout<<typeid(FunctorParam<DF, 4>::Type).name()<<endl; 

	//符合框架要求的functor可以bindf
	DemoBindFunctor<double,double,int> dbf;
	// x1=1.5 / x2 
	cout << bindf(dbf,_p1(),1.5)(3) << endl;
	// x1 / x2=1.5
	cout << bindf(dbf,_p2(),1.5)(3) << endl;

	// 使用func_ptr包装函数指针得到一个函数对象wrap_functor符合框架要求可bindf配接
	auto wrap_functor = func_ptr(&demo);
	// 1-3
	cout << bindf(wrap_functor,_p1(),1)(3) << endl;
	// 3-1
	cout << bindf(wrap_functor,_p2(),1)(3) << endl;
	
	//编译器编译期间能完整推导类型信息，但只能有限获取值信息，因此值为模板参数受限
	//const auto dt = DT(DataType::SHORT); //编译不通过，非constexpr
	const auto dt = DataType::SHORT;
	cout << typeid(Type<dt>::TYPE).name() << endl;
	return 0;
}
