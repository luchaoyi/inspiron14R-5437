#include<mutex>
#include<condition_variable>
#include<queue>
#include <future>
#include <iostream>

using namespace std;

class thread_queue {

	void push(int value) {
		lock_guard<mutex> lk(mut);
		q.push(value);
		cond.notify_one();
	}

	int pop() {
		unique_lock<mutex> lk(mut);
		int value = q.front();
		cond.wait(lk,[this](){return !q.empty();});
		q.pop();
		return value;
	}

	bool empty() {
		lock_guard<mutex> lk(mut);
		return q.empty();
	}

private:
	mutex mut;
	condition_variable cond;
	queue<int> q;
};

// P&V
class Semp {
public:
	Semp(int capcity) : state(0) , capcity(capcity){}
	void acquire() {
		unique_lock<mutex> lk(mut);
		state++; 
		cond_var.wait(lk, [&]{return state <= capcity;});
	}

	void release() {
		lock_guard<mutex> lk(mut);
		state--;
		cond_var.notify_all();
	}
private:
	int state;
	int capcity;
	mutex mut;
	condition_variable cond_var;
};

int main() {
	Semp sem(2);
	sem.acquire();
	sem.acquire();
	cout << "---" << endl;
	cout << "---" << endl;
	sem.release();
	sem.release();
}

