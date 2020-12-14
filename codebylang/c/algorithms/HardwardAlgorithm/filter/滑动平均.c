/*
	当主采样周期较短时，子采样次数不能保证
	考虑平均用历史数据平均，建立一个容纳m个数据的滑动窗口
	用窗口中的数据平均
*/

#defien M 10;

int W[M]; //0-9
int SumW=0;
int p;


int g_xout;

//initialize the sliding window
int initSlideWindow()
{
		for(p=0;p<M-1;p++) //0-8  now p=9
			{
				W[p]=SampleAdc();
				SumW+=W[p];
			}
}

//滤波器工作,考虑使用多线程移植调用filter

//slide window use Circular queue
int filter()
{
	int x0;
	if(p==M) p=0;
	
	while(1)
	{
		R[p]=SampleAdc();
		p++;
		SumW+=R[p];
		g_xout=SumW/M;
	}
	
}


/*
	slide Weighting：think about x0-xm  
	different contribution rate for Xm+1;
	
	so ,set different weight for xo-xm;
*/

#defien M 10
#defien SW 55


int W[M]; //0-9
int SumW=0;
int p;

int weight[]={1,2,3,4,5,6,7,8,9,10};//Sn=n(a1+an)/2=10(11)/2=55


int g_xout;

//initialize the sliding window
int initSlideWindow()
{
		for(p=0;p<M-1;p++) //0-8  now p=9
			{
				W[p]=SampleAdc();
				SumW+=weight[p]*W[p];
			}
}

//滤波器工作,考虑使用多线程移植调用filter

//slide window use Circular queue
int filter()
{
	int x0;
	if(p==M) p=0;
	
	while(1)
	{
		R[p]=SampleAdc();
		p++;
		SumW+=weight[p]*W[p];
		g_xout=SumW/SW;
	}
	
}




