
#define MAX_SIZE 13;


void Fibnacci(int F[],int n)//���и���
{
    int i=2;
    F[0]=1;
    F[1]=1;

    while(i<=n-1)
    {
        F[i]=F[i-1]+F[i-2];
    }
}


int FibnacciSearch(int r[],int n,int key)
{
    int mid;

    int low=1;
    int high=n-1;

    int k=0;
    F[MAX_SIZE];
    Fibnacci(F,MAX_SIZE);


    //��F(k)-1
    while(n>F[K]-1)
    {
        K++;
    }

    //����n<F[K]-1ʱ�貹�룬ȫ�����λ
     for (int i = n; i < F[k] - 1; i++)
    {

        r[i] = r[high];
    }


    while(low<=high)
    {
        mid = low + F[k - 1] - 1;
        if(r[mid]>key)
        {
            high=mid-1;
            k=k-1;
        }
        else if(r[mid]<key))
        {
            low=mid+1;
            k=k-2;
        }
        else
        {
            if(low<=high)//���ǵ�high��������Ԫ��
             return mid;
            else
            return n;
        }


    }
    return 0;
}
