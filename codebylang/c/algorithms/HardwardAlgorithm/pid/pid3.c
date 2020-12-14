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
    pid.Ki=0.04;
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
    int flag=1;

    pid.Rt = Rt;
    pid.Et=pid.Rt-pid.Yt;
    
    if(abs(pid.Et)<=200))
           pid.integral+=pid.Et;
           
    else
        flag=0;

    pid.Ut = pid.Kp*pid.Et+flag*pid.Ki*pid.integral+pid.Kd*(pid.Et-pid.Et_1);
    pid.Et_1=pid.Et;
    

    //Ut-->execute-->Yt
    pid.Yt=execute(pid.Ut);

    return pid.Yt;

}
 



