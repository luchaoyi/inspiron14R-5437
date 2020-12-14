#include<iostream>
using namespace std;

// 利用crtp实现对象个数统计
template <typename CountedType>
class ObjectCounter {
private:
	static size_t count;
protected:
	ObjectCounter() {
		++ObjectCounter<CountedType>::count;
	}

	ObjectCounter(ObjectCounter<CountedType> const &) {
		++ObjectCounter<CountedType>::count;
	}
	~ObjectCounter() {
		--ObjectCounter<CountedType>::count;
	}
public:
	static size_t live() {
		return ObjectCounter<CountedType>::count;
	}
};

// 统计类生成的对象个数
template <typename CountedType>
size_t ObjectCounter<CountedType>::count = 0;


template <typename T> 
class TObject : public ObjectCounter<TObject<T>>{
};


class Object:public ObjectCounter<Object> {

};

int main() {
	TObject<char> c0ob;
	TObject<char> c1ob;
	TObject<int> iob;
	Object ob;
	cout << c0ob.live() << endl;
	cout << iob.live() << endl;
	cout << ob.live() << endl;
	return 0;
}
