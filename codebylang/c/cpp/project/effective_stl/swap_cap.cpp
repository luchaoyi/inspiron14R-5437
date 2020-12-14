#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
	vector<int> v{1,2,1,2,1,2};
	cout << "size "<< v.size() << "," << "capacity " << v.capacity() << endl;
	
	//remove不改变size
	remove(v.begin(), v.end(), 2);
	cout << "size "<< v.size() << "," << "capacity " << v.capacity() << endl;
	for_each(v.begin(), v.end(), [](int x){
			cout << x << endl;
			});
	
	//v.erase没有改变容量
	v.erase(remove(v.begin(), v.end(), 2), v.end());
	cout << "size "<< v.size() << "," << "capacity " << v.capacity() << endl;
	for_each(v.begin(), v.end(), [](int x){
			cout << x << endl;
			});
	
	//swap 利用v创建临时对象并swap
	vector<int>(v).swap(v);
	cout << "size "<< v.size() << "," << "capacity " << v.capacity() << endl;
	
	//swap清除,v is empty
	vector<int>().swap(v);
	cout << "size "<< v.size() << "," << "capacity " << v.capacity() << endl;

	return 0;
}
