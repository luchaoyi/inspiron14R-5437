/*
 * 积分分离:积分作用是消除静差
 * 当偏差太大时消除积分作用
 */
#include<stdio.h>

struct _pid{
   float Kp;
   float Ki;
   float Kd; //p，i，d 

   float Et;// error value
   float Et_1;


    float Rt; //set value
    float Yt ;// actual value



    float integral;
    
    float Ut; 
    
    
    float Umax;
    float Umin;
    
    
} pid;


void pid_init();
float pid_realize(float Rt);

float execute(float Ut);


    
float execute(float Ut)
{;}


    
void pid_init()
{
    
    printf("pid init!\n");

    
    pid.Kp=0.2;
    pid.Ki=0.1;
    pid.Kd=0.2;


    pid.Et=0;
    pid.Et_1=0;
    pid.Rt=0;
    pid.Yt=0;


    pid.Ut=0;
    
    pid.Umax=400;
    pid.Umin=-200;

    pid.integral=0;
    printf("pid init end\n");
}



float pid_realize(Rt)
{
    int flag;

    pid.Rt = Rt;
    pid.Et=pid.Rt-pid.Yt;
    
    //Ut-->execute-->Yt Yt达到了阈值
    if(pid.Yt>pid.Umax)
    {
    	if(abs(pid.Et>200)
    	{
    		flag =0 ;
    	}
    	else
    	{
    		flag=1
    		if(pid.Et<0)
    			pid.intergral+=pid.Et;
    		//else Et>0 正向饱和 only累加 负偏差
    	}
    	
    }
    
    else if(pid.Yt<pid.Umin)
    {
    	if(abs(pid.Et>200)
    	{
    		flag =0 ;
    	}
    	else
    	{
    		flag=1
    		if(pid.Et>0)
    			pid.intergral+=pid.Et;
    		//else Et>0 负向饱和 only累加 正偏差
    	}
    }
    else
    {
			if(abs(pid.Et>200)
			{
					flag =0;
			}
			else
			{
					flag=1;
					pid.intergral+=pid.Et;
			}
    }
 

    pid.Ut = pid.Kp*pid.Et+flag*pid.Ki*pid.integral+pid.Kd*(pid.Et-pid.Et_1);
    pid.Et_1=pid.Et;
    

    //Ut-->execute-->Yt
    pid.Yt=execute(pid.Ut);

    return pid.Yt;

}
 



