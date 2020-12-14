#include<iostream>
#include<typeinfo>
using namespace std;

class NullType {};
template<typename T, typename U>
struct TypeList {
	typedef T Head;
	typedef U Tail;
};

// 以NullType结尾,以嵌套形成List
#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1,TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1,TYPELIST_3(T2, T3, T4)>

/*
 TypeList<T1,TypeList<T2,TypeList<T3,TypeList<T4,NullType>>>>
 */
typedef TYPELIST_4(int,float,long,double) TypePacks;


//计算长度
template<typename TList> struct Length;

template<>
struct Length<NullType> {
	enum {value = 0}; 
};

template<typename T, typename U>
struct Length<TypeList<T,U>> {
	enum {value = 1 + Length<U>::value}; 
};

//索引访问
template<typename TList, unsigned index> struct TypeAt;

template<unsigned index>
struct TypeAt<NullType, index> {
	//越界返回NullType
	typedef NullType Result;
};

template<typename T, typename U>
struct TypeAt<TypeList<T,U>, 0> {
	typedef T Result;
};

template<typename T, typename U, unsigned index>
struct TypeAt<TypeList<T,U>, index> {
	typedef typename TypeAt<U, index-1>::Result Result;
};

// 查找类型T，返回下标，没找到-1
template<typename TList, class T> struct IndexOf;

//边界,查找不到
template<typename T>
struct IndexOf<NullType, T> {
	enum {value = -1}; 
};

// 匹配 Head is T
template<typename T, typename Tail>
struct IndexOf<TypeList<T, Tail>, T> {
	enum {value = 0}; 
};

// 不匹配 
template<typename Head, typename Tail, typename T>
struct IndexOf<TypeList<Head, Tail>, T> {
private:
	// < 0表示-1，遇到边界，一路返回
	enum {temp = IndexOf<Tail, T>::value};
public:
	// < 0表示-1，遇到边界，一路返回
	enum {value = temp < 0? -1 : temp + 1};
};

// 添加T到尾部
template<typename TList, class T> struct Append;

//边界
template<typename T>
struct Append<NullType, T> {
	typedef TypeList<T, NullType> Result; 
};

template<typename Head, typename Tail, typename T>
struct Append <TypeList<Head,Tail>, T> {
	typedef TypeList<Head,
			typename Append<Tail, T>::Result> Result;
};

// 删除
template<typename TList, class T> struct Erase;
//边界
template<typename T>
struct Erase<NullType, T> {
	typedef NullType Result; 
};
// 匹配 Head is T
template<typename T, typename Tail>
struct Erase<TypeList<T, Tail>, T> {
	typedef Tail Result; //移除一个
	//typedef typename Erase<Tail, T>::Result Result; //移除所有
};
//不匹配
template<typename Head, typename Tail, typename T>
struct Erase<TypeList<Head,Tail>, T> {
	typedef TypeList<Head,
			typename Erase<Tail, T>::Result> Result;
};

// NoDup 移除重复值保留一个
template<typename TList> struct NoDup;

template<>
struct NoDup<NullType> {
	typedef NullType Result;
};

template<typename Head, typename Tail>
struct NoDup<TypeList<Head,Tail>> { 
	typedef typename NoDup<Tail>::Result L1;
	typedef typename Erase<L1, Head>::Result L2; 
public:
	typedef TypeList<Head, L2> Result;
};


// Replace T->U
template<typename TList, class T, class U> struct Replace;

//边界
template<typename T,typename U>
struct Replace<NullType, T, U> {
	typedef NullType Result; 
};

// 匹配 Head is T
template<typename T, typename Tail, typename U>
struct Replace <TypeList<T, Tail>, T, U> {
	// typedef TypeList<U, Tail> Result; //替换一个
	typedef typename Replace<TypeList<U, Tail>, T, U>::Result Result; //Replace all
};

//不匹配
template<typename Head, typename Tail, typename T, typename U>
struct Replace <TypeList<Head,Tail>, T, U> {
	typedef TypeList<Head,
			typename Replace<Tail, T, U>::Result> Result;
};

// 添加T到尾部
template<typename TList> struct Reverse;

//边界
template<> 
struct Reverse <NullType> {
	typedef NullType Result; 
};

template<typename Head, typename Tail>
struct Reverse <TypeList<Head,Tail>> {
	typedef typename Append<
		typename Reverse<Tail>::Result, Head>::Result Result;
};

int main() {
	cout << Length<TypePacks>::value << endl;

	cout << typeid(TypeAt<TypePacks, 2>::Result).name()<< endl;
	cout << typeid(TypeAt<TypePacks, 4>::Result).name()<< endl;

	cout << IndexOf<TypePacks, char>::value << endl;
	cout << IndexOf<TypePacks, double>::value << endl;

	// 添加char类型
	typedef typename Append<TypePacks, char>::Result TypePacks_1; 
	cout << IndexOf<TypePacks_1, char>::value << endl;
	// 删除cahr类型
	typedef typename Erase<TypePacks, char>::Result TypePacks_2; 
	cout << IndexOf<TypePacks_2, char>::value << endl;

	// Append int and dup remove
	typedef typename Append<TypePacks, int>::Result TypePacks_3; 
	cout << Length<TypePacks_3>::value << endl;
	typedef typename NoDup<TypePacks>::Result TypePacks_4; 
	cout << Length<TypePacks_4>::value << endl;

	// Replace float->char 
	typedef typename Replace<TypePacks,float,char>::Result TypePacks_5; 
	cout << IndexOf<TypePacks_5, char>::value << endl;

	typedef typename Reverse<TypePacks>::Result TypePacks_6; 
	cout << IndexOf<TypePacks, double>::value << endl;
	//Reverse 
	cout << IndexOf<TypePacks_6, double>::value << endl;
	return 0;
}
