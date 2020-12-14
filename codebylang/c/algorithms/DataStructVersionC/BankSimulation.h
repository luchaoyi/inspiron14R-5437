

//离散事件模拟,事件驱动

typedef struct {
	int OccurTime;
	int Ntype;
}Event,ElemType;

typedef LinkList EventList;

//每一个客户的下面的两个属性是随机的
typedef struct
{
	int ArrivalTime;
	int Duration;
}QElemType;

EventList ev;
Event en;
LinkQueue q[5];
QElemType customer;
int TotalTime,CustomerNum;   //CustomerNum/TotalTime=客户平均逗留时间

//

void OpenForDay(){
	//初始化
	TotalTime=0;
	CustomerNum=0;

	en.OccurTime=0; //假设第一个顾客进门时间为0
	en.NType=0;  //假设第一个时间为客户到达

	//
	OrderInsert(ev,en,cmp);//按时间顺序排序,产生顺序与发生时间不一致
	for(i=1;i<=4;i++) InitQuene(q[i]);
}

//到达事件
void CustomerArrived()
{
	++CustomerNum;
	//此客户到达时产生下一个客户到达时间的间隔
	Random(durtime,intertime);
	t=en.OccurTime+intertime;

	if(t<CloseTime)
		OrderInsert(ev(t,0),cmp);
	i=Minimum(q);
	EnQuene(q[i],(en.OccurTime,durtime));
	if(QueueLength(q[i]) == 1)
		OrderInsert(ev,(en.OccurTime+durtime,i),cmp);

}

//事件列表得到事件->驱动事件处理->处理引发新事件加入事件列表.循环往复交替进行
void CustomerDeparture()
{
	i=en.NType();
	DelQuene(q[i],customer);
	//离开统计时间
	TotalTime+=en.OccurTime-customer.ArrivalTime;

	if(!QueneEmpty(q[i])){
		GetHead(q[i],customer);
		OrderInsert(ev,(en.OccurTime+customer.Duration,i),(*cmp)());
	}	
}

void Bank_Simulation(int CloseTime){
	OpenForDay();

	while(!ListEmpty(ev))
	{
		en=DelFirst(ev);//从时间优先顺序队列删除最先发生的事件
		if(en.Ntype == 0)
			CustomerArrived();
		else
			CustomerDeparture();
	}
}
