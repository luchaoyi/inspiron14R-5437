/*http://wenku.baidu.com/link?url=Jp2mEWAXGgwj6FQXVJ1P84CoNnsTpZUUsQgMFx5g9x-jRRWMghayJFLmV9heU9nea6dtzgJZ-9AjIzVh-dkLPeLp7ClZwosiymvuWSe16pK*/
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
    pid.Ki=0.015;
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
    pid.Rt = Rt;


    pid.Et=pid.Rt-pid.Yt;
    pid.integral=+=pid.Et;

    pid.Ut = pid.Kp*pid.Et+pid.Ki*pid.integral+pid.Kd*(pid.Et-pid.Et_1);
    pid.Et_1=pid.Et;
    

    //Ut-->execute-->Yt
    pid.Yt=execute(pid.Ut);

    return pid.Yt;
}
 



