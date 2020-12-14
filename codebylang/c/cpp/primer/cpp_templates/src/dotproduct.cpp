#include<iostream>
using namespace std;

// Dot(a,b) 
template<int N, typename T>
class Dot {
public:
	static T result (T* a,T* b) {
		return *a * *b + Dot<N-1,T>::result(a+1,b+1);
	}
};

template<typename T>
class Dot<1,T> {
public:
	static T result (T* a,T* b) {
		return *a * *b;
	}
};

int main() {
	int a[3] = {1,2,3};
	int b[3] = {4,5,6};
	cout << Dot<3,int>::result(a,b) << endl;;
return 0;
}
