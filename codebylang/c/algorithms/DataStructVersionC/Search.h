
int Search_Seq(SSTable T,KeyType key)
{
	T.elem[0].key=key; //监视哨可以省去判断
	for(i=ST.length;!(EQ(ST.elem[i].key,key);--i));
	return i;
}

int Search_Bin(SSTable T,KeyType key)
{
	low=1;high=ST.length;

	while(low<=high)
	{
		mid=(low/2)+(high/2);
		if(EQ(...)) return mid;
		else if(LT(key,T.elem[mid].key))  high=mid-1;
		else low=mid+1;
	}
	return 0;
}

...getsw(w,&sw)
{
	sw[0]=0;
	for(i=0;i<**;i++)
		sw[i]+=w[i];//累计权值 
}

//次优查找树

// dotpi=|sw[high]+sw[low-1]-sw[i]-sw[i-1]|
void SecondOptimal(BiTree &T,ElemType R[],float sw,int low,int high)
{
	mi=low;
	min=sw[high]-sw[low]; //init min
	dw=sw[high]+sw[low-1]
	for(i=low;i<=high;i++)
	{
		if(abs(dw-sw[i-1]-sw[i])<min)
		{
			min=abs(...);
			mi=i;
		}
	}

	//有点决策树的感觉，安装某个标志对元素进行划分建树，使某个标准得到满足
	T=(BiTree)malloc(sizeof(BNode));
	if(!T) exit(OVERFLOW);
	T->data=R[mi];
	T->lchild=NULL;
	T->rchild=NULL;
	BiTree(T->lchild,R,sw,low,i-1);
	BiTree(T->rchild,R,sw,i+1,high);
}

int IndexSearch(InTabType &IndexTable,KeyType key)
{
	
	for(i=0;key>IndexTable[i].key;i++);
	//stop  key <= InTabType[i].Key 
	
	flag=0;
	for(j=IndexTable[i].addr;j<=n && flag == 0 ;j++)
	{
		if(==)
		{
			flag=j;
		}
	}

	return j;
}


//return 查找到元素的指针
BiTree SearchBST(BiTree T,KeyType key)
{
	//if(!T) return NULL;
	if(T==NULL ||T->elem.key==key) return T;
	if(key<T->elem.key) return SearchBST(T->lchild,key);
	return SearchBST(T->rchild,key)
}



//动态找不到返回插入位置以待插入
Status SearchBST(BiTree T,KeyType key,BiTree &f,BiTree &p)
{
	if(T==NULL) 
	{
		p=f;
		return FALSE;
	}
    if(T->elem.key==key) {
		p=T;
		return TRUE;
	}
	if(key<T->elem.key) return SearchBST(T->lchild,key,T,p);
	return SearchBST(T->rchild,key,T,p);
}
//while search not found insert
Status InsertBST(BiTree &T,ElemType e)
{

	if(!SearchBST(T,e,p))
	{
		s=(BiTree)malloc(sizeof(BiNode));
		s->elem=e;
		if(!p) p=s; //当树空时会出现此情况
		if(s->elem.key>p->elem.key) p->rchild=s;
		else p->lchild=s;

		return TRUE;
	}
	return FALSE;
}


Status DeleteBST(T,key)
{
	if(!T) return FALSE;

	else {
		if (==) return Delete(T);
		if(key>T->elem.key) DeleteBST(T->rchild,key);
		else DeleteBST(T->lchild,key);
	}
	
}

//左子树的最右
//若删除节点只有一个子树，则紧挨这此元素为另一个孩子无论左右
//&这里更改p相当于同时更改了父节点孩子节点,p相当于父节点甩下来的指针
Status Delete(BiTree &p)
{
	//左右都空蕴含者其中
	if(!p->rchild)
	{
		q=p;
		p=p->lchild;
		free(q);
	}
	else if(!p->lchild)
	{
		q=p;
		p=p->rchild;
		free(p);
	}
	else //左子树的最右 
	{ //因为是最右节点所以只可能存在左孩子或没有孩子否则不是最右,若有左孩子则定在最右位置因为最右要去顶删除节点
		s=p->lchild;
		while(s->rchild)
		{
			q=s;
			s=s->rchild;
		}
		q->rchild=s->lchild; 
		q=p;
		p=s;//挂上去

		p->rchild=q->rchild;

		free(q); //替换了节点，树上是复制了数据
	}
}

/**
 * *********************************hash*************************************
 * 1.好的hash函数减少冲突 (伪随机数法，选择key做为随机种子，适合key长度不等情况)
 * 2.冲突解决方法
 * */

//开放定址法,线性探测
















































