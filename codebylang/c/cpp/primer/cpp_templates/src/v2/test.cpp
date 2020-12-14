/*************************************************************************
	> File Name: tag_dispatch.cpp
	> Author: ycl
	> Mail: ycl@163.com 
	> Created Time: Sat Dec  5 22:48:35 2020
 ************************************************************************/

#include<iostream>
#include<utility>
#include<type_traits>
#include<vector>
#include<string>

#include "traits.hpp"

using namespace std;

struct S {
	S() = delete;
	void set();
	void get();
	bool operator< (const S& s);
};

template <typename T1, typename T2>
void foo_core(typename RParam<T1>::Type t1, typename RParam<T2>::Type t2) {}

// foo是foo_core的内联完美转发函数，辅助自动类型推导让用户接口简单化不暴露细节
template <typename T1, typename T2>
inline void foo(T1&& t1, T2&& t2) {
	foo_core<T1, T2>(std::forward<T1>(t1), std::forward<T2>(t2));
}

int main() {
	// 泛型lambada 被c++ 14支持
	auto func = [] (auto a, auto b) {
		return a + b;
	};
	std::cout << "generic lambda: " << func(1.0, 2.0) << "\n";

	// T is char. 没有指定tag tag默认是T匹配的类型
	MatchTest<char>::print();
	MatchTest<bool>::print();
	MatchTest<double>::print();
	print<int>();

	std::cout << "Is Bool like? "<<IsContextialBool_v<bool> << "\n";
	std::cout << "Is Bool like? "<<IsContextialBool_v<std::vector<bool>> << "\n";

	std::cout << "Is Same? "<<IsSame_v<int, int> << "\n";

	std::cout << "Plus Result type is "<< typeid(PlusResult_t<int ,double>).name() << "\n";
	std::cout << "Plus Result type is "<< typeid(PlusResult_t<char ,int>).name() << "\n";


	std::cout << "Is Default Construct? "<< IsDefaultConstructible_v<int> << "\n";
	std::cout << "Is Default Construct? "<< IsDefaultConstructible_v<S> << "\n";

	std::cout << "Is Convertible? " << IsConvertible<int, int>::value << "\n";
	std::cout << "Is Convertible? " << IsConvertible<int, std::string>::value << "\n";
	std::cout << "Is Convertible? " << IsConvertible<char const*, std::string>::value << "\n";
	std::cout << "Is Convertible? " << IsConvertible<std::string, char const*>::value << "\n";

	std::cout << "Has Func get,set,< ? " << HasVariousFunc_v<S> << "\n";

	Tuple<int, float, std::string> t0(1, 2.0, std::string("hello"));
	std::cout << "get<0> " << get<0>(t0) << "\n";
	std::cout << "get<1> " << get<1>(t0) << "\n";
	std::cout << "get<2> " << get<2>(t0) << "\n";

	auto t1 = makeTuple(2, 3.0, "world");
	std::cout << "get<0> " << get<0>(t1) << "\n";
	std::cout << "get<1> " << get<1>(t1) << "\n";
	std::cout << "get<2> " << get<2>(t1) << "\n";

	return 0;
}
