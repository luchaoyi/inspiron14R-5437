typedef struct LinkStack
{
    DataType data;
    Node *next;
}LStack,*pLStack;



void InitStack(pLStack top)
{
    top=NULL;
}

void Push(pLStack top,DataType x)
{
    p=(DataType)malloc(sizeof(LStack));
    p->data=x;


    p->next = top;
    top=p;
}

DataType  Pop(pLStack top)
{
    if(top==NULL);
    //
    else
        temp = top;
        x=top->data;

        top=top->next;

        free(temp);

        return x;
}



