#include<iostream>

using namespace std;


class Horse
{
	public:
		void Gallop(){cout<<"Galloping..."<<endl;}
		virtual void Fly(){cout<<"Horse can't fly"<<endl;}
	private:
		int itsAge;
};

class Pegasus:public Horse
{
	public:
		void Fly(){cout<<"I can Fly!..."<<endl;}
};

const int NumberHorse=5;

int main()
{
	Horse *Ranch[NumberHorse];
	Horse *pHorse;
	int choice,i;
	for(i=0;i<NumberHorse;i++)
	{
		cout<<"(1)Horse (2)Pegasus:";
		cin>>choice;
		if(choice==2)
		{
			pHorse=new Pegasus;
		}
		else
		{
			pHorse=new Horse;
		}
		Ranch[i]=pHorse;
	}


	for(i=0;i<NumberHorse;i++)
	{
		//RTTI向下类型转换，转换时判断被转换指针的类型与转换类型是否是祖父-子孙关系满足向下
		Pegasus* pPeg= dynamic_cast<Pegasus *>(Ranch[i]);
		//c++提供多种类型转换，及为转换添加了约束条件，相比c语言更加保证安全
		//强制转换相对简单粗暴
		if (pPeg!=NULL) 
			pPeg->Fly();
		else 
			Ranch[i]->Fly();
	}
}
