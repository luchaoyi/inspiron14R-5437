
struct tree
{
	int value;
	tree* left,right;
}tree;

//联赛
//根据max改版而来
tree* Union(Item a[],int left,int right)

	tree* proot=(tree *)malloc(sizeof(tree));
	int m=(left+right)/2;
	if(left=right) //1.考虑递归终止条件;2.考虑是头递归还是尾递归
	{	
		proot->value=a[left];//a[left]=a[right]
		proot->left=proot->right=NULL;		
		return proot;
	//无终止则递归
	}
	
	proot->left=Union(a,left,m);
	proot->right=Union(a,m+1,right);
	
	if(proot->left->value>proot->right->value)
	{	
		proot->value=proot->left->value;//左子树的变量大则根为左子树变量
		return proot;
	}
	else
	{
		p->root->value=proot->right->value;
		return proot;
		
	}
}
