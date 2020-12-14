#include<iostream>
#include <functional>
int main() {
	int w = 10;
	std::function<int(int)> add_w = [w](int x) {
			return w + x;
		};
	std::cout << add_w(10) << std::endl;

	auto func = [w](int x,int y) -> float {
		return x+y+w+0.5;
	};

	std::cout << func(3,4) << std::endl;
	return 0;
}
