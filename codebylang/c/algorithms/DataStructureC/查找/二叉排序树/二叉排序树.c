

typedef struct SortTree
{
    int data;
    struct SortTree *lchild,*rchild;
}SortTree,*pSortTree;


/**
* fΪ����ָ��˫�׵�ָ��
  pΪ����ָ��
*/

bool BSTSearch(pSortTree root,int key,pSortTree f,pSortTree *p)
{
    if(!root)//�ݹ���ҵ���û�ҵ�
    {
        //û�ҵ�����ʱ*p=NULL
        //������ֵָ��ȥ
        *p=f;
        return false;
    }
    else if(key==root->data)
    {
        *p=T;
        return true;
    }

    //��С�Ҵ�
    else if(key>root->data)
    {
       // key���Ҵ����
      return BSTSearch(root->rchild, key, T,p);
    }
    else//key<root->data
    {
        return BSTSearch(root->lchild, key, T,p);

    }

}

bool InsertSearch(pSortTree *root,int key)
{
     pSortTree p,s;



    if(!BSTSearch(root,key,NULL,pSortTree &p))///�Ѵ��ڽڵ㷵��Ϊtrue����ִ�в������///�����Ƿ�ڵ��Ѵ���
    {
        //û�ҵ���ͬ��
            S=(pSortTree)malloc(sizeof(SortTree));
            S->data=key;
            S->lchild=S->rchild=NULL;
        //���ʱp�Ѿ���������
        //����
        if(!p)//������
        {
            *T=S;
        }
        else if(key<p->data)
        {
            p->lchild=S;
        }
        else
        {
            p->rchild=S;

        }
        return true;

    }
    else
    {
        return false;
    }
}




bool Delete(pSortTree *p)
{
    pSortTree s,q;

    if((*p)->rchild==NULL) //Ҷ��ʱ����ʱ
    {
        q=*p;
        *p=*p->lchild; //û���ҽ����ڵ������ȥ
        free(q);
    }
    else if((*p)->lchild==NULL)
    {
        q=*p;
        *p=*p->rchild;
        free(q);
    }
    else //���Ҷ���ʱ
    {
        q=*p;
        s=(*p)->lchild;

        //����ֱ��ǰ��
        //��������������
        while(s->rchild)
        {
            q=s;
            s=s->rchild;
        }

        (*p)->data=s->data;

        if(q!=p)
        {
            q->rchild=s->lchild;
        }
        else
        {
            q->lchild=s->lchild;

        }
        free(s);
    }
}


bool DeleteBST(pSortTree *T,int key)
{
    if(!*T)
    {
        return false;


    }
    else
    {
        if(key==(*T)->data)
        {
            return Delete(T);//ɾ���ڵ�

        }
        else if(key<(*T)->data)
        {
            return DeleteBST(&(*T)->lchild,key)

        }
        else
        {
           return  DeleteBST(&(*T)->rchild,key)

        }

    }

}


/**
My Error Think;

void  SortTree(pSortTree root,int r[],int n,int i)
{
    pSortTree p;
    if(i<=n-1)
    {
        p=(pSortTree)malloc(sizeof(SortTree));
        p->data=r[i];

        if(r[i]>root->data)
            root->rchild=p;
            SortTree(root->rchild,r,n,i+1);
        else
            root->lchild=p;
            SortTree(root->lchild,r,n,i+1);
    }
}
**/
