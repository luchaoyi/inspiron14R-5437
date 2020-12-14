#include<iostream>
#include<utility>
#include<typeinfo>
using namespace std;

template<typename ReturnType, typename... Args>
class Functor {
	public:
		ReturnType operator()(Args&&... args) {	
			return exec(std::forward<Args>(args)...);
		}
	private:
		ReturnType exec();
		template<typename T0>
		ReturnType exec(T0 t) {}
		template<typename T0,typename T1>
		ReturnType exec(T0 t0,T1 t1) {
			cout << 2 << endl;
			return true;
		}
};


/*
//三段
template<typename... Args>
class SUB;

template<typename T, typename... Args>
class SUB<T, Args...> : public T, public SUB<Args...> {

};

template<typename T>
class SUB<T> : public T {

};
*/

template<typename T, typename... Args>
class Factory : public T, public Factory<Args...> {};

template<typename T>
class Factory<T> : public T {};

struct Object0{
	void createObject0() {
		cout << "O0" <<endl;
	}
};
struct Object1{
	void createObject1() {
		cout << "O1" <<endl;
	}
};
struct Object2{
	void createObject2() {
		cout << "O2" <<endl;
	}
};

int main() {
	Functor<bool,int,float>()(1,2.5);
	Factory<Object0,Object1,Object2> factory;
	cout << typeid(factory).name() << endl;
	factory.createObject0();
	factory.createObject1();
	factory.createObject2();
	return 0;
}
