#include<stdio.h>


/*int fib(int n)
{
    if (n<2)
        return n==0? 0:1;
    return fib(n-1)+fib(n-2);
}

int main()
{
    int i;
    for(i=0;i<=40;i++)
        printf("%d ",fib(i));
}
*/

int main()
{
    int i;
    int a[40];

    a[0] = 0;
    a[1] = 1;
    printf("%d %d ", a[0], a[1]);

    for( i=2; i < 40; i++ )
    {
        a[i] = a[i-1] + a[i-2];
        printf("%d ", a[i]);
    }

    return 0;
}

