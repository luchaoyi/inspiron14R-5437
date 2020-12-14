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

using namespace std;

// ------------------19--------------
/*
 *转换traits 增加/去除类型修饰或类型变换，如Decay
 * */
template <typename T>
struct RemoveRef {
	using Type = T;
};

template <typename T>
struct RemoveRef<T&> {
	using Type = T;
};

template <typename T>
struct RemoveRef<T&&> {
	using Type = T;
};

// suffix_t
template <typename T>
using RemoveRef_t = typename RemoveRef<T>::Type;

/*
 * 断言traits, Is*
 * */
template <bool val>
struct BoolConstant{
	using Type = BoolConstant<val>;
	static constexpr bool value = val;
};

struct TrueType : public BoolConstant<true> {};
struct FalseType : public BoolConstant<false> {};

template <typename T1, typename T2>
struct IsSameType :FalseType {};

template <typename T>
struct IsSameType<T, T> : TrueType {};

// suffix_v 
// 变量模板c++14 support!
template <typename T1, typename T2>
constexpr bool IsSame_v = IsSameType<T1, T2>::value;

// T可隐式转换为bool
template <typename T>
struct IsContextialBoolT {
	template <typename U> struct Identity;
	template <typename U>
		static std::true_type test(Identity<decltype(std::declval<U>()? 0 : 1)>*);
	template <typename U>
		static std::false_type test(...);

	static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
constexpr bool IsContextialBool_v = IsContextialBoolT<T>::value;

// 是否可默认构造
template <typename T>
struct IsDefaultConstructibleT {
	// 如果U不可默认构造则U()表达式失败因此decltype不可能推导出第二个模板参数， 因此会替换失败
	template <typename U, typename = decltype(U())>
		static char test(U *);
	template <typename>
		static long test(...);
	static constexpr bool value = IsSame_v<decltype(test<T>(nullptr)), char>;
};

template <typename T>
constexpr bool IsDefaultConstructible_v = IsDefaultConstructibleT<T>::value;

template <typename... Args>
using VoidT = void;

// 基于模板特化的SFINAE
template <typename, typename = VoidT<>>
struct IsDefaultConstructibleTV2 : public std::false_type{};
template <typename T>
struct IsDefaultConstructibleTV2<T, VoidT<decltype(T())>> : public std::true_type{};

template <typename FROM, typename TO>
struct IsConvertibleHelper {
	template <typename F>
		static std::true_type test(TO);

	template <typename>
		static std::false_type test(...);

	using Type = decltype(test<FROM>(std::declval<FROM>()));
};

template <typename FROM, typename TO>
struct IsConvertible : public IsConvertibleHelper<FROM, TO>::Type {};

/*
 *结果类型推导 T1 op T2 => T
 * */
// 将结果类型推导的负载到了编译器
template <typename T1, typename T2> 
struct PlusResultT {
	using Type = decltype(std::declval<T1>() + std::declval<T2>());
	// 在仅需要类型计算的表达式位置请使用declval, declval没有实现体一般仅用在sizeof、decltype
	//若不使用declval, 表达式T1（）+ T2（）试图对类型T1和T2的值进行值初始化，这两个类型都必须具有可访问的，未删除的默认构造函数
	// using Type = decltype(T1() + T2());
};

template <typename T1, typename T2> 
using PlusResult_t = typename PlusResultT<T1, T2>::Type;
/*
 *T::member探测
 * */
template <typename T, typename = VoidT<>>
struct HasVariousFunc : public std::false_type {};

// 探测T是否有get, set, operator <方法
// 用VoidT组合多个参数
template <typename T>
struct HasVariousFunc<T, VoidT<
	decltype(std::declval<T>() < std::declval<T>()),
	decltype(std::declval<T>().get()),
	decltype(std::declval<T>().set())>>
: public std::true_type {};

template <typename T>
constexpr bool HasVariousFunc_v = HasVariousFunc<T>::value;

/*
 *是否抛出声明异常， noexcept声明+运算符
 * */
// 移动构造是否抛出异常, 基于noexcpet运算符
/*
// 在T()求值之前先要检查T()是否有效， 若T() = delete 会引发编译错误, 因此增加一个std::void_t
template <typename T>
struct IsMoveNoThrow: public std::bool_constant<noexcept(T(std::declval<T>()))> {};
*/
template <typename T, typename = std::void_t<>>
struct IsMoveNoThrow: public std::false_type {};

template <typename T>
struct IsMoveNoThrow<T, std::void_t<decltype(T(std::declval<T>()))>> : public std::bool_constant<noexcept(T(std::declval<T>()))> {};

/*
 * 类型区分
 * */
// 基本类型
template<typename T>
struct IsFundaT : std::false_type {};

#define MK_FUNDA_TYPE(T)	\
	template<> struct IsFundaT<T> : std::true_type {};

MK_FUNDA_TYPE(nullptr_t)
MK_FUNDA_TYPE(void)
MK_FUNDA_TYPE(char)
MK_FUNDA_TYPE(short)
MK_FUNDA_TYPE(int)
MK_FUNDA_TYPE(long)
MK_FUNDA_TYPE(float)
MK_FUNDA_TYPE(double)
// ...

#undef MK_FUNDA_TYPE

// 简单符合类型，包含指针，数组，引用等
template<typename T>
struct IsPointerT : std::false_type {};

template<typename T>
struct IsPointerT<T*> : std::true_type {};

template<typename T>
struct IsPointerToMemberT : std::false_type {};

template<typename T, typename C>
struct IsPointerToMemberT<T C::*> : std::true_type {
	using MemberT = T;
	using ClassT = C;
};

// class 类型时可以定义函数成员指针的
template<typename T, typename = std::void_t<>>
struct IsClassT : std::false_type {};

template<typename T>
struct IsClassT<T, std::void_t<char T::*>> : std::true_type {};

// 参数按值/按引用传递
template <typename T>
struct RParam {
	using Type
		= typename std::conditional_t<(sizeof(T) <= 2*sizeof(void*)
				&& std::is_trivially_copy_constructible<T>::value
				&& std::is_trivially_move_constructible<T>::value),
		T,
		T const&>::Type;
};

//------------------ 20 -------------------- 
//enable if false时类型不存在，依据替换失败非错误原则typename = EnableIf可以用于根据某些Pred关闭函数/类型模板
template <typename T, bool Pred>
struct EnableIf;

template <typename T>
struct EnableIf<T, true> {
	using Type = T;
};

template <typename T, bool Pred>
using EnableIfT = typename EnableIf<T, Pred>::Type;

template <typename T = void, bool Pred = true>
EnableIfT<T, Pred> print() {
	std::cout << "enable print\n";
	return T{};
}

// 类型匹配tag分派
template<typename... Args>
struct MatchOverload;

// 递归继承加using collect 一组match函数
template<typename T, typename... Args>
struct MatchOverload<T, Args...> : public MatchOverload<Args...>{
	static T match(T);
	using MatchOverload<Args...>::match;
};

// 不匹配返回void类型
template<>
struct MatchOverload<> {
	static void match(...);
};

template <typename T>
T Declval();

template<typename T, typename... Args>
using BestMatchInSet = decltype(MatchOverload<Args...>::match(Declval<T>()));

template <typename T,
		 typename Tag = BestMatchInSet<T, char, bool, double>
		 >
struct MatchTest;

template <typename T>
struct MatchTest<T, char> {
	static void print() {
		std::cout << "char\n";
	}
};

template <typename T>
struct MatchTest<T, bool> {
	static void print() {
		std::cout << "bool\n";
	}
};

template <typename T>
struct MatchTest<T, double> {
	static void print() {
		std::cout << "double\n";
	}
};

// ---------------------21-------
// CRTP
// Facades模型，由基类定义大部分或全部的public接口，而子类仅需要为父类提供少量接口， 这是一种父类回调子类接口的方法
// 此设计模式可以方便新类型实现快速实现已有接口
// 一种父类定义框架，子类实现必要接口的方法, 子类不同于重载虚函数的设计方法 

// 一个迭代器Facades
template <typename Derived, typename Value, typename Category, typename Reference = Value&, typename Distance = std::ptrdiff_t>
struct IteratorFacede {
	using value_type = typename std::remove_const<Value>::type;
	using reference = Reference;
	using pointer = Value*;
	using difference_type = Distance;
	using iterator_category = Category;

	reference operator *() const {}
	pointer operator ->() const {}

	Derived& operator ++() {}
	Derived operator++(int){}
	// ...
};

//Mixins
// 常用面向对象手法 LabelPoint : public Point
template <typename... Mixins>
struct Point : public Mixins... {
		double x,y;
		Point() : Mixins()..., x(0.0), y(0.0) {}
		Point(double x, double y) : Mixins()..., x(x), y(y) {}
};

struct Label {
	std::string label;
	Label() : label("") {}
};

// mixins手法反转了常规的面向对象的继承方向，将Label混入了Point属性，此手法可以在向用户隐藏Point细节下，扩展Point
using LabledPoint = Point<Label>;

/*
CRTP + Mixins
template <template<typename>... Mixins>
struct NewPoint: public Mixins<NewPoint>... {};
*/

//------------- 22 --------------------
/*
  广义FuncPtr没有直接装载 Callable Functor到FuncPtr 
  Functor -> SpecialFuncBridge : FuncBridge ->  FuncPtr

  FuncPtr没有存储具体的Functor类型，不感知它是一个函数指针，functor对象... 它仅知道R 和 Args...
  存储了一个抽象基类FuncBridge<R, Args...>类型的指针， functor 的对象的请求被转发到了此对象
  
  每一个Functor在构造FuncPtr对象时，会产生一个SpecialFuncBridge对象（实现copy and clone），它存储了Functor类型的成员
  FuncPtr()() -> bridge->invoke() -> functor()
  FuncPtr和具体functor通过Bridge对象链接，Bridge对象为FunPtr擦除了Funtor的类型，FuncPtr不感知Functor, 而通过Bridge转发请求
*/

template <typename R, typename... Args> 
struct FuncBridge {
	virtual ~FuncBridge() {} 
	virtual FuncBridge* clone() = 0;
	virtual R invoke(Args...) = 0;
};

// Functor 是被持有的可调用对象
template <typename Functor, typename R, typename... Args> 
struct SpecialFuncBridge : FuncBridge<R, Args...>  {

	template <typename FunctorFwd> 
		SpecialFuncBridge(FunctorFwd&& functor) : functor(std::forward<FunctorFwd>(functor)) {
		}

	R invoke(Args&&... args) {
		return functor(std::forward<Args>(args)...);
	}

	SpecialFuncBridge* clone() {
		return new SpecialFuncBridge(functor);
	}

private:
	Functor functor;
};

template <typename Signature>
struct FuncPtr;

// FuncPtr不知道Functor类型， 类型被FuncBridge擦除
// FuncPtr对Functor的请求都需要通过Bridge转发
// copy 和 () 转发给bridge 的clone 和 invoke
template <typename R, typename... Args> 
struct FuncPtr<R(Args...)> {

	template<typename F>
		FuncPtr(F&& f) : bridge(nullptr){
			using Functor = std::decay_t<F>;
			using Bridge = SpecialFuncBridge<Functor, R, Args...>;
			bridge = new Bridge(std::forward<F>(f));
		}

	FuncPtr (FuncPtr const& other) : bridge (nullptr) {
		if (other.bridge) {
			bridge = other.bridge->clone();
		}
	}

	R operator()(Args&&... args) {
		bridge->invoke(std::forward<Args>(args)...);
	}

	private:
		FuncBridge<R, Args...>* bridge;
};

//------------- 23 --------------------
/* 
 * 模板元编程
 *
 * struct -> std::tuple
 * union -> std::variant
 *
 * 能力:
 * 计算
 * 反射
 * 代码生成
 *
 * 结构：
 * 状态变量：模板参数
 * 循环结构：通过递归实现
 * 执行路径选择：通过条件表达式或者偏特例化实现
 * 整数运算
 */
template <typename T>
struct RemoveAllExtendsT {
	using Type = T;
};

template <typename T, std::size_t SZ>
struct RemoveAllExtendsT<T[SZ]> {
	using Type = typename RemoveAllExtendsT<T>::Type;
};

template <typename T>
struct RemoveAllExtendsT<T[]> {
	using Type = typename RemoveAllExtendsT<T>::Type;
};

//------24------
// TypeList及其元函数
template <typename... Types>
struct TypeList {};

template <typename List>
struct IsEmpty;

template <typename... Types>
struct IsEmpty<TypeList<Types...>> {
	constexpr static bool value = true;
};

template <>
struct IsEmpty<TypeList<>> {
	constexpr static bool value = false;
};

template <typename List>
struct FrontT;

template <typename Head, typename... Tail>
struct FrontT<TypeList<Head, Tail...>> {
	using Type = Head;
};

template <typename List>
using Front = typename FrontT<List>::Type;

template <typename List>
struct PopFrontT;

template <typename Head, typename... Tail>
struct PopFrontT<TypeList<Head, Tail...>> {
	using Type = TypeList<Tail...>;
};

template <typename List>
using PopFront = typename PopFrontT<List>::Type;

template <typename T, typename List>
struct PushFrontT;

template <typename NewType ,typename... Types>
struct PushFrontT<NewType, TypeList<Types...> > {
	using Type = TypeList<NewType, Types...>;
};

// 使用包扩展将类型列表迭代交给编译器
template <typename List, template <typename> class MetaFunc>
struct TransformT;

template <typename... Types, template <typename> class MetaFunc>
struct TransformT<TypeList<Types...>, MetaFunc> {
	using Type = TypeList<typename MetaFunc<Types>::Type...>;
};

template <typename List>
struct LargestType;

template <typename Head, typename... Tail>
struct LargestType<TypeList<Head, Tail...>> {
private:
	constexpr static bool comp = sizeof(Head) > sizeof(LargestType<Tail...>::Type);
public:
	using Type = typename std::conditional_t<comp,
		Head,
		typename LargestType<Tail...>::Type>::Type;
};

template <>
struct LargestType<TypeList<>> {
	using Type = char;
};

template<typename List, typename T, unsigned N = 0, bool Empty = IsEmpty<List>::value>
struct FindIndexOfT;

template<typename List, typename T, unsigned N>
struct FindIndexOfT<List, T, N, false> : 
public std::conditional_t<std::is_same<Front<List>, T>::value,
	   std::integral_constant<unsigned, N>,   // 这里为 FindIndexOfT 添加了 value = N
	   FindIndexOfT<PopFront<List>, T, N + 1>> {
};
template<typename List, typename T, unsigned N>
struct FindIndexOfT<List, T, N, true>  {};

template<typename T, T Value> 
struct CTValue {
	constexpr static T value = Value;
};

// 借助TypeList的编译期数值列表
// CTValue 将编译时常量转换为类型并将值存储期内，存储值的类型可以放入TypeList借助Typelist的力量形成编译期数值list
template <typename T, T... Values>
using CTTypeList = TypeList<CTValue<T, Values>...>;

// ValueList及其元函数
template <typename T, T... Values>
struct ValueList {};

/*
template <typename List>
struct IsEmpty {
	constexpr static bool value = false;
};

template <typename T>
struct IsEmpty<ValueList<T>>{
	constexpr static bool value = true;
};
*/

template <typename List>
struct IsEmpty {};

template <typename T, T... Values>
struct IsEmpty<ValueList<T, Values...>> {
	constexpr static bool value = sizeof...(Values) == 0;
};

template <typename List>
struct FrontV;

template <typename T, T Head, T... Values>
struct FrontV<ValueList<T, Head, Values...>> {
	using Type = CTValue<T, Head>;
	constexpr static T value = Head;
};

// c++17 可推断非类型参数
template<auto Value>
struct CValue {
	constexpr static auto value = Value;
};

// 利于auto 可容纳不同类型 
template<auto... Values>
class AutoValueList {};

int x;
using PeerTupleList = AutoValueList<1 , 'a', &x>;

// ----------------25------------------
// 注意元组是有又typelist的能力的， 可以为它定义MetaFunc使它成为一个typelist
template <typename... Types>
struct Tuple;

template <typename Head, typename... Tail>
struct Tuple<Head, Tail...> {
	Tuple() {}
	// enbale_if 输入参数个数与声明类型不匹配时禁用
	template <typename VHead, typename... VTail, typename = typename std::enable_if_t<sizeof...(VTail) == sizeof...(Tail)>>
		Tuple(VHead&& vhead, VTail&&... vtail) : head(std::forward<VHead>(vhead)) , tail(std::forward<VTail>(vtail)...) {
		}

	Head const& getHead() const {
		return head;
	}

	Head & getHead() {
		return head;
	}

	Tuple<Tail...> const& getTail() const {
		return tail;
	}

	Tuple<Tail...>& getTail() {
		return tail;
	}

private:
	Head head;
	Tuple<Tail...> tail;
};

template<>
struct Tuple<>{};

// Tuple的元函数

template <unsigned N>
struct TupleGet {
	template <typename Head, typename... Tail>
	static auto apply(Tuple<Head, Tail...>const& t) {
		return TupleGet<N-1>::apply(t.getTail());
	}
};

template <>
struct TupleGet<0> {
	template <typename Head, typename... Tail>
	static Head const& apply(Tuple<Head, Tail...>const& t) {
		return t.getHead();
	}
};

template <unsigned N, typename... Types>
auto get(Tuple<Types...> const& t) {
	return TupleGet<N>::apply(t);
}

template <typename... Types>
auto makeTuple(Types&&... args) {
	return Tuple<std::decay_t<Types>...>(std::forward<Types>(args)...);
}

//---------------------26------------------------
//前置声明
template<typename... Types>
struct Varinat;


template<typename... Types>
struct VarinatStorage {
	// 基于TypeList求解出最大尺寸
	using LargestT = LargestType<TypeList<Types...>>;
	alignas(Types...) unsigned char buffer[sizeof(LargestT)];
	unsigned  discriminator = 0;

	size_t maxSize() {
		return sizeof(LargestT);
	}

	template<typename T>
		T* getBufferAs() {
			return std::launder(reinterpret_cast<T*>(buffer));
		}
	template<typename T>
		T const * getBufferAs() const {
			return std::launder(reinterpret_cast<T*>(buffer));
		}
};

// 提供了变量的有效值是（或将是）类型T时在缓冲区上进行操作所需的核心操作
template<typename T, typename... Types>
struct VarinatChoice {
	using Derived  = Varinat<Types...>; 
	Derived& getDrived() {
		return *static_cast<Derived*>(this);
	}
	Derived const& getDrived() const {
		return *static_cast<Derived*>(this);
	}

	// 在Types... 列表中查找指定T的index
	constexpr static unsigned Discriminator = FindIndexOfT<TypeList<Types...>, T>::value + 1;

	VarinatChoice() {}
	VarinatChoice(T const& value) {
		auto&& drived = getDrived();
		drived.discriminator = Discriminator;
		new(drived.buffer) T(value);
	}

	VarinatChoice(T && value) {
		auto&& drived = getDrived();
		drived.discriminator = Discriminator;
		new(drived.buffer) T(std::move(value));
	}

	bool destory() {
		auto&& drived = getDrived();
		if (drived.discriminator == Discriminator) {
			// 调用析构，并不释放内存
			drived.template getBufferAs<T>()->~T();
			return true;
		}
		return false;
	}

	// Derived& operator= (T&& value)
	Derived& operator= (T const& value) {
		auto&& drived = getDrived();
		if (drived.discriminator == Discriminator) {
			*drived.template getBufferAs<T>() = value;
		} else {
			//assign，对于持有资源的不同类型需要对以前的对象析构
			// 下句暂时编译不过
			// drived.destory();
			new (drived.buffer) T(value);
			drived.discriminator = Discriminator;
		}
	}
};

// private VarinatChoice<Types, Types...>... 
// 产生了两层展开 
// 外部展开即在第一个参数位置展开，产生多个VarinatChoice class
// 内部展开是将参数包所有参数收集到第二个模板参数位置
// 因此展开后的一组 VarinatChoice 记录了类型列表和对应类型的index
template<typename... Types>
class Varinat : 
	private VarinatStorage<Types...>, 
	private VarinatChoice<Types, Types...>... 
{
	template<typename T, typename... OtherTypes>
		friend class VarinatChoice;

	// 委托编译期生成各个调用VarinatChoice对应的Varinat构造函数
	using VarinatChoice<Types, Types...>::VarinatChoice...;

	/*
	//当前g++ 17编译失败
	void destory() {
		// call all 
		(void)std::initializer_list<int>{0, (VarinatChoice<Types, Types...>::destory(), 0)...};
		// set 0 指示没有当前没有存储值
		this.discriminator = 0;
	}

	template<typename T> 
		bool is() {
			// 左面是构造或赋值是存储的index , 右边是T在Types...中查询的index 
			return this->discriminator == VarinatChoice<T, Types...>::Discriminator;
		}
*/
	template<typename T> 
		T& get() {
			return *this.template getBufferAs<T>();
		}
};

// 变参下标
template<std::size_t... Idx, typename C>
void printElemes(C const& col) {
	// col[Idx]...
}
