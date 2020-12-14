void union(List &LA,List &LB)
{

	for(int i=1;i<LB.len;i++)
	{
		if(!LA.find(LB[i]))
		{
					 //element position
			LA.insert(LB[i],++LB.len);
		}
	}

	LB.clearList(); //变为空表
	free(LB);
}

void Merge(List &LA,List &LB,List &LC)
{
	int i,j,k=1;

	//非降序
	while((i<=LA.len)&&(j<=LB.len))
	{
		if(LA[i]>LB[i])
		{
			LC[k]=LA[i++];
		}
		else
		{
			LC[k]=LB[j++];
		}
		k++;
	}

	while(i<=LA.len)
	{
		LC[k++]=LA[i++];
	}

	while(j<=LB.len)
	{
		LC[k++]=LB[j++];
	}


}

//线性表采用顺序存储映像时，采用动态分配的数组表示


#define LIST_INIT_SIZE 100
#define LISTINCREMENT	10 //increment

typedef struct{
	ElemType *elem;		//动态数组基地址
	int length;			//元素数
	int listsize;       //存储容量
	//length==listsize 则插入需在分配空间
}SqList;


Status InitList_Sq(SqList &L)
{
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	//注意申请内存时可能会失败，所以请检测,并抛出异常
	

	L.length=0;//vaild element ??
	l.listsize=LIST_INIT_SIZE;

	return OK;
}

Status ListInsert_Sq(SqList &L,int i ,ElemType e)
{
	//写代码时优先考虑异常检测，软件安全第一
	
	//假定元素排列为 a1,a2,..an i表示在ai之前插入即将ai以及ai以后的向后挪动
	if(i<1 || i > L.length+1) return ERROR;
	if(L.length > =L.listsize)
	{
		newbase = (ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));

		if(!newbase) exit(OVERFLOW);
		L.elem=newbase;
	}

	//0 start ai index is i-1
	ElemType *q=&(L[i-1]);

	//低地址向高地址增长
	//for(ElemType *p=L.elem;p<q;p++)
	for(ElemType *p=(&L.elem[length-1];p>=q;p--)
		*(p+1)=*p;
	*q=e;
	L.length++;

	return OK;
	
}

Status ListDelete_Sq(SqList &L,i,ElemType &e)
{
	if(i<1;i>L.length) return ERROR;
	e=L.elem[i-1];


	for(j=i;j<L.length;j++)
	{
		a[j]=a[j+1];
	}

	--L.length; //只需这一句表尾就删除的
}







