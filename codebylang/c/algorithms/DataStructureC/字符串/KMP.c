


char* GetNext(string T,int* next)
 {
     int i=0;//ǰ׺
     int j=1;//��׺

     next[1]=0;

     while(j<T[0]))
     {
         if(0==i||T[i]==T[j])//i=0�տ�ʼ����һλ
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
    while()//�ַ���β
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
    if()//���һ��Ԫ��
    {
        return i-T[0];//��ʼλ�� i-�ַ�����
    }
    else
    {
        return 0;
    }

}

