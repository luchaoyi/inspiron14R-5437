
//插入节点
void Insert(BiNode *root,BiNode *s)
{
	if(root==NULL)
		root=s;
	else if(s->data<root->data)
	{
		Insert(root->lchild,s);	
	}
	else
	{
		Insert(root->rchild,s);
	}	
}

//构造树
BiNode * Creat(int r[],int n)
{
	for(i=0;i<n;i++)
	{
	//申请节点
		s=(BiNode *)malloc(sizeof(BiNode));
		s->data=r[i];
		s->lchild;
		s->rchild;
	//插入
		Insert(root,s);
	}	
}

//
BiNode* Search(BiNode *root,int k)
{
	if(root==NULL) return NULL;
	
	else if(root->data==k) return root;
	
	else if(root->data>k) return Search(root->lchild,k);
	
	else 	return Search(root->rchild,k);
}

//p为被删节点
//f为p双亲,p为左孩子
void Delete(BiNode *p,BiNode *f)
{
	//1 p为叶子无左右子树
	if((p->lchild==NULL)&&(p->rchild)==NULL)
	{
		f->lchild=NULL;
		free(p);
	}
	//2无右
	else if(p->rchild==NULL)
	{
		f->lchild=p->lchild;
		free(p);
	}
	//3无左
	else if(p->lchild==NULL)
	{
		f->lchild=p->rchild;
		free(p);
	}
	
	//下一个点不是左子树的最右就是右子树的最左
	
	//取右子树左走
	else
	{
		par=p;//par保存s的前驱
		s=s->rchild;
		
		while(s->lchild!=NULL)
		{
			par=s;
			s=s->lchild;
		}
		
		p->data=s->data;
		//当右子树无左时不走直接顶
		if(par==p)
		{
			p->rchild;
			
			par->rchild=s->rchild;//特殊情况
		}
		
		else
		{
			par->lchild=s->lchild;
		}
		free(s);
	}
}

