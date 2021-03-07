模板类型推导 

```
#声明位置为引用类型时会保留原参数的cv特性
#引用类型函数/数组不会发生decay
#因为cx不能被修改，因此param也必须为const& 否则将违反规则
template<typename T>
void f(T& param);  
const int cx = x
f(cx);                      // T是const int，
                            // param的类型是const int&
#非引用类型，按值传递模板参数T，推导时不保留cv特性，且函数/数组会退化为指针
template<typename T>
void f1(T param);  

#引用是特质的保留，因为指向同一个不能产生不一致的属性
#值关注副本的复制，纯粹的内容副本，特质不收之前的限制
```

auto类型推导与T类型推导不一致的例外

```
#使用一对花括号来初始化一个`auto`类型的变量的时候，推导的类型是`std::intializer_list`，如果这种类型无#法被推导代码会编译错误，对待花括号初始化的行为是`auto`唯一和模板类型推导不一样的地方
auto x1 = 27;                       // 类型时int，值是27
auto x2(27);                        // 同上

auto x3 = { 27 };                   // 类型是std::intializer_list<int>
                                    // 值是{ 27 }
auto x4{ 27 };                      // 同上

auto x5 = { 1, 2, 3.0 };            // 错误！ 不能讲T推导成
                                    // std::intializer_list<T>
                                    
#C++14允许auto表示推导的函数返回值, 以及lambda的参数声明，但这些位置的auto使用了模板的类型推导规则，即不能认识{}
auto createInitList()
{
    return { 1, 2, 3 };             // 编译错误：不能推导出{ 1, 2, 3 }的类型
} 	

std::vector<int> v;
auto resetV = 
    [&v](const auto& newValue) { v = newValue; }    // C++14
resetV({ 1, 2, 3 });                // 编译错误，不能推导出{ 1, 2, 3 }的类型


```

auto & decltype(auto)区别

```
# C++14支持decltype(auto)，它的行为就像auto,从初始化操作来推导类型，但是它推导类型时使用decltype的规则(完全保留原来的特性的需求)
	Widget w;
    const Widget& cw = w;
    
    auto myWidget1 = cw;                     // auto type deduction
                                             // myWidget1's type is Widget 
    decltype(auto) myWidget2 = cw            // decltype type deduction:
                                             // myWidget2's type is
                                             //  const Widget&
```

{}初始化

```
#只要有可能，他会优先匹配std::initializer_list构造函数
#对象没有std::initializer_list构造函数，{}初始化调用其它匹配函数，此时它不同于()是阻止内置类型的收缩转换，以及能避免()可能被解析为一个函数声明!!!
```

const 成员函数理论上是不修改对象状态的，因此考虑并保证const成员函数的线程安全

incomplete type  只声明未定义，编译时定义没有被编译为器看到

item 22 pimpl 在实现文件中定义特殊函数的实现，在.h仅声明

std::move和std::forward

```
#move输入参数为左值时T为 Type&,param 类型为Type& ;输入参数为右值时，T为Type, param类型为Type&&
#move 统一转换为右值引用类型
template<typename T>
typename remove_reference<T>::type&&
move(T&& param)
{
	using ReturnType = 						//alias declaration;
	typename remove_reference<T>::type&&;//see Item 9
	return static_cast<ReturnType>(param);
}

template<typename T>				//C++14; still in
decltype(auto) move(T && param)	//namespace std
{
	using ReturnType = remove_reference_t<T>&&;
	return static_cast<ReturnType>(param);
}

#左值引用，T为Type& ，T&& 为Type& && -> Type&
#右值引用，T为Type, 返回Type&& 
template <class T>
T&& forward(typename std::remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template <class T>
T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
    return static_cast<T&&>(t);
}
#在右值引用上使用std::move 在通用引用上使用std::forward
```

引用折叠

```
# 当param为T&&通用引用时
# 传递的实参时左值是T为 Type&
# 传递的实参为右值时T为 Type
template<typename T>
void func(T&& param);

#引用折叠会出现在4中上下文：模板实例化，auto类型生成，typedef和类型别名声明的创建和使用，decltype
```

避免对universal引用进行重载

```
class Person {
public:
    template<typename T>                    
    explicit Person(T&& n)            // 完美转发构造函数
    : name(std::forward<T>(n)) {}
    
    explicit Person(int idx); 
    Person(const Person& rhs);      // 拷贝构造函数
                                    // (编译器产生的)
    Person(Person&& rhs);           // move构造函数
                                    // (编译器产生的)
}
# 模板化的构造函数不能阻止编译期生成 copy和move构造函数
# 但是重载规则下，完美转发构造函数可能实例化出更精确匹配的函数，会劫持拷贝构造函数和move构造函数

e.g. 用一个非const左值（p）初始化完美转发构造函数
 explicit Person(Person& n)              // 从完美转发构造函数
    : name(std::forward<Person&>(n)) {}  // 实例化出来的构造函数
对于非const左值，此实例化函数比 Person(const Person& rhs)更加匹配，因此被调用

#因此避免对universal引用參数进行重载，universal引用參数是最贪婪的函数，它能实例化出大多数不论什么类型參数的准确匹配

#必须对universal引用參数进行重载时，为精确匹配可使用type tag / enable_if
#type tag
template<typename T>
void fooImpl(T&& t, std::false_type)
{
    cout << "fooImpl(T&& t)" << endl;
}

void fooImpl(float t, std::true_type)
{
    cout << "fooImpl(float t)" << endl;
}

#enbale_if 条件屏蔽模板函数
template<typename T, typename = std::enable_if_t<
    !std::is_floating_point<
    std::remove_reference_t<T>
    >::value>
>
void foo(T&& t)
{
    cout << "foo(T&& t)" << endl;
}

void foo(float t)
{
    cout << "foo(float t)" << endl;
}
```

`noexcept`声明 标准库某些容器为了保证异常安全性，因此当移动操作未声明noexcept时仍然复制

完美转发失败的情况

```
#完美转发借助T&&引用, 引用本质上是指针，因此无法取地址的情况不行
- 非const引用不得绑定到位域
- static const成员变量
	
# 模板型别推导失败，或推导结果是错误的型别
```

lambda

```
# 引用捕获，若lambda 闭包超过了捕获的局部变量的生命周期（例如作为函数返回值），则闭包中的引用会悬挂，局部变量已经销毁，而闭包引用还生存
# 值捕获，若捕获了指针，会存在相同问题

# c++ 14支持初始化捕获, 下例使用初始化捕获将对象移动到了闭包中
# ""=" 左边的作用域是在闭包类内，而"="右边的作用域和lambda被定义的地方的作用域相同
#在闭包中创建一个成员变量pw，然后用——对局部变量pw使用std::move的——结果初始化那个成员变量
auto pw = std::make_unique<Widget>();  //创建Widget
auto func = [pw = std::move(pw)]  // 以std::move(pw)来初始化闭包中成员变量pw
            { return pw->isValidated() && pw->isArchived(); }  
            
# c++11 可以使用std::bind等方法达到类似效果
std::vector<double> data;        // 如前
auto func =               // 引用捕获的C++11模仿物
    std::bind(
      [](const std::vector<double>& data)     // 代码关键部分！
      { /* uses of data */ },
      std::move(data);              // 代码关键部分！
   );
# std::move(data) ->移动构造一个对象data' ->data' 传递给lambda对象参数const std::vector<double>& data 
```

泛型lambda

```

auto f = [](auto&& param) {
     return func(normalize(std::forward<decltype(param)>(param)));
     };
     
auto f =
   [](auto&&... params) {
    return func(normalize(std::forward<decltype(param)>(params)...));
   };
   
# 无论auto&& param 推导为左值引用 / 右值引用都为左值，但decltype(param)结果不同

template<typename T>    
T&& forward(remove_reference_t<T>& param)
{
    return static_cast<T&&>(param);
}

# 如果把一个左值传递给通用引用，通用引用的类型会变为左值引用；如果把一个右值传递给通用引用，通用引用会变为一个右值引用 => 因此decltype(param)左值为Type&, 右值为Type&&
# Type& && -> Type&
# Type&& && -> Type&& 
# 因此实现完美转发
```

volatile

```
提示编译器 这个值可能会在当前线程外部被改变
编译器对访问该变量的代码就不再进行优化,从而可以提供对特殊地址的稳定访问，系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据

volatile int i=10;
int a = i;
// ...
int b = i;
# 若优化i读取一次到寄存器，下次直接从寄存器赋值给b, 不优化直接从内存读
常用的地方:
1) 中断服务程序中修改的供其它程序检测的变量需要加 volatile；
2) 多任务环境下各任务间共享的标志应该加 volatile；
3) 存储器映射的硬件寄存器通常也要加 volatile 说明，因为每次对它的读写都可能由不同意义

硬件常见优化
	乱序执行
	指令重排
	cache缓存
	
Memory修改描述符告知GCC:
	1）不要将该段内嵌汇编指令与前面的指令重新排序；也就是在执行内嵌汇编代码之前，它前面的指令都执行完毕
	2）不要将变量缓存到寄存器，因为这段代码可能会用到内存变量，而这些内存变量会以不可预知的方式发生改变，因此GCC插入必要的代码先将缓存到寄存器的变量值写回内存，如果后面又访问这些变量，需要重新访问内存;
	如果汇编指令修改了内存，但是GCC 本身却察觉不到，因为在输出部分没有描述，此时就需要在修改描述部分增加“memory”，告诉GCC 内存已经被修改，GCC 得知这个信息后，就会在这段指令之前，插入必要的指令将前面因为优化Cache 到寄存器中的变量值先写回内存，如果以后又要使用这些变量再重新读取
	"volatile”也可以达到这个目的，但是我们在每个变量前增加该关键字，不如使用“memory”方便
```

