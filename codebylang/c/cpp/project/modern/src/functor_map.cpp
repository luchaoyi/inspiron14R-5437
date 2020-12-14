#include<iostream>
#include<map>
#include<string>
using namespace std;


class Functor {
public:
	virtual operator()() {};
	virtual operator()(int a) {};
	virtual operator()(int a,int b) {};
};

class Fa : public Functor{
public:
	virtual operator()(int a) {
		cout << "Fa" << a << endl; 
	}
};

class Fb :public Functor {
public:
	virtual operator()(int a,int b) {
		cout << "Fb" << a << b << endl; 
	}
};

int main() {
	map<string,Functor*> func_map;
	func_map.insert(std::make_pair(string("Fa"),new Fa));
	func_map.insert(std::make_pair(string("Fb"),new Fb));

	Functor* fb = func_map[string("Fb")];
	(*fb)(1,2);

	Functor* fa = func_map[string("Fa")];
	(*fa)(1);

return 0;
}
