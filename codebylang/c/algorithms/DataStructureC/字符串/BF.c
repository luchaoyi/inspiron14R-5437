    #include<stdio.h>

int BF(char S[],char T[])
{
    int i=0,j=0;
    int index=0;

    printf("%s\n%s\n",S,T);

    while((S[i]!='\0')&&(T[j]!='\0'))
    {
        if(S[i]==T[j])
        {
            i++;
            j++;
        }
        else
        {
            j=0;
            i=++index;
        }

    }

    if(T[j]=='\0')
        return index;
    else
        return -1;
}

int main()
{
    int flag=0;

    char S[10];
    char T[5];

    scanf("%s%s",S,T);

    flag=BF(S,T);

    printf("%d\n",flag);
}
