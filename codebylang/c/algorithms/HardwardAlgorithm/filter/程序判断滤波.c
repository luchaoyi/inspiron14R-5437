/*
	核心思想:相邻采样值变化范围有合理范围
	若超过限度则认定采样不可信,考虑用前一个数据代替
	
	
	算法关键是确定合理周期和最大变化值
	
	
*/

#define D 10 //The reasonable scope

int x0;

int filter()
{
	int x1;
	
	new=SampleAdc();//Sampling get new value;
	
	if((x1-x0>D)||(x0-x1)>D)
		x1=x0;
	x0=x1;
	
	return x1;
}
/*
	线性预测：改进上一个 当检测物理量处于明显变化阶段，采样变化大，
	所以用算法1误差较大采用线性预测法
	假定当前趋势和前依次趋势相同 则 x2-x1=x1-x0;
*/


#define D 10 //The reasonable scope

#define MAX 4095
#define MIN 0

int x1; //The first two times
int x0;

int filter()
{
	int x2;
	
	x2=SampleAdc();//Sampling get new value;
	
	if((x2-x1>D)||(x1-x2)>D)
			x2=2*x1-x0;	
			
			//Cross border judgment
			
			if(x2>MAX) x2=MAX;
			if(x2<MIN) x2=MIN;
			
	x0=x1;
	x1=x2;
	
	return x2;
}