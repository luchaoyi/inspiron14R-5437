#include<iostream>
#include<new>

using namespace std;
class C { 
public:
	C() {
		cout<< "C" <<endl;
	}
};

int main() {
	new C(); //malloc and call C::C()
	void *buffer = operator new (sizeof(C)); // malloc
	new(buffer) C(); //placement new object in buffer 
return 0;
}
