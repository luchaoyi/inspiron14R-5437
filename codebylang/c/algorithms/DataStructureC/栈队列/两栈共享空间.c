
Struct Stack
{
    DataType data[MAX_SIZE];

    int top1,top2
}*pStack;

InitStack(pStack S)
{
    S->top=-1;
    S-top=MAX_SIZE-1;
}

//�����趨�ź����������Ǹ�ջ���в���
DataType Pop(pStack S,int i)
{
    if(i==1)
    {
        if
            x=S->data[S->top--]

    }

    if(i==2)
    {
        if
            x=S->data[S->top++];

    }
    return x;

}

void Push(pStack S,int i)
{
      if(S->top1==S->top2)
    {
        ///����
        exit(-1);
    }

    ///i=1
    S->[++S->top1]=x;
    ///i=2
    S->[--S->top2]=x

}
