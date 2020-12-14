#include<stdio.h>




struct _pid{
   float Kp;
   float Ki;
   float Kd; //p，i，d 

   float Et;// error value
   float Et_1;
   float Et_2;


   float Rt; //set value
    float Ut ;// actual value



    float IncrementUt; 
} pid;


void pid_init();
float pid_realize(float Rt);



    


    
void pid_init()
{
    
    printf("pid init!\n");
    
    pid.Kp=0.2;
    pid.Ki=0.015;
    pid.Kd=0.2;


    pid.Et=0;
    pid.Et_1=0;
    pid.Rt=0;
    pid.Ut=0;

    
    pid.IncrementUt=0;

    printf("pid init end\n");
}



float pid_realize(Rt)
{
    pid.Rt = Rt;


    pid.Et=pid.Rt-pid.Yt;

    pid.integral=+=pid.Et;

    pid.IncrementUt = pid.Kp*(pid.Et-pid.Et_1)+pid.Ki*pid.E_k+pid.Kd*(pid.Et-2*pid.Et_1+pid.Et_2);

    pid.Ut+=pid.IncrementUt; //Ut-Ut_1=dotU

    pid.Et_2=pid.Et_1;
    
    pid.Et_1=pid.Et;

    return pid.Ut;
}
 



