#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include<atomic>

using namespace std;

void func(std::atomic<int>& counter){
	for(int i=0;i<100;i++)
		++counter;
}

int main(){
	std::atomic<int> counter(0);

	std::vector<std::thread> threads;
	for(int i=0;i<4;i++){
		threads.push_back(std::thread{func,std::ref(counter)}); //线程启动默认按值传递参数，std:ref按引用传递

	}

	for(auto& t:threads){
		t.join();
	}

	std::cout << "Result = " << counter << std::endl;
}

