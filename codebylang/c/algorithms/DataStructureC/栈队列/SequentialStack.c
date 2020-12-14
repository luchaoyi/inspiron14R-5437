

typedef struct stack
{
    DataType data[MAX_SIZE];
    int top;//栈顶指针及data[]数组下标
}SeqStack,*pStack;

void InitStack(pStack S)
{
    S->top=-1;
}

void Push(pStack S,DataType x)
{


    if(top==MAX_SIZE-1)
    {
        printf("栈满溢出");
        exit(-1);

    }
    //先自增
    S->data[++S->top]=x;
}

DataType Pop(pStack S)
{
    if(top==-1)
    {
        printf("栈空越界");
        exit(-1);
    }
    //先取值后自减
    x = S->data[S->top--];
    return x;
}

DataType GetTop(pStack S)
{
     if(top==-1)
    {
        printf("栈空越界");
        exit(-1);
    }
    return S->data[S->top];
}

bool IsEmpty(pStack S)
{
    if(S->top==-1)
        return true;
    else
        return false;

}
