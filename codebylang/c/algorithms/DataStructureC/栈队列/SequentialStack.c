

typedef struct stack
{
    DataType data[MAX_SIZE];
    int top;//ջ��ָ�뼰data[]�����±�
}SeqStack,*pStack;

void InitStack(pStack S)
{
    S->top=-1;
}

void Push(pStack S,DataType x)
{


    if(top==MAX_SIZE-1)
    {
        printf("ջ�����");
        exit(-1);

    }
    //������
    S->data[++S->top]=x;
}

DataType Pop(pStack S)
{
    if(top==-1)
    {
        printf("ջ��Խ��");
        exit(-1);
    }
    //��ȡֵ���Լ�
    x = S->data[S->top--];
    return x;
}

DataType GetTop(pStack S)
{
     if(top==-1)
    {
        printf("ջ��Խ��");
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
