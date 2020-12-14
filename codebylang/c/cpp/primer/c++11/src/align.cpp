#include<iostream>
#include<stdio.h>
using namespace std;

//定义H对齐到32B
struct alignas(32) H{
	char a[33];
	int b;
};

int main() {
	cout << sizeof(H) << endl;
	cout << alignof(H) << endl;
	//char (H::*ptra)[33] = &H::a;
	//int H::*ptrb = &H::b;
	auto ptra = &H::a;
	auto ptrb = &H::b;
	printf("offset a is %d\n",ptra); 
	printf("offset b is %d\n",ptrb); 
	int *a= new int;
	delete a;
	delete a;
	return 0;
}
