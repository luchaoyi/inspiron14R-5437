#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct{
	SElemType *base; 
	SElemType *top;

	int stacksize; //栈容量
}SqStack;

Status InitStack(SqStack &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) exit(OVERFLOW);
	S.top=S.base;
	S.stacksize = STACK_INIT_SIZE;

	return OK;
}

Status GetTop(SqStack S,SElemType &e){
	if(S.top==S.base) return ERROR;
	e=*(S.top-1);

	return OK;
}


Status Push(SqStack &S,SElemType e)
{
	//isFull
	if(S.top-S.base>=S.stacksize)
	{
		S. base = (SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType)); //地址可能已经变了,S.top也需要重新赋值

		if(!S.base) exit(OVERFLOW);

		S.stacksize+=STACKINCREMENT;
		S.top = S.base+S.stacksize;
	}
	*S.top++ =e ;
	return OK;
}

Status Pop(SqStack &S,SElemType &e)
{
	//isEmpty
	if(S.top == S.base) return ERROR;
	e=*(--S.top);

	return OK;
}

void conversion()
{
	InitStack(S);
	scanf("%d",N);

	while(N)
	{
		Push(S,N%8);
		N=N/8;
	}

	while(!isStackEmpty())
	{
		Pop(S,e);
		printf("%d",e);

	}
}

Status bracket_match(char *express)
{
	InitStack(S);
	for(i=0;express[i]!='\0';i++)
	{
		if(express[i] == '[' || express[i] == '{' || express[i] == '(')
		{
			Push(S,express[i]);
		}
		else
		{
			switch(express[i])
			{
				case ']':
					{
						if(GetTop(S)=='[') Pop(S,e);
					}
				//...
			}
		}
	}

	if(isStackEmpty(S)) return OK;
	return ERROR;
}
//------------------------------------------------
//迷宫搜索，回朔法利用栈来保存历史信息以待回溯

typedef struct{
	int ord; //路径上的序号 ,走到了第几步
	PosType seat; //坐标
	int di;//方向,按照一个方向深度优先搜索
}SElemType 

//start-->end 
Status MazePath(MazeType maze,PosType start,PosType end)
{
	InitStack(S);
	curpos = start;

	do{
		if(Pass(curpos)){ 
			FooPrint(curpos);//到达
			e=(curstep,curpos,1);//入栈保存

			Push(S,e); 

			if(curpos==end) return TRUE;
			curpos =NextPos(curpos,1);//移动
			curstep++;
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);
				while(e.di==4&&!StackEmpty(S))
				{
					MarkPrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4){
					e.di++;
					Push(S.e);
					curpos = NextPos(e.seat,e.di);

				}//if
			}//if 
		}//else
	}while(!(StackEmpty()));

	return(FALSE);
}

//递归函数千万要高度抽象不要注意细节，明确函数功能当作一个已有函数使用
//函数作用将n个盘子从x搬到z
void hanoi(int n,char x,char y,char z)
{
	//hanoi 
	//1.将n-1个从x搬到y(辅助) 展开递归
	//2.第n个x->z
	//3.n-1个从y搬到z    展开递归 
	
	if(n==1)
	{
		move(x->z);
	}
	else
	{
		hanoi(n-1,x,z,y); //x-->y
		move(x->z);
		hanoi(n-1,y,x,z);//y-->z
	}
}




