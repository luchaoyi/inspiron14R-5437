

typedef struct SortTree
{
    int data;
    struct SortTree *lchild,*rchild;
}SortTree,*pSortTree;


/**
* f为反向指向双亲的指针
  p为工作指针
*/

bool BSTSearch(pSortTree root,int key,pSortTree f,pSortTree *p)
{
    if(!root)//递归查找到底没找到
    {
        //没找到到底时*p=NULL
        //给它赋值指回去
        *p=f;
        return false;
    }
    else if(key==root->data)
    {
        *p=T;
        return true;
    }

    //左小右大
    else if(key>root->data)
    {
       // key大找大的右
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



    if(!BSTSearch(root,key,NULL,pSortTree &p))///已存在节点返回为true不会执行插入操作///查找是否节点已存在
    {
        //没找到相同的
            S=(pSortTree)malloc(sizeof(SortTree));
            S->data=key;
            S->lchild=S->rchild=NULL;
        //完成时p已经搜索到底
        //查找
        if(!p)//到底了
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

    if((*p)->rchild==NULL) //叶子时到底时
    {
        q=*p;
        *p=*p->lchild; //没有右将存在的左接上去
        free(q);
    }
    else if((*p)->lchild==NULL)
    {
        q=*p;
        *p=*p->rchild;
        free(q);
    }
    else //左右都有时
    {
        q=*p;
        s=(*p)->lchild;

        //搜索直接前驱
        //即左子树的最右
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
            return Delete(T);//删除节点

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
