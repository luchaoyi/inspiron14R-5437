/*
	����˼��:���ڲ���ֵ�仯��Χ�к���Χ
	�������޶����϶�����������,������ǰһ�����ݴ���
	
	
	�㷨�ؼ���ȷ���������ں����仯ֵ
	
	
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
	����Ԥ�⣺�Ľ���һ�� ������������������Ա仯�׶Σ������仯��
	�������㷨1���ϴ��������Ԥ�ⷨ
	�ٶ���ǰ���ƺ�ǰ����������ͬ �� x2-x1=x1-x0;
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