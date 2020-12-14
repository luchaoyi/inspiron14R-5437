


char* GetNext(string T,int* next)
 {
     int i=0;//前缀
     int j=1;//后缀

     next[1]=0;

     while(j<T[0]))
     {
         if(0==i||T[i]==T[j])//i=0刚开始后移一位
         {
             i++;
             j++;
             if(T[i]!=T[j])
             {
                 next[j]=i;

             }
             else
             {
                 next[i]=next[j];
             }
         }
         else
        {

            i=next[i];

         }

     }
 }

int kmp(string s,string t,int *next)
{
    while()//字符串尾
    {
        if(0==j||oS[i]==T[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[i];
        }
    }
    if()//最后一个元素
    {
        return i-T[0];//起始位置 i-字符长度
    }
    else
    {
        return 0;
    }

}

