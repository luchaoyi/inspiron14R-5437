
//����ڵ�
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

//������
BiNode * Creat(int r[],int n)
{
	for(i=0;i<n;i++)
	{
	//����ڵ�
		s=(BiNode *)malloc(sizeof(BiNode));
		s->data=r[i];
		s->lchild;
		s->rchild;
	//����
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

//pΪ��ɾ�ڵ�
//fΪp˫��,pΪ����
void Delete(BiNode *p,BiNode *f)
{
	//1 pΪҶ������������
	if((p->lchild==NULL)&&(p->rchild)==NULL)
	{
		f->lchild=NULL;
		free(p);
	}
	//2����
	else if(p->rchild==NULL)
	{
		f->lchild=p->lchild;
		free(p);
	}
	//3����
	else if(p->lchild==NULL)
	{
		f->lchild=p->rchild;
		free(p);
	}
	
	//��һ���㲻�������������Ҿ���������������
	
	//ȡ����������
	else
	{
		par=p;//par����s��ǰ��
		s=s->rchild;
		
		while(s->lchild!=NULL)
		{
			par=s;
			s=s->lchild;
		}
		
		p->data=s->data;
		//������������ʱ����ֱ�Ӷ�
		if(par==p)
		{
			p->rchild;
			
			par->rchild=s->rchild;//�������
		}
		
		else
		{
			par->lchild=s->lchild;
		}
		free(s);
	}
}

