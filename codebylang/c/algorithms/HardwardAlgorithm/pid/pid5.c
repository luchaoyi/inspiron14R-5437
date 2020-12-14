/*
 * 
 http://wenku.baidu.com/link?url=HhMNQmEF6OsIyr-qzd4Lz7k4yfABZurdjt50VyfPeD4fbs4e6eaLRpiwNPpIOXN09zGZSPCPAwSNcNbqmIIBaX7P24XOlOAs2-XMvxHuoru
 *变积分：变换Ki系数 ki=ki*proportion
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
} pid;


void pid_init();
float pid_realize(float Rt);

float execute(float Ut);


    
float execute(float Ut)
{;}


    
void pid_init()
{
    
    printf("pid init!\n");

    
    pid.Kp=0.4;
    pid.Ki=0.2;
    pid.Kd=0.2;


    pid.Et=0;
    pid.Et_1=0;
    pid.Rt=0;
    pid.Yt=0;


    pid.Ut=0;

    pid.integral=0;
    printf("pid init end\n");
}



float pid_realize(Rt)
{
    int proportion;

    pid.Rt = Rt;
    pid.Et=pid.Rt-pid.Yt;
    
    if(abs(pid.Et)>200)
    	proportion=0; 
    else if(abs(pid.Et)<180)
    	{
    		proportion=1;
    		pid.integral+=pid.Et;
    	}
    else
    	{
    		proportion=(200-abs(pid.Et))/20;
    	}
       
    pid.Ut = pid.Kp*pid.Et+proportion*pid.Ki*pid.integral+pid.Kd*(pid.Et-pid.Et_1);
    pid.Et_1=pid.Et;
    

    //Ut-->execute-->Yt
    pid.Yt=execute(pid.Ut);

    return pid.Yt;

}
 



